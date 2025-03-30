#include "common.hpp"
#include "cageCmd.hpp"
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
