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


// This ID is registered with Autodesk and should not clash with other nodes.
MTypeId bezierCage::id(0x0013f8c0);

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


MStatus bezierCage::initialize() {
    MStatus status;

    MFnCompoundAttribute cAttr;
    MFnMatrixAttribute mAttr;
    MFnNumericAttribute fAttr;
    MFnMessageAttribute meAttr;

    // Dirty Attribute
    aDirty = fAttr.create("bound", "bound", MFnNumericData::kBoolean, true);
    fAttr.setArray(true);
    fAttr.setStorable(true);
    fAttr.setUsesArrayDataBuilder(true);
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
    status = attributeAffects(aPatchMatrices, outputGeom);
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
    MStatus status;
    const float fEnvelope = dataBlock.inputValue(envelope, &status).asFloat();
    CHECK_MSTATUS_AND_RETURN_IT(status);
    if (fEnvelope == 0.0f) { return status; }
    status = updateBindPreMatrixPlugs(dataBlock);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    status = bind(dataBlock, geometryIterator, localToWorldMatrix, geometryIndex);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    const auto controlPoints = getControlPoints(dataBlock);
    const auto preControlPoints = getControlPoints(dataBlock, true);

    MPoint currentPoint;
    MVector deformVector;

    for (geometryIterator.reset(); !geometryIterator.isDone(); geometryIterator.next()) {
        currentPoint = geometryIterator.position();
        deformVector = getDeformVector(
            dataBlock,
            controlPoints,
            preControlPoints,
            geometryIterator.index(),
            geometryIndex
        );
        const float weight = weightValue(dataBlock, geometryIndex, geometryIterator.index());
        geometryIterator.setPosition(currentPoint + (deformVector * weight * fEnvelope));
    }
    return status;
}

MVector bezierCage::getDeformVector(MDataBlock &dataBlock, const std::vector<std::vector<MPoint> > &controlPoints,
                                    const std::vector<std::vector<MPoint> > &preControlPoints, unsigned int vertexIndex,
                                    unsigned int geometryIndex) {
    MStatus status;
    MArrayDataHandle geomBindHandle = dataBlock.inputArrayValue(aGeometryBindData, &status);
    CHECK_MSTATUS_AND_RETURN(status, MVector());
    status = geomBindHandle.jumpToElement(geometryIndex);
    CHECK_MSTATUS_AND_RETURN(status, MVector());
    MDataHandle geomElem = geomBindHandle.inputValue(&status);
    CHECK_MSTATUS_AND_RETURN(status, MVector());
    MArrayDataHandle vertBindHandle = geomElem.child(aVertexBindData);
    status = vertBindHandle.jumpToElement(vertexIndex);
    CHECK_MSTATUS_AND_RETURN(status, MVector());
    MDataHandle bindData = vertBindHandle.inputValue(&status);
    CHECK_MSTATUS_AND_RETURN(status, MVector());
    float bindDist = bindData.child(aBindDistance).asFloat();
    float thresh = dataBlock.inputValue(aThreshDist, &status).asFloat();
    CHECK_MSTATUS_AND_RETURN(status, MVector());
    if (bindDist > thresh) {
#if DEBUG_LOG
        MGlobal::displayInfo(
            MString("Vertex at index ") + vertexIndex +
            MString(" is too far from the cage, skipping deformation.")
        );
#endif
        return MVector();
    }

    const auto *uvPtr = bindData.child(aBindUV).asFloat2();
    const float u = uvPtr[0];
    const float v = uvPtr[1];
    const int patchIdx = bindData.child(aBindPatchIndex).asInt();

    MPoint preDeformPoint = evaluateBezierPatch(preControlPoints[patchIdx], u, v);
    MPoint postDeformPoint = evaluateBezierPatch(controlPoints[patchIdx], u, v);

    return postDeformPoint - preDeformPoint;
}

MStatus bezierCage::bind(MDataBlock &dataBlock, MItGeometry &geometryIterator, const MMatrix &localToWorldMatrix,
                         unsigned int geometryIndex) {
    MStatus status;

    MArrayDataHandle dirtyArrayHandle = dataBlock.inputArrayValue(aDirty, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    status = dirtyArrayHandle.jumpToElement(geometryIndex);
    if (status == MS::kSuccess && !dirtyArrayHandle.inputValue().asBool()) {
#if DEBUG_LOG
        MGlobal::displayInfo(MString("Geometry at index ") + MString(std::to_string(geometryIndex).c_str()) + " is already bound.");
#endif
        return status;
    }

    auto controlPoints = getControlPoints(dataBlock);
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
            MPoint surfacePoint = evaluateBezierPatch(patchControlPoints, uv[0], uv[1]);

            if (double distance = currentWorldPosition.distanceTo(surfacePoint); distance < minDistance) {
                minDistance = static_cast<float>(distance);
                bindDistHandle.setFloat(minDistance);
                uvHandle.set2Float(uv[0], uv[1]);
                patchIdxHandle.setInt(patchIndex);
            }
            patchIndex++;
        }
    }

    vertexBindDataHandle.set(vertexBindDataBuilder);
    vertexBindDataHandle.setAllClean();
    geometryBindDataHandle.set(geometryBindDataBuilder);
    geometryBindDataHandle.setAllClean();

    MArrayDataBuilder dirtyBuilder = dirtyArrayHandle.builder(&status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    dirtyBuilder.addElement(geometryIndex).setBool(false);
    dirtyArrayHandle.set(dirtyBuilder);
    dirtyArrayHandle.setAllClean();

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
#if DEBUG_LOG
        MGlobal::displayInfo("Failed to read matrixArray");
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

    std::vector<MPoint> controlPoints;
    controlPoints.reserve(16);

    // Inserts the first 5 points (0-4) from the input (0-4)
    controlPoints.insert(controlPoints.end(), inputPoints.begin(), inputPoints.begin() + 5);

    // Computes and inserts interior point 5
    controlPoints.push_back(inputPoints[4] + (inputPoints[1] - inputPoints[0]));

    // Computes and inserts interior point 6
    controlPoints.push_back(inputPoints[5] + (inputPoints[2] - inputPoints[3]));

    // Inserts the next 2 points (7, 8) from the input (5, 6)
    controlPoints.insert(controlPoints.end(), inputPoints.begin() + 5, inputPoints.begin() + 7);

    // Computes and inserts interior point 9
    controlPoints.push_back(inputPoints[6] + (inputPoints[9] - inputPoints[8]));

    // Computes and inserts interior point 10
    controlPoints.push_back(inputPoints[7] + (inputPoints[10] - inputPoints[11]));

    // Inserts the last 5 points (11-15) from the input (7-11)
    controlPoints.insert(controlPoints.end(), inputPoints.begin() + 7, inputPoints.end());

    return controlPoints;
}

std::array<float, 2> bezierCage::findBindingUV(const std::vector<MPoint> &controlPoints,
                                               const MPoint &queryPoint) {
    // we just return 0.5, 0.5 for now, as this is the center of the patch
    return {0.5f, 0.5f};
}
