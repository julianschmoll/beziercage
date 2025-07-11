#include "common.hpp"
#include <cmath>

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

void GetBarycentricCoordinates(const MPoint &p, const MPoint &a, const MPoint &b, const MPoint &c,
                               MFloatArray &coords) {
    // Compute the normal of the triangle
    MVector N = (b - a) ^ (c - a);
    MVector unitN = N.normal();

    coords.setLength(3);

    // Compute twice area of triangle ABC
    double areaABC = unitN * N;

    // If the triangle is degenerate, just use one of the points.
    if (fabs(areaABC) < 1e-8) {
        coords[0] = 1.0f;
        coords[1] = 0.0f;
        coords[2] = 0.0f;
        return;
    }

    // Compute a
    double areaPBC = unitN * ((b - p) ^ (c - p));
    coords[0] = (float) (areaPBC / areaABC);

    // Compute b
    double areaPCA = unitN * ((c - p) ^ (a - p));
    coords[1] = (float) (areaPCA / areaABC);

    // Compute c
    coords[2] = 1.0f - coords[0] - coords[1];
}

MStatus GetDagPathFromMesh(const MObject &meshObj, MDagPath &dagPath) {
    if (meshObj.isNull()) return MS::kFailure;
    MFnDagNode dagNode(meshObj);
    return dagNode.getPath(dagPath);
}

void RotationMatrixFromTri(const MPoint &a, const MPoint &b, const MPoint &c, MMatrix &m) {
    m.setToIdentity();
    MVector tangent = b - a;
    MVector bitangent = c - a;
    MVector normal = tangent ^ bitangent;

    // if triangle is degenerate, set matrix to identity
    if (normal.length() < 1e-8) {
        return;
    }

    // build orthonormal basis by orthogonalizing the tangent and bitangent
    normal.normalize();
    tangent = tangent.normal();
    tangent = (tangent - normal * (tangent * normal)).normal();
    bitangent = (normal ^ tangent).normal();

    m[0][0] = tangent.x;
    m[0][1] = tangent.y;
    m[0][2] = tangent.z;
    m[0][3] = 0.0;

    m[1][0] = bitangent.x;
    m[1][1] = bitangent.y;
    m[1][2] = bitangent.z;
    m[1][3] = 0.0;

    m[2][0] = -normal.x;
    m[2][1] = -normal.y;
    m[2][2] = -normal.z;
    m[2][3] = 0.0;

    m[3][0] = 0.0;
    m[3][1] = 0.0;
    m[3][2] = 0.0;
    m[3][3] = 1.0;
}
