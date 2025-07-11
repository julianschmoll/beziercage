#include "offsetPin.hpp"
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MObject.h>
#include <maya/MStatus.h>
#include <maya/MArrayDataBuilder.h>
#include <maya/MFnMesh.h>
#include <maya/MFnIntArrayData.h>
#include <maya/MArrayDataHandle.h>
#include <maya/MMatrix.h>
#include <maya/MFloatArray.h>
#include <maya/MFnMeshData.h>
#include <maya/MPoint.h>
#include <maya/MMeshIntersector.h>

#include "common.hpp"

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
 bind(data);
 setOutput(data);
 data.setClean(plug);
 return MS::kSuccess;
}

MStatus offsetPin::buildGeometryLookup(MDataBlock &data) {
 MArrayDataHandle originalGeometryArray = data.inputArrayValue(aOriginalGeometry);
 MArrayDataHandle geoLookupArray = data.outputArrayValue(aGeometryLookup);

 if (geoLookupArray.elementCount() == originalGeometryArray.elementCount()) {
  return MS::kSuccess;
 }

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
 MArrayDataHandle inputMatrixArray = data.inputArrayValue(aInputMatrix);
 MArrayDataHandle bindDataArray = data.outputArrayValue(aBindData);

 for (unsigned int index = 0; index < inputMatrixArray.elementCount(); ++index) {
  inputMatrixArray.jumpToArrayElement(index);
  MMatrix matrix = inputMatrixArray.inputValue().asMatrix();

  if (bindDataArray.elementCount() > index) {
   bindDataArray.jumpToArrayElement(index);
   MMatrix bindMatrix = bindDataArray.inputValue().child(aBindMatrix).asMatrix();
   if (matrix.isEquivalent(bindMatrix, 1e-6)) {
    continue;
   }
  }
  calculateBinding(data, index);
 }
 return MS::kSuccess;
}

MStatus offsetPin::getTriangleVertexIndices(
 MArrayDataHandle &geoLookupArray,
 unsigned int geomIndex,
 int faceId,
 int triId,
 MIntArray &vertexIndices) const {
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
 if (status != MS::kSuccess) return status;

 MPlug origGeomPlug = fnNode.findPlug(aOriginalGeometry, false, &status);
 if (status != MS::kSuccess) return status;

 MPlug elemPlug = origGeomPlug.elementByLogicalIndex(geomIndex, &status);
 if (status != MS::kSuccess) return status;

 MPlugArray connections;
 elemPlug.connectedTo(connections, true, false, &status);
 if (status != MS::kSuccess || connections.length() == 0) return MS::kFailure;

 MObject inputNode = connections[0].node();
 if (!inputNode.hasFn(MFn::kMesh)) return MS::kFailure;

 MFnDagNode dagNode(inputNode, &status);
 if (status != MS::kSuccess) return status;

 status = dagNode.getPath(dagPath);
 return status;
}

MStatus offsetPin::calculateBinding(MDataBlock &data, unsigned int index) {
 DEBUG_MSG("Binding Geom Index: " << index);
 MArrayDataHandle inputMatrixArray = data.inputArrayValue(aInputMatrix);
 MArrayDataHandle inputGeometryArray = data.inputArrayValue(aInputGeometry);
 MArrayDataHandle geoLookupArray = data.outputArrayValue(aGeometryLookup);
 MArrayDataHandle bindDataArray = data.outputArrayValue(aBindData);
 MArrayDataBuilder bindDataBuilder = bindDataArray.builder();

 inputMatrixArray.jumpToArrayElement(index);
 MMatrix inputMatrix = inputMatrixArray.inputValue().asMatrix();
 MPoint inputPoint(inputMatrix[3][0], inputMatrix[3][1], inputMatrix[3][2]);

 double minDistance = std::numeric_limits<double>::max();
 unsigned int bestGeomIndex = 0;
 MPoint bestClosestPoint;
 MIntArray bestVertexIndices;
 MMatrix bestTriangleMatrix;
 MFloatArray bestBaryCoords;

 for (unsigned int geomIndex = 0; geomIndex < inputGeometryArray.elementCount(); ++geomIndex) {
  inputGeometryArray.jumpToArrayElement(geomIndex);
  MObject meshObj = inputGeometryArray.inputValue().asMesh();
  if (meshObj.isNull()) continue;

  MFnMesh fnMesh(meshObj);

  MDagPath dagPath;
  // this is nasty as we dont want to access other dag objects from
  // within the node but this way we can get the correct triangle id
  // as bind is not called regularly this is the best way to do it
  MStatus stat = GetOrigGeomPathFromPlug(geomIndex, dagPath);
  if (stat != MS::kSuccess) continue;

  MMatrix worldMatrix = dagPath.inclusiveMatrix();
  MMeshIntersector intersector;
  stat = intersector.create(dagPath.node(), worldMatrix);
  if (stat != MS::kSuccess) continue;

  MPointOnMesh pointOnMesh;
  intersector.getClosestPoint(inputPoint, pointOnMesh);

  int faceId = pointOnMesh.faceIndex();
  int triId = pointOnMesh.triangleIndex();
  MPoint pointOnMeshPoint = pointOnMesh.getPoint();
  MPoint closestPoint = pointOnMeshPoint * worldMatrix;

  double distance = (closestPoint - inputPoint).length();
  if (distance < minDistance) {
   minDistance = distance;
   bestGeomIndex = geomIndex;
   bestClosestPoint = closestPoint;

   getTriangleVertexIndices(geoLookupArray, geomIndex, faceId, triId, bestVertexIndices);

   MPoint A, B, C;
   fnMesh.getPoint(bestVertexIndices[0], A, MSpace::kWorld);
   fnMesh.getPoint(bestVertexIndices[1], B, MSpace::kWorld);
   fnMesh.getPoint(bestVertexIndices[2], C, MSpace::kWorld);

   RotationMatrixFromTri(A, B, C, bestTriangleMatrix);

   GetBarycentricCoordinates(bestClosestPoint, A, B, C, bestBaryCoords);
  }
 }

 MDataHandle bindElem = bindDataBuilder.addElement(index);
 bindElem.child(aBindMatrix).setMMatrix(inputMatrix);
 bindElem.child(aBindTriangleMatrix).setMMatrix(bestTriangleMatrix);
 bindElem.child(aBindDistance).setDouble(minDistance);
 bindElem.child(aBindCoordinates).set3Double(
  bestBaryCoords[0],
  bestBaryCoords[1],
  bestBaryCoords[2]
 );
 bindElem.child(aBindVertexIndices).set3Int(
  bestVertexIndices[0],
  bestVertexIndices[1],
  bestVertexIndices[2]
 );
 bindElem.child(aBindGeomIndex).setInt(bestGeomIndex);

 bindDataArray.set(bindDataBuilder);

 DEBUG_MSG(
  "BestVertexIndices: " << bestVertexIndices[0] << ", " << bestVertexIndices[1] << ", " << bestVertexIndices[2]);
 DEBUG_MSG(
  "BestClosestPoint: (" << bestClosestPoint.x << ", " << bestClosestPoint.y << ", " << bestClosestPoint.z << ")");
 DEBUG_MSG("BestBaryCoords: " << bestBaryCoords[0] << ", " << bestBaryCoords[1] << ", " << bestBaryCoords[2]);

 return MS::kSuccess;
}

MStatus offsetPin::setOutput(MDataBlock &data) {
 return MS::kSuccess;
}
