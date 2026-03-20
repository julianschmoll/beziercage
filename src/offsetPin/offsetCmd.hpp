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

private:
    enum CommandMode {
        kCreate,
        kEdit,
        kAdd
    };

    /**
     * Parses the command arguments.
     * @param args The argument list to parse.
     * @return MStatus indicating success or failure.
     */
    MStatus ParseArguments(const MArgList &args);

    /**
     * Makes the connections for the pin node.
     * @param pinFn The MFnDependencyNode for the pin node.
     * @return MStatus indicating success or failure.
     */
    MStatus ConnectPin(MFnDependencyNode &pinFn);

    /**
     * Creates a new pin node with the specified geometry.
     * @return MStatus indicating success or failure.
     */
    MStatus CreatePinNode();

    /**
     * Edits an existing pin node by clearing its connections and reconnecting.
     * @return MStatus indicating success or failure.
     */
    MStatus EditPinNode();

    /**
     * Adds pin objects to the existing pin node.
     * @return MStatus indicating success or failure.
     */
    MStatus AddPinObjects();

    // The command mode being executed
    CommandMode commandMode_ = kCreate;

    // The name of the pin node to create or edit
    MString nodeName_;

    // The selection list of geometries to pin;
    MSelectionList geometryList_;

    // The modifier for creating and editing nodes
    MDGModifier dgModifier_;

    // The pin node object
    MObject pinNode_;
};
