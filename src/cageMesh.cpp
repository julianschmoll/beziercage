#include "cageMesh.hpp"

MObject animCube::time;
MObject animCube::outputMesh;
MTypeId animCube::id(0x80000);

void* animCube::creator()
{
    return new animCube;
}

MStatus animCube::initialize()
{
    MFnUnitAttribute unitAttr;
    MFnTypedAttribute typedAttr;
    MStatus returnStatus;
    animCube::time = unitAttr.create( "time", "tm",
                                          MFnUnitAttribute::kTime,
                                          0.0, &returnStatus );
    CHECK_MSTATUS_AND_RETURN_IT(returnStatus);
    animCube::outputMesh = typedAttr.create( "outputMesh", "out", MFnData::kMesh, &returnStatus ); 
    CHECK_MSTATUS_AND_RETURN_IT(returnStatus);
    typedAttr.setStorable(false);
    returnStatus = addAttribute(animCube::time);
    CHECK_MSTATUS_AND_RETURN_IT(returnStatus);
    returnStatus = addAttribute(animCube::outputMesh);
    CHECK_MSTATUS_AND_RETURN_IT(returnStatus);
    returnStatus = attributeAffects(animCube::time,
                                    animCube::outputMesh);
    CHECK_MSTATUS_AND_RETURN_IT(returnStatus);
    return MS::kSuccess;
}

MObject animCube::createMesh(const MTime& time,
                              MObject& outData,
                              MStatus& stat)
{
    // Scale the cube on the frame number, wrap every 10 frames.
    //
    const int frame = (int)time.as( MTime::kFilm );
    const float cubeSize = 0.5f * (float)( frame % 10 + 1 );
    MFloatPointArray points;
    points.append( -cubeSize, -cubeSize, -cubeSize );
    points.append(  cubeSize, -cubeSize, -cubeSize );
    points.append(  cubeSize, -cubeSize,  cubeSize );
    points.append( -cubeSize, -cubeSize,  cubeSize );
    points.append( -cubeSize,  cubeSize, -cubeSize );
    points.append( -cubeSize,  cubeSize,  cubeSize );
    points.append(  cubeSize,  cubeSize,  cubeSize );
    points.append(  cubeSize,  cubeSize, -cubeSize );
    MObject newMesh;
    static const bool sTestVertexIdAndFaceId =
        (getenv("MAYA_TEST_VERTEXID_AND_FACEID") != NULL);
    if (sTestVertexIdAndFaceId)
    {
        // If the env var is set, the topology of the cube will be changed over
        // frame number (looping in every 4 frames). When the shape is assigned
        // with a hwPhongShader, the shader receives vertex ids and face ids,
        // which are generated from polygonConnects passed to MFnMesh::create
        // method in this plugin.
        //
        switch (frame % 4)
        {
        case 1:
            newMesh = createQuads(points, outData, stat);
            break;
        case 2:
            newMesh = createReverseQuads(points, outData, stat);
            break;
        case 3:
            newMesh = createTris(points, outData, stat);
            break;
        case 0:
            newMesh = createReverseTris(points, outData, stat);
            break;
        default:
            newMesh = createQuads(points, outData, stat);
            break;
        }
    }
    else
    {
        newMesh = createQuads(points, outData, stat);
    }
    return newMesh;
}

MObject animCube::createQuads(
    const MFloatPointArray& points,
    MObject& outData,
    MStatus& stat)
{
    // Set up an array containing the number of vertices
    // for each of the 6 cube faces (4 vertices per face)
    //
    const int numFaces = 6;
    int face_counts[numFaces] = { 4, 4, 4, 4, 4, 4 };
    MIntArray faceCounts( face_counts, numFaces );
    // Set up and array to assign vertices from points to each face 
    //
    const int numFaceConnects = 24;
    int face_connects[ numFaceConnects ] = {0, 1, 2, 3,
                                            4, 5, 6, 7,
                                            3, 2, 6, 5,
                                            0, 3, 5, 4,
                                            0, 4, 7, 1,
                                            1, 7, 6, 2};
    MIntArray faceConnects( face_connects, numFaceConnects );
    
    MFnMesh meshFS;
    return meshFS.create(points.length(), faceCounts.length(),
        points, faceCounts, faceConnects, outData, &stat);
}

MObject animCube::createReverseQuads(
    const MFloatPointArray& points,
    MObject& outData,
    MStatus& stat)
{
    // Set up an array containing the number of vertices
    // for each of the 6 cube faces (4 vertices per face)
    //
    const int numFaces = 6;
    int face_counts[numFaces] = { 4, 4, 4, 4, 4, 4 };
    MIntArray faceCounts( face_counts, numFaces );
    // Set up and array to assign vertices from points to each face
    //
    const int numFaceConnects = 24;
    int face_connects[ numFaceConnects ] = {0, 3, 2, 1,
                                            4, 7, 6, 5,
                                            3, 5, 6, 2,
                                            0, 4, 5, 3,
                                            0, 1, 7, 4,
                                            1, 2, 6, 7};
    MIntArray faceConnects( face_connects, numFaceConnects );
    MFnMesh meshFS;
    return meshFS.create(points.length(), faceCounts.length(),
        points, faceCounts, faceConnects, outData, &stat);
}

MObject animCube::createTris(
    const MFloatPointArray& points,
    MObject& outData,
    MStatus& stat)
{
    // Set up an array containing the number of vertices
    // for each of the 12 triangles (3 verticies per triangle)
    //
    const int numFaces = 12;
    int face_counts[numFaces] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
    MIntArray faceCounts( face_counts, numFaces );
    // Set up and array to assign vertices from points to each face
    //
    const int numFaceConnects = 36;
    int face_connects[ numFaceConnects ] = {0, 1, 2,
                                            2, 3, 0,
                                            4, 5, 6,
                                            6, 7, 4,
                                            3, 2, 6,
                                            6, 5, 3,
                                            0, 3, 5,
                                            5, 4, 0,
                                            0, 4, 7,
                                            7, 1, 0,
                                            1, 7, 6,
                                            6, 2, 1};
    MIntArray faceConnects( face_connects, numFaceConnects );
    MFnMesh meshFS;
    return meshFS.create(points.length(), faceCounts.length(),
        points, faceCounts, faceConnects, outData, &stat);
}

MObject animCube::createReverseTris(
    const MFloatPointArray& points,
    MObject& outData,
    MStatus& stat)
{
    // Set up an array containing the number of vertices
    // for each of the 12 triangles (3 verticies per triangle)
    //
    const int numFaces = 12;
    int face_counts[numFaces] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
    MIntArray faceCounts( face_counts, numFaces );
    // Set up and array to assign vertices from points to each face
    //
    const int numFaceConnects = 36;
    int face_connects[ numFaceConnects ] = {0, 2, 1,
                                            2, 0, 3,
                                            4, 6, 5,
                                            6, 4, 7,
                                            3, 6, 2,
                                            6, 3, 5,
                                            0, 5, 3,
                                            5, 0, 4,
                                            0, 7, 4,
                                            7, 0, 1,
                                            1, 6, 7,
                                            6, 1, 2};
    MIntArray faceConnects( face_connects, numFaceConnects );
    MFnMesh meshFS;
    return meshFS.create(points.length(), faceCounts.length(),
        points, faceCounts, faceConnects, outData, &stat);
}

MStatus animCube::compute(const MPlug& plug, MDataBlock& data)
{
    MStatus returnStatus;
    if (plug == outputMesh) {
        /* Get time */
        MDataHandle timeData = data.inputValue( time, &returnStatus ); 
        CHECK_MSTATUS_AND_RETURN_IT(returnStatus);
        MTime time = timeData.asTime();
        /* Get output object */
        MDataHandle outputHandle = data.outputValue(outputMesh, &returnStatus);
        CHECK_MSTATUS_AND_RETURN_IT(returnStatus);
        MFnMeshData dataCreator;
        MObject newOutputData = dataCreator.create(&returnStatus);
        CHECK_MSTATUS_AND_RETURN_IT(returnStatus);
        createMesh(time, newOutputData, returnStatus);
        CHECK_MSTATUS_AND_RETURN_IT(returnStatus);
        outputHandle.set(newOutputData);
        data.setClean( plug );
    } else
        return MS::kUnknownParameter;
    return MS::kSuccess;
}
