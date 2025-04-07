#ifndef cageMESH_HPP
#define cageMESH_HPP

#include <maya/MTime.h>
#include <maya/MFnMesh.h>
#include <maya/MPoint.h>
#include <maya/MFloatPoint.h>
#include <maya/MFloatPointArray.h>
#include <maya/MIntArray.h>
#include <maya/MDoubleArray.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MPxNode.h>
#include <maya/MObject.h>
#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MFnMeshData.h>
#include <maya/MIOStream.h>

class animCube : public MPxNode
{
public:
    animCube() {};
    ~animCube() override {};
    MStatus compute(const MPlug& plug, MDataBlock& data) override;
    static  void*   creator();
    static MStatus initialize();
    static MObject  time;
    static MObject  outputMesh;
    static MTypeId  id;
protected:
    MObject createMesh(const MTime& time, MObject& outData, MStatus& stat);
    // Helpers
    MObject createQuads(const MFloatPointArray& points, MObject& outData, MStatus& stat);
    MObject createReverseQuads(const MFloatPointArray& points, MObject& outData, MStatus& stat);
    MObject createTris(const MFloatPointArray& points, MObject& outData, MStatus& stat);
    MObject createReverseTris(const MFloatPointArray& points, MObject& outData, MStatus& stat);
};

#endif