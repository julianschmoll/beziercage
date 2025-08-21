#pragma once

#include <maya/MPxCommand.h>
#include <maya/MString.h>
#include <maya/MSelectionList.h>
#include <maya/MDGModifier.h>
#include <maya/MDagPathArray.h>
#include <maya/MMatrix.h>
#include <vector>

class offsetCmd : public MPxCommand {
public:
    offsetCmd() = default;
    ~offsetCmd() override = default;

    MStatus doIt(const MArgList &args) override;
    MStatus undoIt() override;
    MStatus redoIt() override;

    bool isUndoable() const override { return true; }

    static void *creator();
    static MSyntax newSyntax();

    const static char *kName;
    static const char *kNameFlagShort;
    static const char *kNameFlagLong;
    static const char *kEditFlagShort;
    static const char *kEditFlagLong;
    static const char *kAddFlagShort;
    static const char *kAddFlagLong;
    static const char *kMatrixFlagShort;
    static const char *kMatrixFlagLong;

private:
    enum CommandMode {
        kCreate,
        kEditMatrix,
        kAdd
    };

    MStatus ParseArguments(const MArgList &args);
    MStatus CreatePinNode();
    MStatus EditMatrix();
    MStatus AddMatrix();

    CommandMode commandMode_ = kCreate;
    MString nodeName_;
    int matrixIndex_ = -1;
    MSelectionList geometryList_;
    MMatrix matrix_;
    MDGModifier dgModifier_;
    MObject pinNode_;
};
