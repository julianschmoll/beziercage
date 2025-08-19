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
    syntax.addFlag(kMatrixFlagShort, kMatrixFlagLong, MSyntax::kString);

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
        case kEdit:
            return EditPinNode();
        case kAdd:
            return AddMatrices();
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
        commandMode_ = kEdit;
    }
    if (argData.isFlagSet(kAddFlagShort)) {
        commandMode_ = kAdd;
    }

    if (argData.isFlagSet(kNameFlagShort)) {
        status = argData.getFlagArgument(kNameFlagShort, 0, nodeName_);
        CHECK_MSTATUS_AND_RETURN_IT(status);
    }

    if (argData.isFlagSet(kMatrixFlagShort)) {
        MString matrixStr;
        argData.getFlagArgument(kMatrixFlagShort, 0, matrixStr);
        MStringArray matrixValues;
        matrixStr.split(' ', matrixValues);
        if (matrixValues.length() % 16 != 0) {
            MGlobal::displayError("Matrix list must contain a multiple of 16 values.");
            return MS::kFailure;
        }
        for (unsigned int i = 0; i < matrixValues.length() / 16; ++i) {
            MMatrix m;
            for (int row = 0; row < 4; ++row) {
                for (int col = 0; col < 4; ++col) {
                    m[row][col] = matrixValues[i * 16 + row * 4 + col].asDouble();
                }
            }
            matrixList_.push_back(m);
        }
    }

    status = argData.getObjects(geometryList_);
    CHECK_MSTATUS_AND_RETURN_IT(status);

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
        CHECK_MSTATUS_AND_RETURN_IT(status);
        status = GetShapeNode(geomPath);
        CHECK_MSTATUS_AND_RETURN_IT(status);

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
    for (unsigned int i = 0; i < matrixList_.size(); ++i) {
        MPlug matrixElementPlug = inMatrixPlug.elementByLogicalIndex(i, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        MFnMatrixData matrixData;
        MObject matrixObj = matrixData.create(matrixList_[i], &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        dgModifier_.newPlugValue(matrixElementPlug, matrixObj);
    }

    return dgModifier_.doIt();
}

MStatus offsetCmd::EditPinNode() {
    MStatus status;
    MSelectionList sel;
    status = sel.add(nodeName_);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    status = sel.getDependNode(0, pinNode_);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    if (matrixIndex_ < 0 || matrixList_.empty()) {
        MGlobal::displayError("Matrix index and matrix value must be provided for edit mode.");
        return MS::kFailure;
    }

    MFnDependencyNode pinFn(pinNode_);
    MPlug inMatrixPlug = pinFn.findPlug(offsetPin::aInputMatrix, false, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MPlug matrixElementPlug = inMatrixPlug.elementByLogicalIndex(matrixIndex_, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MFnMatrixData matrixData;
    MObject matrixObj = matrixData.create(matrixList_[0], &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    dgModifier_.newPlugValue(matrixElementPlug, matrixObj);

    return dgModifier_.doIt();
}

MStatus offsetCmd::AddMatrices() {
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

    for (unsigned int i = 0; i < matrixList_.size(); ++i) {
        MPlug matrixElementPlug = inMatrixPlug.elementByLogicalIndex(nextIndex + i, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        MFnMatrixData matrixData;
        MObject matrixObj = matrixData.create(matrixList_[i], &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        dgModifier_.newPlugValue(matrixElementPlug, matrixObj);
    }

    return dgModifier_.doIt();
}
