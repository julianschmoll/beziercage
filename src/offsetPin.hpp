#pragma once

#include <maya/MPxNode.h>
#include <maya/MTypeId.h>
#include <maya/MObject.h>
#include <maya/MStatus.h>
#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MThreadPool.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnCompoundAttribute.h>

class offsetPin : public MPxNode {
public:
    offsetPin() = default;

    ~offsetPin() override = default;

    static void *creator();

    static MStatus initialize();

    MStatus compute(const MPlug &plug, MDataBlock &data) override;

    static MTypeId id;
    static const char *typeName;

    // Input/Output Attributes
    static MObject aOutputMatrix;
    static MObject aInputMatrix;
    static MObject aInputGeometry;
    static MObject aOriginalGeometry;

    // Bind Data
    static MObject aBindData;
    static MObject aBindMatrix;
    static MObject aBindTriangleMatrix;
    static MObject aBindDistance;
    static MObject aBindCoordinates;
    static MObject aBindVertexIndices;
    static MObject aBindOffsetVector;
    static MObject aBindGeomIndex;

    // Geometry Lookup
    static MObject aGeometryLookup;
    static MObject aFaceVertices;

private:
    static MStatus buildGeometryLookup(MDataBlock &data);

    MStatus bind(MDataBlock &data);

    MStatus getVertexIndices(MDataBlock &data, unsigned int geoID, unsigned int faceID, unsigned int triangleID);

    MStatus GetBindMesh(unsigned int geoID);

    MStatus calculateBinding(MDataBlock &data, unsigned int index);

    MStatus setOutput(MDataBlock &data);

    MStatus getTriangleVertexIndices(MArrayDataHandle &geoLookupArray, unsigned int geomIndex, int faceId, int triId, MIntArray &vertexIndices) const;
};
