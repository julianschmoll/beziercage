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
const char *offsetCmd::kAddFlagShort = "-am";
const char *offsetCmd::kAddFlagLong = "-add_matrix";
const char *offsetCmd::kMatrixFlagShort = "-m";
const char *offsetCmd::kMatrixFlagLong = "-matrix";

void *offsetCmd::creator() {
    return new offsetCmd();
}

MSyntax offsetCmd::newSyntax() {
    MSyntax syntax;
    syntax.addFlag(kNameFlagShort, kNameFlagLong, MSyntax::kString);
    syntax.addFlag(kEditFlagShort, kEditFlagLong, MSyntax::kBoolean);
    syntax.addFlag(kAddFlagShort, kAddFlagLong, MSyntax::kBoolean);
    syntax.addFlag(kMatrixFlagShort, kMatrixFlagLong, MSyntax::kDouble);
    syntax.makeFlagMultiUse(kMatrixFlagShort);

    syntax.setObjectType(MSyntax::kSelectionList);
    syntax.useSelectionAsDefault(true);
    syntax.setMinObjects(0);

    syntax.enableQuery(false);
    syntax.enableEdit(true);

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
        case kEditMatrix:
            return EditMatrix();
        case kAdd:
            return AddMatrix();
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
        commandMode_ = kEditMatrix;
    }
    if (argData.isFlagSet(kAddFlagShort)) {
        commandMode_ = kAdd;
    }

    if (argData.isFlagSet(kNameFlagShort)) {
        status = argData.getFlagArgument(kNameFlagShort, 0, nodeName_);
        CHECK_MSTATUS_AND_RETURN_IT(status);
    }

    if (argData.isFlagSet(kMatrixFlagShort)) {
        unsigned int numMatrixArgs = argData.numberOfFlagUses(kMatrixFlagShort);
        if (numMatrixArgs != 16) {
            MGlobal::displayError("Matrix flag requires exactly 16 values for a 4x4 matrix.");
            return MS::kFailure;
        }

        MGlobal::displayInfo(MString("Matrix flag used ") + numMatrixArgs + " times.");
        MArgList argList;

        for (unsigned int i = 0; i < numMatrixArgs; ++i) {
            argData.getFlagArgumentList(kMatrixFlagShort, i, argList);
            double value = argList.asDouble(i, &status);
            CHECK_MSTATUS_AND_RETURN_IT(status);
            matrix_[i / 4][i % 4] = value;
        }

#if DEBUG_LOG
        MString matrixStr = "Matrix set to: [";
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                matrixStr += std::to_string(matrix_[row][col]).c_str();
                if (col < 3) matrixStr += ", ";
            }
        }
        MGlobal::displayInfo(matrixStr + "]");
#endif
    }

    status = argData.getObjects(geometryList_);
    CHECK_MSTATUS_AND_RETURN_IT(status);

#if DEBUG_LOG
    MGlobal::displayInfo("Succesfully parsed arguments for offsetCmd.");
#endif

    return MS::kSuccess;
}


MStatus offsetCmd::CreatePinNode() {
    MStatus status;
    if (geometryList_.isEmpty()) {
        displayError("No geometry specified or selected. Please select or specify the geometry to pin to.");
        return MS::kFailure;
    }
    pinNode_ = dgModifier_.createNode(offsetPin::id, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    if (!nodeName_.isEmpty()) {
        dgModifier_.renameNode(pinNode_, nodeName_);
    }

    MFnDependencyNode pinFn(pinNode_);
    MPlug inGeomPlug = pinFn.findPlug(offsetPin::aInputGeometry, false, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MPlug origGeomPlug = pinFn.findPlug(offsetPin::aOriginalGeometry, false, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    for (unsigned int i = 0; i < geometryList_.length(); ++i) {
        MDagPath geomPath;
        status = geometryList_.getDagPath(i, geomPath);
        if (status != MS::kSuccess) {
            MGlobal::displayError("Could not find a mesh for object at index " + MString(std::to_string(i).c_str()));
            return status;
        }
        status = GetShapeNode(geomPath);
        if (status != MS::kSuccess) {
            MGlobal::displayError("Could not find valid geometry to connect node to.");
            return status;
        }

        MFnDependencyNode geomFn(geomPath.node());
        MPlug outMeshPlug = geomFn.findPlug("outMesh", false, &status);
        if (status != MS::kSuccess) {
            outMeshPlug = geomFn.findPlug("worldMesh", false, &status).elementByLogicalIndex(0);
        }
        CHECK_MSTATUS_AND_RETURN_IT(status);

        MPlug inGeomElementPlug = inGeomPlug.elementByLogicalIndex(i, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        MPlug origGeomElementPlug = origGeomPlug.elementByLogicalIndex(i, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);

        dgModifier_.connect(outMeshPlug, inGeomElementPlug);
        dgModifier_.connect(outMeshPlug, origGeomElementPlug);
    }

    MPlug inMatrixPlug = pinFn.findPlug(offsetPin::aInputMatrix, false, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MPlug matrixElementPlug = inMatrixPlug.elementByLogicalIndex(0, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MFnMatrixData matrixData;
    MObject matrixObj = matrixData.create(matrix_, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    dgModifier_.newPlugValue(matrixElementPlug, matrixObj);

    setResult(nodeName_);

    return dgModifier_.doIt();
}

MStatus offsetCmd::EditMatrix() {
    MStatus status;
    MSelectionList sel;
    status = sel.add(nodeName_);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    status = sel.getDependNode(0, pinNode_);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MFnDependencyNode pinFn(pinNode_);
    MPlug inMatrixPlug = pinFn.findPlug(offsetPin::aInputMatrix, false, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    return dgModifier_.doIt();
}

MStatus offsetCmd::AddMatrix() {
    MStatus status;
    MSelectionList sel;
    status = sel.add(nodeName_);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    status = sel.getDependNode(0, pinNode_);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MFnDependencyNode pinFn(pinNode_);
    MPlug inMatrixPlug = pinFn.findPlug(offsetPin::aInputMatrix, false, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    unsigned int nextIndex = inMatrixPlug.numElements();

    return dgModifier_.doIt();
}
