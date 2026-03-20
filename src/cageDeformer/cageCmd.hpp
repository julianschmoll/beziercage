#pragma once

#include <maya/MSelectionList.h>
#include <maya/MDagPath.h>
#include <maya/MDagPathArray.h>
#include <maya/MPlug.h>
#include <maya/MString.h>
#include <maya/MStringArray.h>
#include <maya/MGlobal.h>
#include <maya/MSyntax.h>
#include <maya/MString.h>
#include <maya/MArgList.h>
#include <maya/MArgDatabase.h>
#include <maya/MObject.h>
#include <maya/MDGModifier.h>

#include <maya/MItGeometry.h>
#include <maya/MItDependencyGraph.h>
#include <maya/MItSelectionList.h>
#include <maya/MFnDagNode.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFn.h>
#include <maya/MFnData.h>
#include <maya/MFnMesh.h>
#include <maya/MFnTransform.h>

#include <maya/MPxCommand.h>

#include "common.hpp"
#include "cageDeformer.hpp"

class cageCmd : public MPxCommand {
public:
    cageCmd();

    // Enum to figure out which command was executed
    enum CommandMode { kCommandCreate, kCommandHelp, kCommandRebind };

    static void *creator();

    virtual MStatus doIt(const MArgList &);

    /**
     * Gets the latest deformer node from the deformation chain of the first selected geometry.
     * @return MStatus indicating success or failure.
     */
    MStatus GetLatestDeformerNode();

    virtual MStatus undoIt();

    virtual MStatus redoIt();

    virtual bool isUndoable() const;

    const static char *kName;
    const static char *kNameFlagShort;
    const static char *kNameFlagLong;
    const static char *kHelpFlagShort;
    const static char *kHelpFlagLong;
    const static char *kRebindFlagShort;
    const static char *kRebindFlagLong;

    static MTypeId id;

    static MSyntax newSyntax();

private:
    /**
     * Gathers command arguments from the provided argument list.
     * @param args The argument list to gather arguments from.
     * @return MStatus indicating success or failure.
     */
    MStatus GatherCommandArguments(const MArgList &args);

    /**
     * Retrieves geometry paths from the current selection.
     * This is used to find the geometry that the deformer will operate on.
     * @return MStatus indicating success or failure.
     */
    MStatus GetGeometryPaths();

    MString name_;
    MSelectionList currentSelection;
    MDGModifier dgMod_;
    MObject oCageNode;
    MDagPathArray deformedDagPaths;
    CommandMode executedCommand;
};
