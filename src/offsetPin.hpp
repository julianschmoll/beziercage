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
    /**
     * Builds a lookup table for the original geometry to store face vertices.
     * @param[in,out] data The data block containing input and output values.
     * @return MStatus indicating success or failure.
     */
    static MStatus buildGeometryLookup(MDataBlock &data);

    /**
     * Calculates the binding of input matrix to the original geometry.
     * @param[in,out] data The data block containing input and output values.
     * @return MStatus indicating success or failure.
     */
    MStatus bind(MDataBlock &data);

    /**
     * Generates bind data for a specific mesh based on the closest point.
     * @param[in,out] data The data block containing input and output values.
     * @param[in] index Index of the matrix to bind.
     * @return MStatus indicating success or failure.
     */
    MStatus calculateBinding(MDataBlock &data, unsigned int index);

    /**
     * Sets the output matrix plug based on the binding data.
     * @param[in,out] data The data block containing input and output values.
     * @return MStatus indicating success or failure.
     */
    static MStatus setOutput(MDataBlock &data);

    /**
     * Retrieves the vertex indices of a triangle in a specific geometry.
     * @param[in] geoLookupArray The geometry lookup array handle.
     * @param[in] geomIndex Index of the geometry in the geometryLookup attribute.
     * @param[in] faceId Index of the face in the geometry.
     * @param[in] triId Index of the triangle within the face.
     * @param[out] vertexIndices The array to be filled with vertex indices.
     * @return MStatus indicating success or failure.
     */
    static MStatus getTriangleVertexIndices(MArrayDataHandle &geoLookupArray, unsigned int geomIndex, int faceId,
                                            int triId,
                                            MIntArray &vertexIndices);

    /**
    * Creates an intermediate object at dagPath for binding.
    * @param[in] geomIndex Index of the geometry.
    * @param[out] dagPath The MDagPath.
    * @return MStatus indicating success or failure.
    */
    MStatus CreateBindGeom(unsigned int geomIndex, MDagPath &dagPath);

    /**
     * Calculates the output matrix based on barycentric coordinates and triangle data.
     * @param[in] baryCoords Barycentric coordinates of the point in the triangle.
     * @param[in] A First vertex of the triangle.
     * @param[in] B Second vertex of the triangle.
     * @param[in] C Third vertex of the triangle.
     * @param[in] bindTriangleMatrix Transformation matrix of the triangle.
     * @param[in] offsetVector Optional offset vector to apply to the output position.
     * @return MMatrix representing the output position in world space.
     */
    static MMatrix calculateOutputMatrix(
        const MFloatArray &baryCoords,
        const MPoint &A,
        const MPoint &B,
        const MPoint &C,
        const MMatrix &bindTriangleMatrix,
        const MVector *offsetVector = nullptr
    );
};
