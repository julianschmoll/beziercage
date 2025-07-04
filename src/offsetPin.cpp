#include "offsetPin.hpp"
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MObject.h>
#include <maya/MStatus.h>

MTypeId offsetPin::id(0x001226C2);
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

void *offsetPin::creator() {
 return new offsetPin();
}

MStatus offsetPin::initialize() {
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
 if (status != MS::kSuccess) return status;

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
 if (status != MS::kSuccess) return status;

 // --- Output Matrix ---
 aOutputMatrix = mAttr.create("outputMatrix", "outMat");
 mAttr.setArray(true);
 mAttr.setKeyable(false);
 mAttr.setReadable(true);
 mAttr.setWritable(false);
 mAttr.setUsesArrayDataBuilder(true);

 status = addAttribute(aOutputMatrix);
 if (status != MS::kSuccess) return status;

 // --- Input Matrix ---
 aInputMatrix = mAttr.create("inputMatrix", "inMat");
 mAttr.setArray(true);
 mAttr.setReadable(false);
 mAttr.setKeyable(false);
 mAttr.setWritable(true);

 status = addAttribute(aInputMatrix);
 if (status != MS::kSuccess) return status;

 // --- Input Geometry ---
 aInputGeometry = tAttr.create("inputGeometry", "inGeom", MFnData::kMesh);
 tAttr.setArray(true);
 tAttr.setKeyable(false);
 tAttr.setWritable(true);
 tAttr.setReadable(false);

 status = addAttribute(aInputGeometry);
 if (status != MS::kSuccess) return status;

 // --- Original Geometry ---
 aOriginalGeometry = tAttr.create("originalGeometry", "origGeom", MFnData::kMesh);
 tAttr.setArray(true);
 tAttr.setKeyable(false);
 tAttr.setWritable(true);
 tAttr.setReadable(false);

 status = addAttribute(aOriginalGeometry);
 if (status != MS::kSuccess) return status;

 // --- Attribute Dependencies ---
 attributeAffects(aInputMatrix, aOutputMatrix);
 attributeAffects(aInputGeometry, aOutputMatrix);
 attributeAffects(aOriginalGeometry, aOutputMatrix);

 return MS::kSuccess;
}

MStatus offsetPin::compute(const MPlug &plug, MDataBlock &data) {
 if (plug != aOutputMatrix) { return MS::kUnknownParameter; }
 buildGeometryLookup(data);
 calculateBinding(data, 0);
 setOutput(data);
 data.setClean(plug);
 return MS::kSuccess;
}

void offsetPin::buildGeometryLookup(MDataBlock &data) {
 // TODO: Implement :)
}

void offsetPin::calculateBinding(MDataBlock &data, unsigned int index) {
 // TODO: Implement :)
}

void offsetPin::setOutput(MDataBlock &data) {
 // TODO: Implement :)
}
