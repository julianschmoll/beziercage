#pragma once

#include <maya/MPxDeformerNode.h>
#include <maya/MTypeId.h>
#include <maya/MObject.h>
#include <maya/MDataBlock.h>
#include <maya/MItGeometry.h>
#include <maya/MMatrix.h>
#include <maya/MVector.h>
#include <maya/MPoint.h>
#include <maya/MPlug.h>
#include <vector>
#include <array>

class bezierCage : public MPxDeformerNode {
public:
    bezierCage() = default;

    ~bezierCage() override = default;

    static void *creator();

    static MStatus initialize();

    MStatus deform(MDataBlock &dataBlock, MItGeometry &geometryIterator, const MMatrix &localToWorldMatrix,
                   unsigned int geometryIndex) override;

    static MTypeId id;
    static const char *typeName;

    // Node attributes
    static MObject aControlMessage;
    static MObject aPatchMatrices;
    static MObject aMatrix;
    static MObject aBindPreMatrix;
    static MObject aPatchBindPreMatrices;
    static MObject aThreshDist;
    static MObject aBindUV;
    static MObject aBindDistance;
    static MObject aBindPatchIndex;
    static MObject aVertexBindPosition;
    static MObject aVertexBindData;
    static MObject aGeometryBindData;
    static MObject aDirty;

private:

    static MStatus updateBindPreMatrixPlugs(MDataBlock &dataBlock);

    static std::vector<std::vector<MPoint> > getControlPoints(MDataBlock &dataBlock, bool preMatrix = false);

    static MVector getDeformVector(MDataBlock &dataBlock, const std::vector<std::vector<MPoint> > &controlPoints,
                                   const std::vector<std::vector<MPoint> > &preControlPoints, unsigned int vertexIndex,
                                   unsigned int geometryIndex);

    bool bind(MDataBlock &dataBlock, MItGeometry &geometryIterator, const MMatrix &localToWorldMatrix,
              unsigned int geometryIndex);

    static void connectionMonitorCallback(MPlug &srcPlug, MPlug &destPlug, bool made, void *clientData);

    static std::array<float, 2> findBindingUV(const std::vector<std::vector<MPoint> > &controlPoints,
                                              const MPoint &queryPoint);

    static MPoint evaluateBezierPatch(const std::vector<std::vector<MPoint> > &controlPoints, float u, float v);

    static std::vector<MPoint> getPatchPoints(const MArrayDataHandle &matrixArray);

    static MPoint calculateInteriorPoint(const MPoint &point1, const MPoint &point2, const MPoint &point3);

    static MPoint deCasteljau(const std::vector<MPoint> &points, float t);

    static MPoint npEvaluateBezierPatch(const std::vector<std::vector<MPoint> > &controlPoints, float u, float v);
};
