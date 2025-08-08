#include "common.hpp"
#include <cmath>
#include <maya/MPoint.h>

#include "offsetPin.hpp"
#include "cageDeformer.hpp"

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

    m[2][0] = normal.x;
    m[2][1] = normal.y;
    m[2][2] = normal.z;
    m[2][3] = 0.0;

    m[3][0] = 0.0;
    m[3][1] = 0.0;
    m[3][2] = 0.0;
    m[3][3] = 1.0;
}

MPoint deCasteljau(const std::vector<MPoint> &points, float t) {
    if (points.empty()) {
#if ERROR_LOG
        MGlobal::displayError("No points provided for de Casteljau's algorithm.");
#endif
        return MPoint();
    }
    auto p = points;
    for (size_t i = 1; i < p.size(); ++i) {
        for (size_t j = 0; j < p.size() - i; ++j) {
            p[j] = p[j] * (1.0f - t) + p[j + 1] * t;
        }
    }
    return p[0];
}

MPoint evaluateBezierPatch(const std::vector<MPoint> &controlPoints, float u, float v) {
    if (controlPoints.size() != 16) {
#if ERROR_LOG
        MGlobal::displayError(
            "Bezier patch must consist of 16 control points, found " +
            MString(std::to_string(controlPoints.size()).c_str())
        );
#endif
        return MPoint();
    }

    std::vector<MPoint> vPoints;
    vPoints.reserve(4);
    for (int i = 0; i < 4; ++i) {
        std::vector<MPoint> row(controlPoints.begin() + i * 4, controlPoints.begin() + i * 4 + 4);
        vPoints.push_back(deCasteljau(row, v));
    }

    return deCasteljau(vPoints, u);
}

void connectionMonitorCallback(MPlug &srcPlug, MPlug &destPlug, bool made, void *clientData) {
    MStatus status;

    MObject destNode = destPlug.node(&status);
    CHECK_MSTATUS(status);
    MFnDependencyNode destNodeFn(destNode, &status);
    CHECK_MSTATUS(status);

    if (destNodeFn.typeName() != bezierCage::typeName) {
        return;
    }

    if (destPlug.attribute() != MPxDeformerNode::inputGeom) {
        return;
    }

    unsigned int logicalIndex = destPlug.parent().logicalIndex(&status);
    CHECK_MSTATUS(status);

    MPlug messagePlug = destNodeFn.findPlug(bezierCage::aControlMessage, false, &status);
    CHECK_MSTATUS(status);

    MPlugArray connectedPlugs;
    messagePlug.connectedTo(connectedPlugs, true, false, &status);
    CHECK_MSTATUS(status);

    if (connectedPlugs.length() == 0) {
        return;
    }

    MObject controlNode = connectedPlugs[0].node(&status);
    CHECK_MSTATUS(status);
    MFnDependencyNode controlNodeFn(controlNode, &status);
    if (status != MS::kSuccess || controlNodeFn.typeName() != offsetPin::typeName) { return; }

    MPlug controlInputGeomArrayPlug = controlNodeFn.findPlug(offsetPin::aInputGeometry, false, &status);
    CHECK_MSTATUS(status);

    MPlug controlInputGeomElementPlug = controlInputGeomArrayPlug.elementByLogicalIndex(logicalIndex, &status);
    CHECK_MSTATUS(status);

    MDGModifier modifier;

    if (made) {
        MPlugArray connected;
        if (controlInputGeomElementPlug.connectedTo(connected, true, false) && connected.length() > 0) {
            modifier.disconnect(connected[0], controlInputGeomElementPlug);
        }
        modifier.connect(srcPlug, controlInputGeomElementPlug);
    } else {
        modifier.disconnect(srcPlug, controlInputGeomElementPlug);
    }

    status = modifier.doIt();
    CHECK_MSTATUS(status);
}
