#include "cageDeformer.hpp"

#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMessageAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MGlobal.h>
#include <maya/MArrayDataBuilder.h>
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

    return MS::kSuccess;
}

void *bezierCage::creator() {
    return new bezierCage();
}


MStatus bezierCage::deform(MDataBlock &dataBlock, MItGeometry &geometryIterator, const MMatrix &localToWorldMatrix,
                           unsigned int geometryIndex) {
    updateBindPreMatrixPlugs(dataBlock);
    float fEnvelope = dataBlock.inputValue(envelope).asFloat();
    if (fEnvelope == 0.0f) { return MS::kSuccess; }

    if (bind(dataBlock, geometryIterator, localToWorldMatrix, geometryIndex) == false) {
        return MS::kFailure;
    }

    return MS::kSuccess;
}

bool bezierCage::bind(MDataBlock &dataBlock, MItGeometry &geometryIterator, const MMatrix &localToWorldMatrix,
                      unsigned int geometryIndex) {
    return true;
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
