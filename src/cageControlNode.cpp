#include <cfloat>

#include "CageControlNode.hpp"

MTypeId   CageControlNode::id(0x13f8c20);
MObject   CageControlNode::aInputMatrix;
MObject   CageControlNode::aInputGeometry;
MObject   CageControlNode::aOriginalGeometry;
MObject   CageControlNode::aOutputMatrix;

CageControlNode::CageControlNode() {}
CageControlNode::~CageControlNode() {}

void* CageControlNode::creator() {
    return new CageControlNode();
}

MStatus CageControlNode::initialize() {
    MFnMatrixAttribute mAttr;
    MFnTypedAttribute  tAttr;

    aInputMatrix = mAttr.create("inputMatrix", "inMat");
    mAttr.setArray(true);
    addAttribute(aInputMatrix);

    aInputGeometry = tAttr.create("inputGeometry", "inGeo", MFnData::kMesh);
    tAttr.setArray(true);
    addAttribute(aInputGeometry);

    aOriginalGeometry = tAttr.create("originalGeometry", "origGeo", MFnData::kMesh);
    tAttr.setArray(true);
    addAttribute(aOriginalGeometry);

    aOutputMatrix = mAttr.create("outputMatrix", "outMat");
    mAttr.setArray(true);
    mAttr.setWritable(false);
    addAttribute(aOutputMatrix);

    attributeAffects(aInputMatrix, aOutputMatrix);
    attributeAffects(aInputGeometry, aOutputMatrix);
    attributeAffects(aOriginalGeometry, aOutputMatrix);

    return MS::kSuccess;
}

MStatus CageControlNode::compute(const MPlug& plug, MDataBlock& data) {
    if (plug != aOutputMatrix) {
        return MS::kUnknownParameter;
    }
    buildTriangleLookup(data);
    calculateBinding(data);
    setOutputMatrix(data);
    return MS::kSuccess;
}

void CageControlNode::buildTriangleLookup(MDataBlock& data) {
    MArrayDataHandle origGeomArray = data.inputArrayValue(aOriginalGeometry);
    const unsigned int elementCount = origGeomArray.elementCount();

    if (meshData.size() == elementCount) {
        return;
    }

    meshData.clear();
    meshData.reserve(elementCount);

    for (unsigned int geomIndex = 0; geomIndex < elementCount; ++geomIndex) {
        origGeomArray.jumpToArrayElement(geomIndex);
        MObject meshObj = origGeomArray.inputValue().asMesh();
        MFnMesh fnMesh(meshObj);

        MeshData md;
        fnMesh.getPoints(md.vertices, MSpace::kWorld);
        fnMesh.getVertexNormals(false, md.normals, MSpace::kWorld);

        MIntArray faceVertexCounts, faceVertices;
        MIntArray triangleCounts, triangleVertices;
        fnMesh.getVertices(faceVertexCounts, faceVertices);
        fnMesh.getTriangles(triangleCounts, triangleVertices);

        int vertIter = 0;
        int triIter = 0;
        for (unsigned int faceId = 0; faceId < faceVertexCounts.length(); ++faceId) {
            Face face;
            for (int i = 0; i < faceVertexCounts[faceId]; ++i) {
                face.vertices.push_back(faceVertices[vertIter++]);
            }
            for (int t = 0; t < triangleCounts[faceId]; ++t) {
                std::array<int,3> tri = {
                    triangleVertices[triIter],
                    triangleVertices[triIter + 1],
                    triangleVertices[triIter + 2]
                };
                face.triangles.push_back(tri);
                triIter += 3;
            }
            md.faces.push_back(std::move(face));
        }

        meshData.push_back(std::move(md));
    }
}

void CageControlNode::calculateBinding(MDataBlock& data) {
    MArrayDataHandle inMatArray   = data.inputArrayValue(aInputMatrix);
    MArrayDataHandle inGeomArray  = data.inputArrayValue(aInputGeometry);
    unsigned int        numPoints = inMatArray.elementCount();

    if (bindData.size() == numPoints) {
        return;
    }

    bindData.clear();
    bindData.resize(numPoints);
    for (auto& bd : bindData) {
        bd.closestPointDistance = DBL_MAX;
    }

    for (unsigned int geomIndex = 0; geomIndex < meshData.size(); ++geomIndex) {
        inGeomArray.jumpToArrayElement(geomIndex);
        MObject meshObj = inGeomArray.inputValue().asMesh();
        MFnMesh fnMesh(meshObj);

        MDagPath    dagPath;
        MSelectionList sel;
        sel.add(meshObj);
        sel.getDagPath(0, dagPath);
        MMeshIntersector intersector;
        intersector.create(dagPath.node(), dagPath.inclusiveMatrix());

        for (unsigned int ptIndex = 0; ptIndex < numPoints; ++ptIndex) {
            inMatArray.jumpToArrayElement(ptIndex);
            MMatrix mat = inMatArray.inputValue().asMatrix();
            MPoint  point(mat(3,0), mat(3,1), mat(3,2));

            MPointOnMesh ptOnMesh;
            intersector.getClosestPoint(point, ptOnMesh);
            double distance = ptOnMesh.getPoint().distanceTo(point);

            // Nur aktualisieren, wenn kürzer
            if (distance >= bindData[ptIndex].closestPointDistance) {
                continue;
            }

            int                faceId = ptOnMesh.faceIndex();
            int                triId  = ptOnMesh.triangleIndex();
            auto&              tri    = meshData[geomIndex].faces[faceId].triangles[triId];
            MPoint             v0, v1, v2;
            fnMesh.getPoint(tri[0], v0, MSpace::kWorld);
            fnMesh.getPoint(tri[1], v1, MSpace::kWorld);
            fnMesh.getPoint(tri[2], v2, MSpace::kWorld);

            MMatrix           rotMat = rotationMatrixFromTri(v0, v1, v2);
            auto              bary   = getBarycentricCoordinates(ptOnMesh.getPoint(), v0, v1, v2);

            BindData bd;
            bd.vertexIdxs           = { tri[0], tri[1], tri[2] };
            bd.barycentricCoords    = { bary[0], bary[1], bary[2] };
            bd.rotationMatrix       = rotMat;
            bd.closestPointDistance = distance;
            bd.geomIndex            = geomIndex;

            MMatrix defMat = getTransformedMatrix(bd, data);
            bd.offsetVector = MVector(-defMat(3,0), -defMat(3,1), -defMat(3,2));

            bindData[ptIndex] = bd;
        }
    }
}

void CageControlNode::setOutputMatrix(MDataBlock& data) {
    MArrayDataHandle inMatArray  = data.inputArrayValue(aInputMatrix);
    MArrayDataHandle outArrHandle = data.outputArrayValue(aOutputMatrix);
    unsigned int count = inMatArray.elementCount();

    MArrayDataBuilder builder(data, aOutputMatrix, count);

    for (unsigned int i = 0; i < count; ++i) {
        auto element = builder.addElement(i);
        MMatrix matrix = getTransformedMatrix(bindData[i], data);
        element.setMMatrix(matrix);
    }

    outArrHandle.set(builder);
    outArrHandle.setAllClean();
}
