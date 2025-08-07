#include "cageDeformer.hpp"
#include "common.hpp"

#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMessageAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MGlobal.h>
#include <maya/MArrayDataBuilder.h>
#include <maya/MArrayDataHandle.h>
#include <maya/MFnNumericData.h>
#include <maya/MStatus.h>
#include <maya/MPlug.h>
#include <maya/MPoint.h>
#include <maya/MVector.h>
#include <maya/MMatrix.h>
#include <maya/MItGeometry.h>
#include <maya/MDataBlock.h>
#include <maya/MObject.h>
#include <maya/MTypeId.h>
#include <maya/MPxDeformerNode.h>
#include <maya/MThreadPool.h>

#include <LBFGSB.h>
#include <Eigen/Core>

#include <thread>
#include <vector>


// This ID is registered with Autodesk (https://adndata.autodesk.io/maya).
MTypeId bezierCage::id(0x0013f8c1);

const char *bezierCage::typeName = "bezierCage";

MObject bezierCage::aControlMessage;
MObject bezierCage::aPatchMatrices;
MObject bezierCage::aMatrix;
MObject bezierCage::aBindPreMatrix;
MObject bezierCage::aPatchBindPreMatrices;
MObject bezierCage::aThreshDist;
MObject bezierCage::aBindUV;
MObject bezierCage::aBindDistance;
MObject bezierCage::aBindPatchIndex;
MObject bezierCage::aVertexBindPosition;
MObject bezierCage::aVertexBindData;
MObject bezierCage::aGeometryBindData;
MObject bezierCage::aDirty;

bezierCage::bezierCage(): MDeformTaskData() {
    unsigned int kTaskCount = std::thread::hardware_concurrency();
    // Fallback to a single thread if the number of threads cannot be determined
    if (kTaskCount == 0) { kTaskCount = 1; }
#if DEBUG_LOG
    MGlobal::displayInfo(MString("Using ") + kTaskCount + " threads for bezierCage deformer.");
#endif
    MDeformThreadData.resize(kTaskCount);
}

MStatus bezierCage::initialize() {
    MFnCompoundAttribute cAttr;
    MFnMatrixAttribute mAttr;
    MFnNumericAttribute fAttr;
    MFnMessageAttribute meAttr;

    // Dirty Attribute
    aDirty = fAttr.create("dirty", "dirty", MFnNumericData::kBoolean, true);
    fAttr.setStorable(true);
    addAttribute(aDirty);

    // Message Attribute
    aControlMessage = meAttr.create("controlMessage", "controlMessage");
    meAttr.setReadable(false);
    addAttribute(aControlMessage);

    // Matrix Attribute
    aMatrix = mAttr.create("Matrix", "Matrix");
    mAttr.setArray(true);

    // Patch Matrices Compound
    aPatchMatrices = cAttr.create("patchMatrices", "patchMatrices");
    cAttr.setArray(true);
    cAttr.addChild(aMatrix);
    addAttribute(aPatchMatrices);

    // Bind Pre Matrix
    aBindPreMatrix = mAttr.create("bindPreMatrix", "bindPreMatrix");
    mAttr.setUsesArrayDataBuilder(true);
    mAttr.setArray(true);
    mAttr.setStorable(true);
    addAttribute(aBindPreMatrix);

    // Patch Bind Pre Matrices Compound
    aPatchBindPreMatrices = cAttr.create("patchBindPreMatrices", "patchBindPreMatrices");
    cAttr.addChild(aBindPreMatrix);
    cAttr.setArray(true);
    cAttr.setStorable(true);
    cAttr.setUsesArrayDataBuilder(true);
    addAttribute(aPatchBindPreMatrices);

    // Threshold Distance
    aThreshDist = fAttr.create("thresholdDist", "thresholdDist", MFnNumericData::kFloat, 1.0f);
    fAttr.setKeyable(true);
    fAttr.setStorable(true);
    addAttribute(aThreshDist);

    // Bind UV
    aBindUV = fAttr.create("bindUV", "bruv", MFnNumericData::k2Float);
    fAttr.setStorable(true);
    addAttribute(aBindUV);

    // Vertex Bind Position
    aVertexBindPosition = fAttr.create("bindPosition", "bpos", MFnNumericData::k3Float);
    fAttr.setStorable(true);
    addAttribute(aVertexBindPosition);

    // Bind Distance
    aBindDistance = fAttr.create("bindDistance", "bdist", MFnNumericData::kFloat, 0.0f);
    fAttr.setStorable(true);
    addAttribute(aBindDistance);

    // Bind Patch Index
    aBindPatchIndex = fAttr.create("bindPatchIndex", "bpidx", MFnNumericData::kInt, -1);
    fAttr.setStorable(true);
    addAttribute(aBindPatchIndex);

    // Vertex Bind Data Compound
    aVertexBindData = cAttr.create("vertexBindData", "vbd");
    cAttr.setArray(true);
    cAttr.setStorable(true);
    cAttr.setHidden(true);
    cAttr.setConnectable(false);
    cAttr.setUsesArrayDataBuilder(true);
    cAttr.addChild(aBindUV);
    cAttr.addChild(aBindDistance);
    cAttr.addChild(aBindPatchIndex);
    cAttr.addChild(aVertexBindPosition);
    addAttribute(aVertexBindData);

    // Geometry Bind Data Compound
    aGeometryBindData = cAttr.create("geometryBindData", "gbd");
    cAttr.setArray(true);
    cAttr.setStorable(true);
    cAttr.setHidden(true);
    cAttr.setConnectable(false);
    cAttr.setUsesArrayDataBuilder(true);
    cAttr.addChild(aVertexBindData);
    addAttribute(aGeometryBindData);

    // Attribute affects
    MStatus status = attributeAffects(aPatchMatrices, outputGeom);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    status = attributeAffects(aThreshDist, outputGeom);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    status = attributeAffects(aGeometryBindData, outputGeom);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    status = attributeAffects(aDirty, outputGeom);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MString paintCmd;
    paintCmd.format("makePaintable -attrType multiFloat -shapeMode deformer ^1s weights",
                    MString(typeName));
    MGlobal::executeCommand(paintCmd);

    return status;
}

void *bezierCage::creator() {
    return new bezierCage();
}

MStatus bezierCage::deform(MDataBlock &dataBlock, MItGeometry &geometryIterator, const MMatrix &localToWorldMatrix,
                           unsigned int geometryIndex) {
    // early exit if envelope is 0
    MStatus status;
    const float fEnvelope = dataBlock.inputValue(envelope, &status).asFloat();
    CHECK_MSTATUS_AND_RETURN_IT(status);
    if (fEnvelope == 0.0f) { return status; }
    status = updateBindPreMatrixPlugs(dataBlock);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    // bind the geometry if not already bound
    status = bind(dataBlock, geometryIterator, localToWorldMatrix, geometryIndex);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    // gather all data for threading
    const auto controlPoints = getControlPoints(dataBlock);
    const auto preControlPoints = getControlPoints(dataBlock, true);
    MPointArray points;
    geometryIterator.allPositions(points);
    std::vector<float> bindDist, weights, u, v;
    std::vector<unsigned int> patchIdx;
    const auto numPoints = points.length();
    bindDist.reserve(numPoints);
    weights.reserve(numPoints);
    u.reserve(numPoints);
    v.reserve(numPoints);
    patchIdx.reserve(numPoints);
    float thresh = dataBlock.inputValue(aThreshDist, &status).asFloat();
    CHECK_MSTATUS_AND_RETURN_IT(status);

    // gather bind data
    MArrayDataHandle geomBindHandle = dataBlock.inputArrayValue(aGeometryBindData, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    status = geomBindHandle.jumpToElement(geometryIndex);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MDataHandle geomElem = geomBindHandle.inputValue(&status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MArrayDataHandle vertBindHandle = geomElem.child(aVertexBindData);

    for (unsigned int i = 0; i < numPoints; ++i) {
        status = vertBindHandle.jumpToElement(i);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        MDataHandle bindData = vertBindHandle.inputValue(&status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        float bindDistVal = bindData.child(aBindDistance).asFloat();
        const float *uvPtr = bindData.child(aBindUV).asFloat2();
        float uVal = uvPtr[0];
        float vVal = uvPtr[1];
        unsigned int patchIdxVal = static_cast<unsigned int>(bindData.child(aBindPatchIndex).asInt());

        float weightVal = weightValue(dataBlock, geometryIndex, i);

        bindDist.push_back(bindDistVal);
        u.push_back(uVal);
        v.push_back(vVal);
        patchIdx.push_back(patchIdxVal);
        weights.push_back(weightVal);
    }

    const MMatrix worldToLocalMatrix = localToWorldMatrix.inverse();

    // prepare thread tasks
    MDeformTaskData.numVerts = points.length();
    MDeformTaskData.points = &points;
    MDeformTaskData.bindDistance = &bindDist;
    MDeformTaskData.weights = &weights;
    MDeformTaskData.envelope = fEnvelope;
    MDeformTaskData.distanceTreshold = thresh;
    MDeformTaskData.controlPoints = &controlPoints;
    MDeformTaskData.preControlPoints = &preControlPoints;
    MDeformTaskData.patchIndex = &patchIdx;
    MDeformTaskData.u = &u;
    MDeformTaskData.v = &v;
    MDeformTaskData.localToWorldMatrix = &localToWorldMatrix;
    MDeformTaskData.worldToLocalMatrix = &worldToLocalMatrix;

    CreateThreadData();
    MThreadPool::newParallelRegion(CreateTasks, static_cast<void *>(&MDeformThreadData[0]));
    geometryIterator.setAllPositions(points);

    return status;
}

void bezierCage::CreateThreadData() {
    int taskCount = static_cast<int>(MDeformThreadData.size());
    unsigned int taskLength = (MDeformTaskData.numVerts + taskCount - 1) / taskCount;
    unsigned int start = 0, end = taskLength;
    for (int i = 0; i < taskCount; ++i) {
        if (i == taskCount - 1) { end = MDeformTaskData.numVerts; }
        MDeformThreadData[i] = {start, end, static_cast<unsigned int>(taskCount), &MDeformTaskData};
        start += taskLength;
        end += taskLength;
    }
}

void bezierCage::CreateTasks(void *pData, MThreadRootTask *pRoot) {
    deformThreadData *pThreadData = static_cast<deformThreadData *>(pData);
    int taskCount = pThreadData[0].numTasks;
    for (int i = 0; i < taskCount; ++i) {
        MThreadPool::createTask(ThreadEvaluate, static_cast<void *>(&pThreadData[i]), pRoot);
    }
    MThreadPool::executeAndJoin(pRoot);
}

MThreadRetVal bezierCage::ThreadEvaluate(void *pParam) {
    const auto *threadData = static_cast<deformThreadData *>(pParam);
    deformTaskData *data = threadData->data;
    auto &points = *data->points;
    const auto &bindDist = *data->bindDistance;
    const auto &weights = *data->weights;
    const auto &patchIdx = *data->patchIndex;
    const auto &u = *data->u;
    const auto &v = *data->v;
    const auto &controlPoints = *data->controlPoints;
    const auto &preControlPoints = *data->preControlPoints;
    const auto &worldToLocalMatrix = *data->worldToLocalMatrix;
    const auto &localToWorldMatrix = *data->localToWorldMatrix;
    const auto &envelope = data->envelope;

    for (unsigned int i = threadData->start; i < threadData->end; ++i) {
        if (i >= bindDist.size() || i >= weights.size() || i >= patchIdx.size() || i >= u.size() || i >= v.size() || i
            >= points.length()) {
#if ERROR_LOG
            MGlobal::displayError("Index out of bounds in ThreadEvaluate: " + MString(std::to_string(i).c_str()));
#endif
            continue;
        }

        const auto weight = weights[i];

        // Skip calculation if we don't need to deform to be faster
        if (weight != 0.0f && bindDist[i] < data->distanceTreshold) {
#if DEBUG_LOG
            MGlobal::displayInfo("Deforming vertex at index " + MString(std::to_string(i).c_str()));
            MGlobal::displayInfo("Points length: " + points.length());
            MGlobal::displayInfo("Patch index: " + MString(std::to_string(patchIdx[i]).c_str()));
            MGlobal::displayInfo("U: " + MString(std::to_string(u[i]).c_str()) + ", V: " + MString(std::to_string(v[i]).c_str()));
#endif

            // Calculate the deformation in world space
            MPoint worldPoint = points[i] * localToWorldMatrix;
            MPoint preDeformPoint = evaluateBezierPatch(preControlPoints[patchIdx[i]], u[i], v[i]);
            MPoint postDeformPoint = evaluateBezierPatch(controlPoints[patchIdx[i]], u[i], v[i]);
            MVector deformVec = postDeformPoint - preDeformPoint;
#if DEBUG_LOG
            MGlobal::displayInfo("Calculated deformation vector");
#endif
            worldPoint += deformVec * weight * envelope;

            // Maya Deformers expect the points to be in local space
            points[i] = worldPoint * worldToLocalMatrix;
        }
    }
    return 0;
}

MStatus bezierCage::bind(MDataBlock &dataBlock, MItGeometry &geometryIterator, const MMatrix &localToWorldMatrix,
                         unsigned int geometryIndex) {
    MStatus status;

    MDataHandle dirtyHandle = dataBlock.inputValue(aDirty, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    if (!dirtyHandle.asBool()) {
#if DEBUG_LOG
        MGlobal::displayInfo("Geometry already bound, skipping binding.");
#endif
        return status;
    }

    auto controlPoints = getControlPoints(dataBlock, true);
    if (controlPoints.empty()) {
#if ERROR_LOG
        MGlobal::displayError("No valid NURBS surface connected to the deformer.");
#endif
        return MS::kFailure;
    }

#if DEBUG_LOG
    MGlobal::displayInfo(MString("Binding geometry at index ") + MString(std::to_string(geometryIndex).c_str()) +
                  MString(" to bezier cage with ") + MString(std::to_string(controlPoints.size()).c_str()) + MString(" patches."));
#endif

    MArrayDataHandle geometryBindDataHandle = dataBlock.inputArrayValue(aGeometryBindData, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MArrayDataBuilder geometryBindDataBuilder = geometryBindDataHandle.builder(&status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MDataHandle geometryElementHandle = geometryBindDataBuilder.addElement(geometryIndex);
    MArrayDataHandle vertexBindDataHandle = geometryElementHandle.child(aVertexBindData);
    MArrayDataBuilder vertexBindDataBuilder = vertexBindDataHandle.builder();

    for (geometryIterator.reset(); !geometryIterator.isDone(); geometryIterator.next()) {
        MPoint currentWorldPosition = geometryIterator.position() * localToWorldMatrix;
        float minDistance = std::numeric_limits<float>::max();

        MDataHandle vertexElementHandle = vertexBindDataBuilder.addElement(geometryIterator.index());
        MDataHandle uvHandle = vertexElementHandle.child(aBindUV);
        MDataHandle bindDistHandle = vertexElementHandle.child(aBindDistance);
        MDataHandle patchIdxHandle = vertexElementHandle.child(aBindPatchIndex);
        MDataHandle bindPosHandle = vertexElementHandle.child(aVertexBindPosition);
        bindPosHandle.set3Float(static_cast<float>(currentWorldPosition.x), static_cast<float>(currentWorldPosition.y),
                                static_cast<float>(currentWorldPosition.z));

        int patchIndex = 0;
        for (const auto &patchControlPoints: controlPoints) {
            auto uv = findBindingUV(patchControlPoints, currentWorldPosition);
#if DEBUG_LOG
            MGlobal::displayInfo("Binding UV for vertex at index " +
                                 MString(std::to_string(geometryIterator.index()).c_str()) + ": (" +
                                 MString(std::to_string(uv[0]).c_str()) + ", " +
                                 MString(std::to_string(uv[1]).c_str()) + ")");
#endif
            MPoint surfacePoint = evaluateBezierPatch(patchControlPoints, uv[0], uv[1]);

            if (double distance = currentWorldPosition.distanceTo(surfacePoint); distance < minDistance) {
                minDistance = static_cast<float>(distance);
                bindDistHandle.setFloat(minDistance);
                uvHandle.set2Float(uv[0], uv[1]);
                patchIdxHandle.setInt(patchIndex);
            }
            patchIndex++;
        }
#if DEBUG_LOG
        MGlobal::displayInfo(MString("Minimum distance for vertex at index ") +
                             MString(std::to_string(geometryIterator.index()).c_str()) + ": " +
                             MString(std::to_string(minDistance).c_str()));
#endif
    }

    vertexBindDataHandle.set(vertexBindDataBuilder);
    vertexBindDataHandle.setAllClean();
    geometryBindDataHandle.set(geometryBindDataBuilder);
    geometryBindDataHandle.setAllClean();

    dirtyHandle.setBool(false);
    dirtyHandle.setClean();

    return MS::kSuccess;
}

MStatus bezierCage::updateBindPreMatrixPlugs(MDataBlock &dataBlock) {
    MStatus status;
    MArrayDataHandle patchMatricesHandle = dataBlock.inputArrayValue(aPatchMatrices, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MArrayDataHandle patchBindPreMatricesHandle = dataBlock.inputArrayValue(aPatchBindPreMatrices, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MArrayDataBuilder patchBindPreMatricesBuilder = patchBindPreMatricesHandle.builder(&status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    status = patchMatricesHandle.jumpToArrayElement(0);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    do {
        MDataHandle patchMatrixElemHandle = patchMatricesHandle.inputValue(&status).child(aMatrix);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        MArrayDataHandle matrixArrayHandle(patchMatrixElemHandle);

        MDataHandle patchBindPreMatrixElemHandle = patchBindPreMatricesBuilder.addElement(
            patchMatricesHandle.elementIndex());
        MArrayDataHandle bindPreMatrixArrayHandle = patchBindPreMatrixElemHandle.child(aBindPreMatrix);
        MArrayDataBuilder bindPreMatrixArrayBuilder = bindPreMatrixArrayHandle.builder();

        unsigned int existingMatrixCount = bindPreMatrixArrayHandle.elementCount();
        if (matrixArrayHandle.elementCount() > existingMatrixCount) {
            matrixArrayHandle.jumpToArrayElement(existingMatrixCount);
            do {
                unsigned int matrixIndex = matrixArrayHandle.elementIndex();
                MMatrix matrixValue = matrixArrayHandle.inputValue().asMatrix();
                MDataHandle bindPreMatrixElemHandle = bindPreMatrixArrayBuilder.addElement(matrixIndex);
                bindPreMatrixElemHandle.setMMatrix(matrixValue);
            } while (matrixArrayHandle.next() == MS::kSuccess);
            bindPreMatrixArrayHandle.set(bindPreMatrixArrayBuilder);
        }
        bindPreMatrixArrayHandle.setAllClean();
    } while (patchMatricesHandle.next() == MS::kSuccess);

    patchBindPreMatricesHandle.set(patchBindPreMatricesBuilder);
    patchBindPreMatricesHandle.setAllClean();
    return status;
}

std::vector<std::vector<MPoint> > bezierCage::getControlPoints(MDataBlock &dataBlock, const bool preDeform) {
    MStatus status;
    std::vector<std::vector<MPoint> > patches;

    MObject matrixArrayAttr = preDeform ? aPatchBindPreMatrices : aPatchMatrices;
    MObject matrixAttr = preDeform ? aBindPreMatrix : aMatrix;

    MArrayDataHandle patchArrayHandle = dataBlock.inputArrayValue(matrixArrayAttr, &status);
    CHECK_MSTATUS_AND_RETURN(status, patches);

    const unsigned int patchCount = patchArrayHandle.elementCount();
    patches.reserve(patchCount);

    status = patchArrayHandle.jumpToArrayElement(0);
    CHECK_MSTATUS_AND_RETURN(status, patches);

    do {
        MDataHandle patchElementHandle = patchArrayHandle.inputValue(&status);
        MDataHandle matrixArrayDataHandle = patchElementHandle.child(matrixAttr);
        MArrayDataHandle matrixArrayHandle(matrixArrayDataHandle);

        if (auto patchPoints = getPatchPoints(matrixArrayHandle); !patchPoints.empty()) {
            patches.push_back(patchPoints);
        }
    } while (patchArrayHandle.next() == MS::kSuccess);

    return patches;
}

std::vector<MPoint> bezierCage::getPatchPoints(MArrayDataHandle &matrixArray) {
    MStatus status;
    /* The input structure for the control points is as follows:
     *
     * 8---9---10--11
     * |   |   |   |
     * 6---X---X---7
     * |   |   |   |
     * 4---X---X---5
     * |   |   |   |
     * 0---1---2---3
     *
     * The points marked with 'X' are computed from the other points, so they are not
     * specified in the input.
     *
     * That's why we expect 12 matrices in the array.
     */
    if (matrixArray.elementCount() != 12) {
#if ERROR_LOG
        MGlobal::displayError("Patch must consist of 12 matrices, found " +
                              MString(std::to_string(matrixArray.elementCount()).c_str()));
#endif
        return {};
    }
    std::vector<MPoint> inputPoints;
    inputPoints.reserve(12);
    status = matrixArray.jumpToArrayElement(0);
    CHECK_MSTATUS_AND_RETURN(status, inputPoints);

    do {
        MMatrix matrix = matrixArray.inputValue(&status).asMatrix();
        CHECK_MSTATUS_AND_RETURN(status, inputPoints);
        inputPoints.emplace_back(matrix(3, 0), matrix(3, 1), matrix(3, 2));
    } while (matrixArray.next() == MS::kSuccess);

    if (inputPoints.size() != 12) {
#if ERROR_LOG
        MGlobal::displayError("Failed to read matrixArray");
#endif
        return {};
    }

    /* Here we compute the interior points to get the full set of control points.
     *
     * X---X---X---X
     * |   |   |   |
     * X---2---3---X
     * |   |   |   |
     * X---0---1---X
     * |   |   |   |
     * X---X---X---X
     *
     * The position of 0 would be the vector from 0 to 1 from point 4.
     *
     * in the final control points array, the points are ordered as follows:
     *
     * 12--13--14--15
     * |   |   |   |
     * 8---9--10---11
     * |   |   |   |
     * 4---5---6---7
     * |   |   |   |
     * 0---1---2---3
     *
     * there is no differentiation between defined control points and computed
     * interior points anymore as this is not relevant for the evaluation of the cage.
     *
     */

    std::vector<MPoint> controlPoints(16);

    // Bottom row
    controlPoints[0] = inputPoints[0];
    controlPoints[1] = inputPoints[1];
    controlPoints[2] = inputPoints[2];
    controlPoints[3] = inputPoints[3];

    // Second row
    controlPoints[4] = inputPoints[4];
    controlPoints[5] = inputPoints[4] + (inputPoints[1] - inputPoints[0]);
    controlPoints[6] = inputPoints[5] + (inputPoints[2] - inputPoints[3]);
    controlPoints[7] = inputPoints[5];

    // Third row
    controlPoints[8] = inputPoints[6];
    controlPoints[9] = inputPoints[6] + (inputPoints[9] - inputPoints[8]);
    controlPoints[10] = inputPoints[7] + (inputPoints[10] - inputPoints[11]);
    controlPoints[11] = inputPoints[7];

    // Top row
    controlPoints[12] = inputPoints[8];
    controlPoints[13] = inputPoints[9];
    controlPoints[14] = inputPoints[10];
    controlPoints[15] = inputPoints[11];

    return controlPoints;
}

class BezierPatchDistance
{
    const std::vector<MPoint>& controlPoints;
    const MPoint& queryPoint;
    const int u_degree = 3;
    const int v_degree = 3;

    std::array<double, 4> bernstein(double t) const {
        double t2 = t * t;
        double t3 = t2 * t;
        double one_minus_t = 1.0 - t;
        double one_minus_t2 = one_minus_t * one_minus_t;
        double one_minus_t3 = one_minus_t2 * one_minus_t;
        return {one_minus_t3, 3.0 * t * one_minus_t2, 3.0 * t2 * one_minus_t, t3};
    }

    std::array<double, 4> bernstein_derivative(double t) const {
        double t2 = t * t;
        double one_minus_t = 1.0 - t;
        double one_minus_t2 = one_minus_t * one_minus_t;
        return {-3.0 * one_minus_t2, 3.0 * one_minus_t2 - 6.0 * t * one_minus_t, 6.0 * t * one_minus_t - 3.0 * t2, 3.0 * t2};
    }

public:
    BezierPatchDistance(const std::vector<MPoint>& cps, const MPoint& qp)
        : controlPoints(cps), queryPoint(qp) {}

    MPoint evaluate(double u, double v) const {
        auto B_u = bernstein(u);
        auto B_v = bernstein(v);
        MPoint point(0, 0, 0);
        for (int i = 0; i <= u_degree; ++i) {
            for (int j = 0; j <= v_degree; ++j) {
                point += controlPoints[i * (v_degree + 1) + j] * B_u[i] * B_v[j];
            }
        }
        return point;
    }

    void derivatives(double u, double v, MVector& dPdu, MVector& dPdv) const {
        auto B_u = bernstein(u);
        auto B_v = bernstein(v);
        auto dB_u = bernstein_derivative(u);
        auto dB_v = bernstein_derivative(v);

        dPdu = MVector::zero;
        dPdv = MVector::zero;

        for (int i = 0; i <= u_degree; ++i) {
            for (int j = 0; j <= v_degree; ++j) {
                const MPoint& cp = controlPoints[i * (v_degree + 1) + j];
                dPdu += MVector(cp) * dB_u[i] * B_v[j];
                dPdv += MVector(cp) * B_u[i] * dB_v[j];
            }
        }
    }

    double operator()(const Eigen::VectorXd& uv, Eigen::VectorXd& grad) {
        double u = uv[0];
        double v = uv[1];

        MPoint p = evaluate(u, v);
        MVector diff = p - queryPoint;

        MVector dPdu, dPdv;
        derivatives(u, v, dPdu, dPdv);

        grad.resize(2);
        grad[0] = 2.0 * diff * dPdu;
        grad[1] = 2.0 * diff * dPdv;

        return diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
    }
};

std::array<float, 2> bezierCage::findBindingUV(const std::vector<MPoint>& controlPoints,
                                               const MPoint& queryPoint) {
    LBFGSpp::LBFGSBParam<double> param;
    param.epsilon = 1e-5;
    param.max_iterations = 100;

    LBFGSpp::LBFGSBSolver<double> solver(param);
    BezierPatchDistance fun(controlPoints, queryPoint);

    int n = 2;
    Eigen::VectorXd lb = Eigen::VectorXd::Constant(n, 0.0);
    Eigen::VectorXd ub = Eigen::VectorXd::Constant(n, 1.0);

    Eigen::VectorXd uv = Eigen::VectorXd::Constant(static_cast<Eigen::Index>(n), 0.5);

    double fx;
    solver.minimize(fun, uv, fx, lb, ub);

    return {static_cast<float>(uv[0]), static_cast<float>(uv[1])};
}
