#ifndef JSMEARCMD_HPP
#define JSMEARCMD_HPP

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
#include "jSmearDeformer.hpp"

class jSmearCmd : public MPxCommand {
public:
    jSmearCmd();

    static void *creator();

    static MStatus initialize();

    virtual MStatus doIt(const MArgList &);

    MStatus GetLatestDeformerNode();

    virtual MStatus undoIt();

    virtual MStatus redoIt();

    virtual bool isUndoable() const;

    const static char *kName;
    const static char *kNameFlagShort;
    const static char *kNameFlagLong;
    const static char *kHelpFlagShort;
    const static char *kHelpFlagLong;

    static MTypeId id;

    static MSyntax newSyntax();

private:
    MStatus GatherCommandArguments(const MArgList &args);

    MStatus GetGeometryPaths();

    MString name_;
    MSelectionList selectionList_; /**< Selected command input nodes. */
    MDagPathArray drivenGeometry_;
    MDGModifier dgMod_;
    MObject oDeformerNode_;
    MDagPathArray pathDriven_;
};
#endif
