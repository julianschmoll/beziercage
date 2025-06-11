#include "common.hpp"

bool IsShapeNode(MDagPath &path) {
    return path.node().hasFn(MFn::kMesh) ||
           path.node().hasFn(MFn::kNurbsCurve) ||
           path.node().hasFn(MFn::kNurbsSurface);
}

MStatus GetShapeNode(MDagPath &path, bool intermediate) {
    MStatus status;

    if (IsShapeNode(path)) {
        path.pop();
    }

    if (path.hasFn(MFn::kTransform)) {
        unsigned int shapeCount = path.childCount();

        for (unsigned int i = 0; i < shapeCount; ++i) {
            status = path.push(path.child(i));
            CHECK_MSTATUS_AND_RETURN_IT(status);
            if (!IsShapeNode(path)) {
                path.pop();
                continue;
            }

            MFnDagNode fnNode(path, &status);
            CHECK_MSTATUS_AND_RETURN_IT(status);

            if ((!fnNode.isIntermediateObject() && !intermediate) || (fnNode.isIntermediateObject() && intermediate)) {
                return MS::kSuccess;
            }
            path.pop();
        }
    }
    return MS::kFailure;
}

MStatus GetDagPath(MString &name, MDagPath &path) {
    MStatus status;
    MSelectionList list;
    status = MGlobal::getSelectionListByName(name, list);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    status = list.getDagPath(0, path);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    return MS::kSuccess;
}

MStatus DeleteIntermediateObjects(MDagPath &path) {
    MStatus status;
    MDagPath pathMesh(path);
    while (GetShapeNode(pathMesh, true) == MS::kSuccess) {
        status = MGlobal::executeCommand("delete " + pathMesh.partialPathName());
        CHECK_MSTATUS_AND_RETURN_IT(status);
        pathMesh = MDagPath(path);
    }
    return MS::kSuccess;
}

// Erzeugt aus drei Dreieckspunkten eine orthonormale Basis als Rotationsmatrix
MMatrix rotationMatrixFromTri(const MPoint& a, const MPoint& b, const MPoint& c) {
    MVector tangent   = b - a;
    MVector bitangent = c - a;
    MVector normal    = tangent ^ bitangent;
    MMatrix result; // initial Identity

    if (normal.length() < 1e-8) {
        MGlobal::displayWarning("Degenerates Dreieck, benutze Identität.");
        return result;
    }

    normal.normalize();
    tangent = tangent.normal();
    tangent = (tangent - normal * (tangent * normal)).normal();
    bitangent = (normal ^ tangent).normal();

    double elems[16] = {
        tangent.x,   tangent.y,   tangent.z,   0.0,
        bitangent.x, bitangent.y, bitangent.z, 0.0,
       -normal.x,   -normal.y,   -normal.z,   0.0,
        0.0,         0.0,         0.0,         1.0
    };
    MScriptUtil::createMatrixFromList(elems, result);
    return result;
}

// Berechnet baryzentrische Koordinaten eines Punktes p relativ zum Dreieck a,b,c
std::array<double,3> getBarycentricCoordinates(
    const MPoint& p,
    const MPoint& a,
    const MPoint& b,
    const MPoint& c
) {
    MVector v0 = b - a;
    MVector v1 = c - a;
    MVector v2 = p - a;
    MVector n  = v0 ^ v1;
    double area2 = n.length();
    if (area2 < 1e-8) {
        return {1.0, 0.0, 0.0};
    }
    // Flächenanteile
    double u = ((b - p) ^ (c - p)).length() / area2;
    double v = ((c - p) ^ (a - p)).length() / area2;
    double w = 1.0 - u - v;
    return {u, v, w};
}

// Zusammensetzen der finalen Transformationsmatrix aus BindData und deformiertem Mesh
MMatrix getTransformedMatrix(const BindData& bd, MDataBlock& data) {
    // Deformiertes Mesh holen
    MArrayDataHandle geomArr = data.inputArrayValue(CageControlNode::aInputGeometry);
    geomArr.jumpToArrayElement(bd.geomIndex);
    MFnMesh fnMesh(geomArr.inputValue().asMesh());

    // Welt-Punkte der drei Bind-Vertizes
    MPoint va, vb, vc;
    fnMesh.getPoint(bd.vertexIdxs[0], va, MSpace::kWorld);
    fnMesh.getPoint(bd.vertexIdxs[1], vb, MSpace::kWorld);
    fnMesh.getPoint(bd.vertexIdxs[2], vc, MSpace::kWorld);

    // Interpolierter Punkt
    MPoint interp = va * bd.barycentricCoords[0]
                  + vb * bd.barycentricCoords[1]
                  + vc * bd.barycentricCoords[2];

    // Drehung: urspr. Bind-Rotation -> aktuelle Dreiecks-Rotation
    MMatrix rotNow = rotationMatrixFromTri(va, vb, vc);
    MMatrix delta  = bd.rotationMatrix.inverse() * rotNow;

    MTransformationMatrix tm(delta);
    tm.addTranslation(MVector(interp), MSpace::kWorld);
    tm.addTranslation(bd.offsetVector, MSpace::kObject);

    return tm.asMatrix();
}
