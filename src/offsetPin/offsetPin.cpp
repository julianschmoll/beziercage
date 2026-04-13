#include "offsetPin.hpp"
#include <maya/MArrayDataBuilder.h>
#include <maya/MArrayDataHandle.h>
#include <maya/MFloatArray.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnIntArrayData.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnMesh.h>
#include <maya/MFnMeshData.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MMatrix.h>
#include <maya/MMeshIntersector.h>
#include <maya/MObject.h>
#include <maya/MPoint.h>
#include <maya/MStatus.h>

#include "common.hpp"
#include <limits>
#include <memory>
#include <thread>

// This ID is registered with Autodesk (https://adndata.autodesk.io/maya).
MTypeId offsetPin::id(0x0013f8c0);
const char *offsetPin::typeName = "offsetPin";

MObject offsetPin::aOutputMatrix;
MObject offsetPin::aInputMatrix;
MObject offsetPin::aInputGeometry;
MObject offsetPin::aOriginalGeometry;

MObject offsetPin::aBindData;
MObject offsetPin::aBindMatrix;
MObject offsetPin::aBindTriangleMatrix;
MObject offsetPin::aBindDistance;
MObject offsetPin::aBindCoordinates;
MObject offsetPin::aBindVertexIndices;
MObject offsetPin::aBindOffsetVector;
MObject offsetPin::aBindGeomIndex;

MObject offsetPin::aGeometryLookup;
MObject offsetPin::aFaceVertices;

offsetPin::offsetPin() : MTaskData() {
    unsigned int kTaskCount = std::thread::hardware_concurrency();
    if (kTaskCount == 0) {
        kTaskCount = 1;
    }
#if DEBUG_LOG
    MGlobal::displayInfo(MString("Using ") + kTaskCount + " threads for offsetPin node.");
#endif
    MThreadData.resize(kTaskCount);
}

void *offsetPin::creator() {
    return new offsetPin();
}

MStatus offsetPin::initialize() {
#if INFO_LOG
    MGlobal::displayInfo("Initializing offsetPin node");
#endif
    MFnMatrixAttribute mAttr;
    MFnNumericAttribute nAttr;
    MFnTypedAttribute tAttr;
    MFnCompoundAttribute cAttrBind;
    MFnCompoundAttribute cAttrGeom;
    MStatus status;

    // --- Bind Data Compound ---
    aBindData = cAttrBind.create("bindData", "bindData");
    cAttrBind.setArray(true);
    cAttrBind.setStorable(true);
    cAttrBind.setReadable(false);
    cAttrBind.setHidden(true);
    cAttrBind.setConnectable(false);
    cAttrBind.setUsesArrayDataBuilder(true);

    aBindMatrix = mAttr.create("bindMatrix", "bindMat");
    cAttrBind.addChild(aBindMatrix);

    aBindTriangleMatrix = mAttr.create("bindTriangleMatrix", "bindTriMat");
    cAttrBind.addChild(aBindTriangleMatrix);

    aBindDistance = nAttr.create("bindDistance", "bindDist", MFnNumericData::kDouble, 0.0);
    cAttrBind.addChild(aBindDistance);

    aBindCoordinates = nAttr.create("bindCoordinates", "bindCoords", MFnNumericData::k3Double);
    cAttrBind.addChild(aBindCoordinates);

    aBindVertexIndices = nAttr.create("bindVertexIndices", "bindVertIdx", MFnNumericData::k3Long);
    cAttrBind.addChild(aBindVertexIndices);

    aBindOffsetVector = nAttr.create("bindOffsetVector", "bindOff", MFnNumericData::k3Double);
    cAttrBind.addChild(aBindOffsetVector);

    aBindGeomIndex = nAttr.create("bindGeomIndex", "bindGeom", MFnNumericData::kInt, 0);
    cAttrBind.addChild(aBindGeomIndex);

    status = addAttribute(aBindData);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    // --- Geometry Lookup Compound ---
    aGeometryLookup = cAttrGeom.create("geometryLookup", "geomLookup");
    cAttrGeom.setArray(true);
    cAttrGeom.setStorable(true);
    cAttrGeom.setReadable(false);
    cAttrGeom.setHidden(true);
    cAttrGeom.setConnectable(false);
    cAttrGeom.setUsesArrayDataBuilder(true);

    aFaceVertices = tAttr.create("faceVertices", "faceVertices", MFnData::kIntArray);
    tAttr.setArray(true);
    cAttrGeom.addChild(aFaceVertices);

    status = addAttribute(aGeometryLookup);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    // --- Output Matrix ---
    aOutputMatrix = mAttr.create("outputMatrix", "outMat");
    mAttr.setArray(true);
    mAttr.setKeyable(false);
    mAttr.setReadable(true);
    mAttr.setWritable(false);
    mAttr.setUsesArrayDataBuilder(true);

    status = addAttribute(aOutputMatrix);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    // --- Input Matrix ---
    aInputMatrix = mAttr.create("inputMatrix", "inMat");
    mAttr.setArray(true);
    mAttr.setReadable(false);
    mAttr.setKeyable(false);
    mAttr.setWritable(true);

    status = addAttribute(aInputMatrix);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    // --- Input Geometry ---
    aInputGeometry = tAttr.create("inputGeometry", "inGeom", MFnData::kMesh);
    tAttr.setArray(true);
    tAttr.setKeyable(false);
    tAttr.setWritable(true);
    tAttr.setReadable(false);

    status = addAttribute(aInputGeometry);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    // --- Original Geometry ---
    aOriginalGeometry = tAttr.create("originalGeometry", "origGeom", MFnData::kMesh);
    tAttr.setArray(true);
    tAttr.setKeyable(false);
    tAttr.setWritable(true);
    tAttr.setReadable(false);

    status = addAttribute(aOriginalGeometry);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    // --- Attribute Dependencies ---
    attributeAffects(aInputMatrix, aOutputMatrix);
    attributeAffects(aInputGeometry, aOutputMatrix);
    attributeAffects(aOriginalGeometry, aOutputMatrix);

    return MS::kSuccess;
}

MStatus offsetPin::compute(const MPlug &plug, MDataBlock &data) {
    MStatus status;
#if DEBUG_LOG
    MGlobal::displayInfo(MString("Recomputation was requested for plug: ") + plug.name());
#endif
    if (plug != aOutputMatrix) {
        return MS::kUnknownParameter;
    }
    buildGeometryLookup(data);
    status = bind(data);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    setOutput(data);
    data.setClean(plug);
    return status;
}

MStatus offsetPin::buildGeometryLookup(MDataBlock &data) {
    MArrayDataHandle originalGeometryArray = data.inputArrayValue(aOriginalGeometry);
    MArrayDataHandle geoLookupArray = data.outputArrayValue(aGeometryLookup);

    if (geoLookupArray.elementCount() == originalGeometryArray.elementCount()) {
        return MS::kSuccess;
    }

#if INFO_LOG
    MGlobal::displayInfo("Building geometry lookup");
#endif

    MArrayDataBuilder geoBuilder = geoLookupArray.builder();
    MIntArray triCounts, triVertices;

    for (unsigned int geomIndex = 0; geomIndex < originalGeometryArray.elementCount(); ++geomIndex) {
        originalGeometryArray.jumpToArrayElement(geomIndex);
        MObject meshObj = originalGeometryArray.inputValue().asMesh();

        if (meshObj.isNull()) {
            continue;
        }

        MFnMesh fnMesh(meshObj);
        fnMesh.getTriangles(triCounts, triVertices);

        MDataHandle geomElem = geoBuilder.addElement(geomIndex);
        MArrayDataHandle faceHandle = geomElem.child(aFaceVertices);
        MArrayDataBuilder faceBuilder = faceHandle.builder();

        int triIter = 0;
        MIntArray triangleIndices;
        MFnIntArrayData fnIntData;

        for (unsigned int faceId = 0, faceCount = triCounts.length(); faceId < faceCount; ++faceId) {
            int triCount = triCounts[faceId];
            triangleIndices.setLength(triCount * 3);

            for (int i = 0; i < triCount; ++i) {
                triangleIndices[i * 3] = triVertices[triIter];
                triangleIndices[i * 3 + 1] = triVertices[triIter + 1];
                triangleIndices[i * 3 + 2] = triVertices[triIter + 2];
                triIter += 3;
            }

            MObject intArrayObj = fnIntData.create(triangleIndices);
            MDataHandle faceElem = faceBuilder.addElement(faceId);
            faceElem.set(intArrayObj);
        }

        faceHandle.set(faceBuilder);
    }

    geoLookupArray.set(geoBuilder);
    geoLookupArray.setAllClean();

    return MS::kSuccess;
}

MStatus offsetPin::bind(MDataBlock &data) {
    MStatus status;
    MArrayDataHandle inputMatrixArray = data.inputArrayValue(aInputMatrix);
    MArrayDataHandle bindDataArray = data.outputArrayValue(aBindData);

    for (unsigned int index = 0; index < inputMatrixArray.elementCount(); ++index) {
        status = inputMatrixArray.jumpToArrayElement(index);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        MMatrix matrix = inputMatrixArray.inputValue(&status).asMatrix();
        CHECK_MSTATUS_AND_RETURN_IT(status);

        if (bindDataArray.elementCount() > index) {
            status = bindDataArray.jumpToArrayElement(index);
            CHECK_MSTATUS_AND_RETURN_IT(status);
            MMatrix bindMatrix = bindDataArray.inputValue(&status).child(aBindMatrix).asMatrix();
            CHECK_MSTATUS_AND_RETURN_IT(status);
            if (matrix.isEquivalent(bindMatrix, 1e-6)) {
                continue;
            }
#if INFO_LOG
            MGlobal::displayInfo(MString("Rebinding point at index: ") + MString(std::to_string(index).c_str()));
#endif
        }
        status = calculateBinding(data, index);
    }
    return status;
}

MStatus offsetPin::getTriangleVertexIndices(MArrayDataHandle &geoLookupArray, unsigned int geomIndex, int faceId, int triId,
                                            MIntArray &vertexIndices) {
    geoLookupArray.jumpToArrayElement(geomIndex);
    MArrayDataHandle faceHandle = geoLookupArray.inputValue().child(aFaceVertices);
    faceHandle.jumpToArrayElement(faceId);
    MObject intArrayObj = faceHandle.inputValue().data();
    MFnIntArrayData fnIntData(intArrayObj);
    MIntArray allIndices = fnIntData.array();

    vertexIndices.setLength(3);
    vertexIndices[0] = allIndices[triId * 3];
    vertexIndices[1] = allIndices[triId * 3 + 1];
    vertexIndices[2] = allIndices[triId * 3 + 2];

    return MS::kSuccess;
}

MStatus offsetPin::GetOrigGeomPathFromPlug(unsigned int geomIndex, MDagPath &dagPath) {
    MStatus status;
    MFnDependencyNode fnNode(thisMObject(), &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MPlug origGeomPlug = fnNode.findPlug(aOriginalGeometry, false, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MPlug elemPlug = origGeomPlug.elementByLogicalIndex(geomIndex, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MPlugArray connections;
    elemPlug.connectedTo(connections, true, false, &status);
    if (status != MS::kSuccess || connections.length() <= 0) {
#if ERROR_LOG
        MGlobal::displayInfo("No connections found on original geometry plug.");
#endif
        return MS::kFailure;
    }

    MObject inputNode = connections[0].node();
    if (!inputNode.hasFn(MFn::kMesh))
        return MS::kFailure;

    MFnDagNode dagNode(inputNode, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    status = dagNode.getPath(dagPath);
    return status;
}

MStatus offsetPin::calculateBinding(MDataBlock &data, unsigned int index) {
    MStatus status;
#if DEBUG_LOG
    MGlobal::displayInfo("Calculating binding for index: " + MString(std::to_string(index).c_str()));
#endif
    MArrayDataHandle inputMatrixArray = data.inputArrayValue(aInputMatrix, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MArrayDataHandle inputGeometryArray = data.inputArrayValue(aInputGeometry, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MArrayDataHandle geoLookupArray = data.outputArrayValue(aGeometryLookup, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MArrayDataHandle bindDataArray = data.outputArrayValue(aBindData, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MArrayDataBuilder bindDataBuilder = bindDataArray.builder(&status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    status = inputMatrixArray.jumpToArrayElement(index);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MMatrix inputMatrix = inputMatrixArray.inputValue(&status).asMatrix();
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MPoint inputPoint(inputMatrix[3][0], inputMatrix[3][1], inputMatrix[3][2]);

    double minDistance = std::numeric_limits<double>::max();
    unsigned int bestGeomIndex = 0;
    MPoint bestClosestPoint;
    MIntArray bestVertexIndices;
    MMatrix bestTriangleMatrix;
    MFloatArray bestBaryCoords;
    MPoint pointA, pointB, pointC, pointOnMeshPoint, closestPoint;
    MMatrix worldMatrix;
    MObject meshObj;
    MPointOnMesh pointOnMesh;

    for (unsigned int geomIndex = 0; geomIndex < inputGeometryArray.elementCount(); ++geomIndex) {
        status = inputGeometryArray.jumpToArrayElement(geomIndex);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        meshObj = inputGeometryArray.inputValue(&status).asMesh();
        CHECK_MSTATUS_AND_RETURN_IT(status);
        if (meshObj.isNull())
            continue;

        MFnMesh fnMesh(meshObj, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        MDagPath dagPath;
        // this is nasty as we don't want to access other dag objects from
        // within the node but this way we can get the correct triangle id
        // as bind is not called regularly this is the best way to do it
        status = GetOrigGeomPathFromPlug(geomIndex, dagPath);
        if (status != MS::kSuccess)
            continue;

        worldMatrix = dagPath.inclusiveMatrix(&status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        MMeshIntersector intersector;
        MObject node = dagPath.node();
        status = intersector.create(node, worldMatrix);
        if (status != MS::kSuccess)
            continue;

        intersector.getClosestPoint(inputPoint, pointOnMesh);

        int faceId = pointOnMesh.faceIndex();
        int triId = pointOnMesh.triangleIndex();
        pointOnMeshPoint = pointOnMesh.getPoint();
        closestPoint = pointOnMeshPoint * worldMatrix;

        double distance = (closestPoint - inputPoint).length();
        if (distance < minDistance) {
            minDistance = distance;
            bestGeomIndex = geomIndex;
            bestClosestPoint = closestPoint;

            getTriangleVertexIndices(geoLookupArray, geomIndex, faceId, triId, bestVertexIndices);

            fnMesh.getPoint(bestVertexIndices[0], pointA, MSpace::kWorld);
            fnMesh.getPoint(bestVertexIndices[1], pointB, MSpace::kWorld);
            fnMesh.getPoint(bestVertexIndices[2], pointC, MSpace::kWorld);

            RotationMatrixFromTri(pointA, pointB, pointC, bestTriangleMatrix);

            GetBarycentricCoordinates(bestClosestPoint, pointA, pointB, pointC, bestBaryCoords);
        }
    }

    CHECK_MSTATUS_AND_RETURN_IT(status);

    MDataHandle bindElem = bindDataBuilder.addElement(index);
    bindElem.child(aBindMatrix).setMMatrix(inputMatrix);
    bindElem.child(aBindTriangleMatrix).setMMatrix(bestTriangleMatrix);
    bindElem.child(aBindDistance).setDouble(minDistance);
    bindElem.child(aBindCoordinates).set3Double(bestBaryCoords[0], bestBaryCoords[1], bestBaryCoords[2]);
    bindElem.child(aBindVertexIndices).set3Int(bestVertexIndices[0], bestVertexIndices[1], bestVertexIndices[2]);
    bindElem.child(aBindGeomIndex).setInt(bestGeomIndex);

    inputGeometryArray.jumpToArrayElement(bestGeomIndex);
    meshObj = inputGeometryArray.inputValue().asMesh();
    MFnMesh fnMesh(meshObj);
    MMatrix deformMatrix = calculateOutputMatrix(bestBaryCoords, pointA, pointB, pointC, bestTriangleMatrix);
    MVector deformTranslation(deformMatrix[3][0], deformMatrix[3][1], deformMatrix[3][2]);
    MVector offsetVector = -deformTranslation;
    bindElem.child(aBindOffsetVector).set3Double(offsetVector.x, offsetVector.y, offsetVector.z);

    bindDataArray.set(bindDataBuilder);
    return status;
}

MMatrix offsetPin::calculateOutputMatrix(const MFloatArray &baryCoords, const MPoint &pointA, const MPoint &pointB, const MPoint &pointC,
                                         const MMatrix &bindTriangleMatrix, const MVector *offsetVector) {
    MVector interpolatedPosition = MVector(pointA) * baryCoords[0] + MVector(pointB) * baryCoords[1] + MVector(pointC) * baryCoords[2];
    MMatrix outputMatrix;
    RotationMatrixFromTri(pointA, pointB, pointC, outputMatrix);
    outputMatrix = bindTriangleMatrix.inverse() * outputMatrix;

    if (offsetVector) {
        // Transform offset vector to local space of the triangle
        MVector offset = (*offsetVector) * outputMatrix;
        outputMatrix[3][0] = interpolatedPosition.x + offset.x;
        outputMatrix[3][1] = interpolatedPosition.y + offset.y;
        outputMatrix[3][2] = interpolatedPosition.z + offset.z;
    } else {
        outputMatrix[3][0] = interpolatedPosition.x;
        outputMatrix[3][1] = interpolatedPosition.y;
        outputMatrix[3][2] = interpolatedPosition.z;
    }
    return outputMatrix;
}

MStatus offsetPin::setOutput(MDataBlock &data) {
    MArrayDataHandle inputMatrixArray = data.inputArrayValue(aInputMatrix);
    MArrayDataHandle bindDataArray = data.outputArrayValue(aBindData);
    MArrayDataHandle inputGeometryArray = data.inputArrayValue(aInputGeometry);
    MArrayDataHandle outputMatrixArray = data.outputArrayValue(aOutputMatrix);
    MArrayDataBuilder builder = outputMatrixArray.builder();

    std::vector<std::unique_ptr<MFnMesh>> meshCache(inputGeometryArray.elementCount());
    for (unsigned int geomIndex = 0; geomIndex < inputGeometryArray.elementCount(); ++geomIndex) {
        inputGeometryArray.jumpToArrayElement(geomIndex);
        MObject meshObj = inputGeometryArray.inputValue().asMesh();
        if (!meshObj.isNull()) {
            meshCache[geomIndex] = std::make_unique<MFnMesh>(meshObj);
        }
    }

    const unsigned int numMatrices = inputMatrixArray.elementCount();
    MTaskData.numMatrices = numMatrices;
    MTaskData.meshCache = &meshCache;
    MTaskData.vertexIndices.resize(numMatrices);
    MTaskData.baryCoords.resize(numMatrices);
    MTaskData.triMatrices.resize(numMatrices);
    MTaskData.offsetVectors.resize(numMatrices);
    MTaskData.geomIndices.resize(numMatrices);
    MTaskData.outputMatrices.resize(numMatrices);

    for (unsigned int index = 0; index < numMatrices; ++index) {
        if (bindDataArray.elementCount() <= index)
            continue;
        bindDataArray.jumpToArrayElement(index);

        MDataHandle bindElem = bindDataArray.inputValue();
        MIntArray vertexIndices(3);
        const int *vertPtr = bindElem.child(aBindVertexIndices).asInt3();
        vertexIndices[0] = vertPtr[0];
        vertexIndices[1] = vertPtr[1];
        vertexIndices[2] = vertPtr[2];
        MTaskData.vertexIndices[index] = vertexIndices;
        MFloatArray baryCoordsArr(3);
        const double *baryPtr = bindElem.child(aBindCoordinates).asDouble3();
        baryCoordsArr[0] = static_cast<float>(baryPtr[0]);
        baryCoordsArr[1] = static_cast<float>(baryPtr[1]);
        baryCoordsArr[2] = static_cast<float>(baryPtr[2]);
        MTaskData.baryCoords[index] = baryCoordsArr;
        MTaskData.triMatrices[index] = bindElem.child(aBindTriangleMatrix).asMatrix();
        MTaskData.offsetVectors[index] = bindElem.child(aBindOffsetVector).asVector();
        MTaskData.geomIndices[index] = bindElem.child(aBindGeomIndex).asInt();
    }
    CreateThreadData();
    MThreadPool::newParallelRegion(CreateTasks, static_cast<void *>(&MThreadData[0]));
    for (unsigned int index = 0; index < numMatrices; ++index) {
        MDataHandle elem = builder.addElement(index);
        elem.setMMatrix(MTaskData.outputMatrices[index]);
    }
    outputMatrixArray.set(builder);
    outputMatrixArray.setAllClean();
    return MS::kSuccess;
}

void offsetPin::CreateThreadData() {
    int taskCount = static_cast<int>(MThreadData.size());
    unsigned int taskLength = (MTaskData.numMatrices + taskCount - 1) / taskCount;
    unsigned int start = 0, end = taskLength;

    for (int i = 0; i < taskCount; ++i) {
        if (i == taskCount - 1) {
            end = MTaskData.numMatrices;
        }
        MThreadData[i] = {start, end, static_cast<unsigned int>(taskCount), &MTaskData};
        start += taskLength;
        end += taskLength;
    }
}

void offsetPin::CreateTasks(void *pData, MThreadRootTask *pRoot) {
    auto *pThreadData = static_cast<offsetPinThreadData *>(pData);
    const unsigned int taskCount = pThreadData[0].numTasks;

    for (unsigned int i = 0; i < taskCount; ++i) {
        MThreadPool::createTask(ThreadEvaluate, static_cast<void *>(&pThreadData[i]), pRoot);
    }
    MThreadPool::executeAndJoin(pRoot);
}

MThreadRetVal offsetPin::ThreadEvaluate(void *pParam) {
    const auto *threadData = static_cast<offsetPinThreadData *>(pParam);
    offsetPinTaskData *data = threadData->data;
    const auto &vertexIndices = data->vertexIndices;
    const auto &baryCoords = data->baryCoords;
    const auto &triMatrices = data->triMatrices;
    const auto &offsetVectors = data->offsetVectors;
    const auto &geomIndices = data->geomIndices;
    auto &outputMatrices = data->outputMatrices;
    const auto &meshCache = *data->meshCache;

    for (unsigned int index = threadData->start; index < threadData->end; ++index) {
        if (index >= data->numMatrices)
            continue;

        int geomIndex = geomIndices[index];
        if (geomIndex < 0 || geomIndex >= static_cast<int>(meshCache.size()))
            continue;

        MFnMesh *fnMesh = meshCache[geomIndex].get();
        if (!fnMesh)
            continue;

        MPoint pointA, pointB, pointC;
        fnMesh->getPoint(vertexIndices[index][0], pointA, MSpace::kWorld);
        fnMesh->getPoint(vertexIndices[index][1], pointB, MSpace::kWorld);
        fnMesh->getPoint(vertexIndices[index][2], pointC, MSpace::kWorld);

        outputMatrices[index] = calculateOutputMatrix(baryCoords[index], pointA, pointB, pointC, triMatrices[index], &offsetVectors[index]);
    }
    return 0;
}
