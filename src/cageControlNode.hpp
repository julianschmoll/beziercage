#ifndef CAGE_CONTROL_NODE_H
#define CAGE_CONTROL_NODE_H

#include <maya/MPxNode.h>
#include <maya/MTypeId.h>
#include <maya/MArrayDataHandle.h>
#include <maya/MMatrix.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MGlobal.h>
#include <maya/MPointArray.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MVector.h>
#include <maya/MFnMesh.h>

#include <array>
#include <vector>

struct Face {
    std::vector<int> vertices;
    std::vector<std::array<int,3>> triangles;
};

struct MeshData {
    MPointArray vertices;
    MFloatVectorArray normals;
    std::vector<Face> faces;
};

struct BindData {
    std::array<int,3> vertexIdxs;
    std::array<double,3> barycentricCoords;
    MMatrix rotationMatrix;
    double closestPointDistance;
    unsigned int geomIndex;
    MVector offsetVector;
};

class CageControlNode : public MPxNode {
public:
    CageControlNode();
    ~CageControlNode() override;
    MStatus compute(const MPlug& plug, MDataBlock& data) override;
    static void* creator();
    static MStatus initialize();

    static MTypeId   id;
    static MObject   aInputMatrix;
    static MObject   aInputGeometry;
    static MObject   aOriginalGeometry;
    static MObject   aOutputMatrix;

private:
    void buildTriangleLookup(MDataBlock& data);
    void calculateBinding(MDataBlock& data);
    void setOutputMatrix(MDataBlock& data);

    std::vector<MeshData> meshData;
    std::vector<BindData> bindData;
};

#endif
