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
    /**
     * Matches the length of bind pre matrices array to the patch matrices array.
     * @param[in,out] dataBlock The data block of the deformer.
     * @return MStatus indicating success or failure.
     */
    static MStatus updateBindPreMatrixPlugs(MDataBlock &dataBlock);

    static std::vector<std::vector<MPoint> > getControlPoints(MDataBlock &dataBlock, bool preDeform = false);

    static MVector getDeformVector(MDataBlock &dataBlock, const std::vector<std::vector<MPoint> > &controlPoints,
                                   const std::vector<std::vector<MPoint> > &preControlPoints, unsigned int vertexIndex,
                                   unsigned int geometryIndex);

    /**
     * Binds the geometry to the cage.
     * @param[in,out] dataBlock The data block of the deformer.
     * @param[in,out] geometryIterator The geometry iterator for the deformed geometry.
     * @param[in] localToWorldMatrix The local to world matrix for the geometry.
     * @param[in] geometryIndex The index of the geometry being deformed.
     * @return MStatus indicating success or failure.
     */
    static MStatus bind(MDataBlock &dataBlock, MItGeometry &geometryIterator, const MMatrix &localToWorldMatrix,
                        unsigned int geometryIndex);

    static void connectionMonitorCallback(MPlug &srcPlug, MPlug &destPlug, bool made, void *clientData);

    static std::array<float, 2> findBindingUV(const std::vector<MPoint> &controlPoints,
                                              const MPoint &queryPoint);

    static std::vector<MPoint> getPatchPoints(MArrayDataHandle &matrixArray);
};
