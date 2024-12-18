#include "jSmearCmd.h"

const char *jSmearCmd::kName = "jSmear";

const char *jSmearCmd::kNameFlagShort = "-n";
const char *jSmearCmd::kNameFlagLong = "-name";

const char *jSmearCmd::kHelpFlagShort = "-h";
const char *jSmearCmd::kHelpFlagLong = "-help";

bool helpFlagSet = false;


void DisplayHelp() {
    MString help;
    help += "Flags of jSmear Command:\n";
    help += "-name (-n):          String     Name of the jSmear node to create.\n";
    help += "-help (-h)           N/A        Display this text.\n";
    MGlobal::displayInfo(help);
}

jSmearCmd::jSmearCmd() : name_("jSmear#") {
}


MSyntax jSmearCmd::newSyntax() {
    MSyntax syntax;

    syntax.addFlag(kNameFlagShort, kNameFlagLong, MSyntax::kString);
    syntax.addFlag(kHelpFlagShort, kHelpFlagLong, MSyntax::kBoolean);

    // Allows between 1 and 255 objects to be deformed, 0 for help flag
    syntax.setObjectType(MSyntax::kSelectionList, 0, 255);
    syntax.useSelectionAsDefault(true);

    return syntax;
}


void *jSmearCmd::creator() {
    return new jSmearCmd;
}


bool jSmearCmd::isUndoable() const {
    return true;
}


MStatus jSmearCmd::doIt(const MArgList &args) {
    MStatus status;

    status = GatherCommandArguments(args);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    status = GetGeometryPaths();
    CHECK_MSTATUS_AND_RETURN_IT(status);

    if (pathDriven_.length() == 0 && !helpFlagSet) {
        MGlobal::displayError("jSmear requires at least 1 shape(s) to be specified or selected;  found 0.");
        return MS::kFailure;
    }

    MString command = "deformer -type jSmear -n \"" + name_ + "\"";

    for (unsigned int i = 0; i < pathDriven_.length(); ++i) {
        MFnDagNode fnDriven(pathDriven_[i]);
        command += " " + fnDriven.partialPathName();
    }

    status = dgMod_.commandToExecute(command);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    return redoIt();
}


MStatus jSmearCmd::GetGeometryPaths() {
    MStatus status;

    MItSelectionList iter(selectionList_);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    pathDriven_.clear();

    for (unsigned int i = 0; i < selectionList_.length(); ++i, iter.next()) {
        MDagPath path;
        MObject component;
        iter.getDagPath(path, component);
        status = GetShapeNode(path);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        pathDriven_.append(path);
    }
    return MS::kSuccess;
}


MStatus jSmearCmd::GatherCommandArguments(const MArgList &args) {
    MStatus status;

    MArgDatabase argData(syntax(), args);
    argData.getObjects(selectionList_);

    if (argData.isFlagSet(kHelpFlagShort)) {
        helpFlagSet = argData.flagArgumentBool(kHelpFlagShort, 0, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        return MS::kSuccess;
    }

    if (argData.isFlagSet(kNameFlagShort)) {
        name_ = argData.flagArgumentString(kNameFlagShort, 0, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
    }

    return MS::kSuccess;
}


MStatus jSmearCmd::redoIt() {
    MStatus status;

    if (helpFlagSet) {
        DisplayHelp();
        return MS::kSuccess;
    }

    status = dgMod_.doIt();
    CHECK_MSTATUS_AND_RETURN_IT(status);

    // Reacquire the path because on referenced geo, a new mesh is created (the ShapeDeformed).
    status = GetGeometryPaths();
    CHECK_MSTATUS_AND_RETURN_IT(status);

    // Get the created mesh blur deformer node.
    status = GetLatestDeformerNode();
    MFnDependencyNode fnDeformerNode(oDeformerNode_, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MDGModifier dgMod;
    // dgMod.connect(plugOutWorldMatrix, plugInMatrix); etc
    // status = dgMod.doIt();
    // CHECK_MSTATUS_AND_RETURN_IT(status);
    // setResult(fnDeformerNode.name());

    /*
     *
     * redoIt it needs to do the following:
     *
     * 1. Find all the relevant nodes and plugs
     *    (deformer node, deformed mesh, matrix, time, etc plugs)
     * 2. Create MDGModifier dgMod and connect those plugs with:
     *    dgMod.connect(plugOutWorldMatrix, plugInMatrix);
     *    status = dgMod.doIt();
     *  3. Run setResult(fnDeformerNode.name()) to return deformer node
     *
     */

    return MS::kSuccess;
}


MStatus jSmearCmd::GetLatestDeformerNode() {
    MStatus status;
    MObject oMesh = pathDriven_[0].node();

    // find it in the deformation chain.
    MItDependencyGraph itDG(
        oMesh,
        MFn::kGeometryFilt,
        MItDependencyGraph::kUpstream,
        MItDependencyGraph::kDepthFirst,
        MItDependencyGraph::kNodeLevel,
        &status
    );
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MObject oDeformerNode;
    for (; !itDG.isDone(); itDG.next()) {
        oDeformerNode = itDG.currentItem();
        MFnDependencyNode fnNode(oDeformerNode, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        if (fnNode.typeId() == jSmear::id) {
            oDeformerNode_ = oDeformerNode;
            return MS::kSuccess;
        }
    }
    return MS::kFailure;
}


MStatus jSmearCmd::undoIt() {
    MStatus status;
    status = dgMod_.undoIt();
    CHECK_MSTATUS_AND_RETURN_IT(status);
    return MS::kSuccess;
}
