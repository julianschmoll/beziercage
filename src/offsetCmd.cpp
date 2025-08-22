#include "offsetCmd.hpp"
#include "offsetPin.hpp"
#include "common.hpp"

#include <maya/MArgDatabase.h>
#include <maya/MGlobal.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MPlug.h>
#include <maya/MPlugArray.h>
#include <maya/MFnMatrixData.h>
#include <maya/MSyntax.h>
#include <maya/MSyntax.h>
#include <maya/MSyntax.h>
#include <maya/MSyntax.h>

const char *offsetCmd::kName = "offsetPin";

const char *offsetCmd::kNameFlagShort = "-n";
const char *offsetCmd::kNameFlagLong = "-name";

const char *offsetCmd::kEditFlagShort = "-e";
const char *offsetCmd::kEditFlagLong = "-edit";

const char *offsetCmd::kAddFlagShort = "-ap";
const char *offsetCmd::kAddFlagLong = "-append";

void *offsetCmd::creator() {
    return new offsetCmd();
}

MSyntax offsetCmd::newSyntax() {
    MSyntax syntax;
    MStatus status = syntax.addFlag(kNameFlagShort, kNameFlagLong, MSyntax::kString);
    if (status != MS::kSuccess) {
        MGlobal::displayError("Failed to add name flag to syntax.");
    }
    status = syntax.addFlag(kAddFlagShort, kAddFlagLong, MSyntax::kBoolean);
    if (status != MS::kSuccess) {
        MGlobal::displayError("Failed to add add flag to syntax.");
    }
    status = syntax.addFlag(kEditFlagShort, kEditFlagLong, MSyntax::kBoolean);
    if (status != MS::kSuccess) {
        MGlobal::displayError("Failed to add edit flag to syntax.");
    }

    // We need at least 2 objects, one geometry and one object to pin.
    syntax.setObjectType(MSyntax::kSelectionList, 2, 255);
    syntax.useSelectionAsDefault(true);

    return syntax;
}

MStatus offsetCmd::doIt(const MArgList &args) {
    MStatus status = ParseArguments(args);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    return redoIt();
}

MStatus offsetCmd::redoIt() {
    switch (commandMode_) {
        case kCreate:
            return CreatePinNode();
        case kEdit:
            return EditPinNode();
        case kAdd:
            return AddPinObjects();
    }
    return MS::kFailure;
}

MStatus offsetCmd::undoIt() {
    return dgModifier_.undoIt();
}

MStatus offsetCmd::ParseArguments(const MArgList &args) {
    MStatus status;
    MArgDatabase argData(syntax(), args, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    commandMode_ = kCreate;

    if (argData.isFlagSet(kEditFlagShort)) {
        if (!argData.isFlagSet(kNameFlagShort)) {
            MGlobal::displayError("Edit flag requires a name to be specified.");
            return MS::kFailure;
        }
        commandMode_ = kEdit;
    }
    if (argData.isFlagSet(kAddFlagShort)) {
        if (!argData.isFlagSet(kNameFlagShort)) {
            MGlobal::displayError("Add flag requires a name to be specified.");
            return MS::kFailure;
        }
        commandMode_ = kAdd;
    }

    if (argData.isFlagSet(kNameFlagShort)) {
        status = argData.getFlagArgument(kNameFlagShort, 0, nodeName_);
        CHECK_MSTATUS_AND_RETURN_IT(status);
    }
    status = argData.getObjects(geometryList_);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    return MS::kSuccess;
}


MStatus offsetCmd::ConnectPin(MFnDependencyNode &pinFn) {
    MStatus status;
    if (geometryList_.isEmpty()) {
        displayError("No geometry specified or selected. Please select or specify the geometry to pin to.");
        return MS::kFailure;
    }
    MPlug inGeomPlug = pinFn.findPlug(offsetPin::aInputGeometry, false, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MPlug origGeomPlug = pinFn.findPlug(offsetPin::aOriginalGeometry, false, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MDagPath geomPath;
    status = geometryList_.getDagPath(0, geomPath);
    if (status != MS::kSuccess) {
        MGlobal::displayError("Could not find a mesh for object at index 0");
        return status;
    }
    status = GetShapeNode(geomPath);
    if (status != MS::kSuccess) {
        MGlobal::displayError("Could not find valid geometry to connect node to.");
        return status;
    }
    MFnDependencyNode geomFn(geomPath.node());
    unsigned int nextIndex = inGeomPlug.numElements();

    MPlug outMeshPlug = geomFn.findPlug("outMesh", false, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MPlug worldMeshPlug = geomFn.findPlug("worldMesh", false, &status).elementByLogicalIndex(0);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    bool alreadyConnected = false;
    for (unsigned int i = 0; i < inGeomPlug.numElements(); ++i) {
        MPlug inGeomElementPlug = inGeomPlug.elementByLogicalIndex(i, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);

        MPlugArray existingConnections;
        inGeomElementPlug.connectedTo(existingConnections, true, false, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);

        for (unsigned int j = 0; j < existingConnections.length(); ++j) {
            if (existingConnections[j] == worldMeshPlug) {
                alreadyConnected = true;
                break;
            }
        }
    }

    if (!alreadyConnected) {
        MPlug inGeomElementPlug = inGeomPlug.elementByLogicalIndex(nextIndex, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        MPlug origGeomElementPlug = origGeomPlug.elementByLogicalIndex(nextIndex, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);

        dgModifier_.connect(worldMeshPlug, inGeomElementPlug);
        dgModifier_.connect(outMeshPlug, origGeomElementPlug);
    }

    for (unsigned int i = 1; i < geometryList_.length(); ++i) {
        unsigned int index = i - 1;

        MPlug inMatrixPlug = pinFn.findPlug(offsetPin::aInputMatrix, false, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        MPlug outMatrixPlug = pinFn.findPlug(offsetPin::aOutputMatrix, false, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);

        MPlug matrixElementPlug = inMatrixPlug.elementByLogicalIndex(index, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);

        MPlug outMatrixElementPlug = outMatrixPlug.elementByLogicalIndex(index, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);

        status = geometryList_.getDagPath(i, geomPath);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        MFnDagNode dagFn(geomPath.node());
        if (geomPath.node().hasFn(MFn::kTransform)) {
            MFnTransform transformFn(geomPath.node(), &status);
            CHECK_MSTATUS_AND_RETURN_IT(status);
            MMatrix matrix = transformFn.transformation().asMatrix();

            MFnMatrixData matrixDataFn;
            MObject matrixObj = matrixDataFn.create(matrix, &status);
            CHECK_MSTATUS_AND_RETURN_IT(status);
            dgModifier_.newPlugValue(matrixElementPlug, matrixObj);

            MPlug offsetParentMatrixPlug = transformFn.findPlug("offsetParentMatrix", false, &status);
            CHECK_MSTATUS_AND_RETURN_IT(status);
            MPlugArray existingConnections;
            offsetParentMatrixPlug.connectedTo(existingConnections, true, false, &status);
            CHECK_MSTATUS_AND_RETURN_IT(status);
            for (unsigned int j = 0; j < existingConnections.length(); ++j) {
                dgModifier_.disconnect(existingConnections[j], offsetParentMatrixPlug);
            }
            dgModifier_.connect(outMatrixElementPlug, offsetParentMatrixPlug);
        } else {
            MGlobal::displayError("Node is not a transform. Cannot extract matrix.");
            return MS::kFailure;
        }
    }
    return dgModifier_.doIt();
}

MStatus offsetCmd::CreatePinNode() {
    MStatus status;
    pinNode_ = dgModifier_.createNode(offsetPin::id, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    if (!nodeName_.isEmpty()) {
        dgModifier_.renameNode(pinNode_, nodeName_);
    }

    MFnDependencyNode pinFn(pinNode_);
    status = ConnectPin(pinFn);
    setResult(pinFn.name());
    return status;
}

MStatus offsetCmd::EditPinNode() {
    MSelectionList sel;
    MStatus status = sel.add(nodeName_);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    status = sel.getDependNode(0, pinNode_);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MFnDependencyNode pinFn(pinNode_);

    MPlug plugsToClear[] = {
        pinFn.findPlug(offsetPin::aInputGeometry, false, &status),
        pinFn.findPlug(offsetPin::aOriginalGeometry, false, &status),
        pinFn.findPlug(offsetPin::aInputMatrix, false, &status),
        pinFn.findPlug(offsetPin::aOutputMatrix, false, &status),
        pinFn.findPlug(offsetPin::aGeometryLookup, false, &status),
        pinFn.findPlug(offsetPin::aBindData, false, &status),
    };

    for (auto &plug: plugsToClear) {
        CHECK_MSTATUS_AND_RETURN_IT(status);
        for (unsigned int i = 0; i < plug.numElements(); ++i) {
            MPlug elem = plug.elementByLogicalIndex(i, &status);
            CHECK_MSTATUS_AND_RETURN_IT(status);
            MPlugArray connectedPlugs;
            elem.connectedTo(connectedPlugs, true, false, &status);
            CHECK_MSTATUS_AND_RETURN_IT(status);
            for (unsigned int j = 0; j < connectedPlugs.length(); ++j) {
                dgModifier_.disconnect(connectedPlugs[j], elem);
            }
            dgModifier_.removeMultiInstance(elem, true);
        }
    }
    status = dgModifier_.doIt();
    CHECK_MSTATUS_AND_RETURN_IT(status);
    status = ConnectPin(pinFn);
    if (status != MS::kSuccess) {
        MGlobal::displayError("Failed to reconnect " + pinFn.name());
        return status;
    }
    setResult("Reconnected " + pinFn.name());
    return status;
}

MStatus offsetCmd::AddPinObjects() {
    MSelectionList sel;
    MStatus status = sel.add(nodeName_);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    status = sel.getDependNode(0, pinNode_);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MFnDependencyNode pinFn(pinNode_);
    status = ConnectPin(pinFn);
    setResult("Added pin object to " + pinFn.name());
    return status;
}
