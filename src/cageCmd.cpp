#include "cageCmd.hpp"
#include "cageDeformer.hpp"
#include "common.hpp"

const char *cageCmd::kName = "deformCage";

const char *cageCmd::kNameFlagShort = "-n";
const char *cageCmd::kNameFlagLong = "-name";

const char *cageCmd::kHelpFlagShort = "-h";
const char *cageCmd::kHelpFlagLong = "-help";

const char *cageCmd::kRebindFlagShort = "-r";
const char *cageCmd::kRebindFlagLong = "-rebind";


void DisplayHelp() {
    MString help;
    help += "Flags of cage Command:\n";
    help += "-name (-n):          String     Name of the cage node to create.\n";
    help += "-help (-h)           N/A        Display this text.\n";
    MGlobal::displayInfo(help);
}

cageCmd::cageCmd() : name_("cage#"), executedCommand(kCommandCreate) {
}


MSyntax cageCmd::newSyntax() {
    MSyntax syntax;

    syntax.addFlag(kNameFlagShort, kNameFlagLong, MSyntax::kString);
    syntax.addFlag(kHelpFlagShort, kHelpFlagLong, MSyntax::kBoolean);
    syntax.addFlag(kRebindFlagShort, kRebindFlagLong, MSyntax::kString);

    // Allows between 1 and 255 objects to be deformed, 0 for help flag
    syntax.setObjectType(MSyntax::kSelectionList, 0, 255);
    syntax.useSelectionAsDefault(true);

    return syntax;
}


void *cageCmd::creator() {
    return new cageCmd;
}


bool cageCmd::isUndoable() const {
    return executedCommand == kCommandCreate;
}


MStatus cageCmd::doIt(const MArgList &args) {
    MStatus status;

    status = GatherCommandArguments(args);
    CHECK_MSTATUS_AND_RETURN_IT(status);

#if DEBUG_LOG
    MGlobal::displayInfo("Gathered command arguments successfully.");
#endif

    GetGeometryPaths();

#if DEBUG_LOG
    MGlobal::displayInfo("Gathered geometry paths successfully.");
#endif

    if (deformedDagPaths.length() == 0 && executedCommand == kCommandCreate) {
        MGlobal::displayError("cage requires at least 1 shape(s) to be specified or selected;  found 0.");
        return MS::kFailure;
    }

    MString deformerType = MString(bezierCage::typeName);
    MString command = "deformer -type " + deformerType + " -n \"" + name_ + "\"";

    for (unsigned int i = 0; i < deformedDagPaths.length(); ++i) {
        MFnDagNode fnNode(deformedDagPaths[i]);
        command += " " + fnNode.partialPathName();
    }

    status = dgMod_.commandToExecute(command);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    return redoIt();
}


MStatus cageCmd::GetGeometryPaths() {
    MStatus status;

    MItSelectionList iter(currentSelection);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    deformedDagPaths.clear();

    for (unsigned int i = 0; i < currentSelection.length(); ++i, iter.next()) {
        MDagPath path;
        MObject component;
        iter.getDagPath(path, component);
        status = GetShapeNode(path);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        deformedDagPaths.append(path);
    }
    return MS::kSuccess;
}


MStatus cageCmd::GatherCommandArguments(const MArgList &args) {
    MStatus status;

    MArgDatabase argData(syntax(), args);
    argData.getObjects(currentSelection);

    if (argData.isFlagSet(kHelpFlagShort)) {
        if (argData.flagArgumentBool(kHelpFlagShort, 0, &status)) {
            executedCommand = kCommandHelp;
        }
        CHECK_MSTATUS_AND_RETURN_IT(status);
    }
    if (argData.isFlagSet(kNameFlagShort)) {
        name_ = argData.flagArgumentString(kNameFlagShort, 0, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
    }
    if (argData.isFlagSet(kRebindFlagShort)) {
        executedCommand = kCommandRebind;
        MString cageNode = argData.flagArgumentString(kRebindFlagShort, 0, &status);
        MSelectionList slist;
        status = slist.add(cageNode);
        if (status != MS::kSuccess || slist.length() == 0) {
            MGlobal::displayError("There is no node named: " + cageNode);
            return MS::kFailure;
        }
        status = slist.getDependNode(0, oCageNode);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        MFnDependencyNode fnNode(oCageNode, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        if (fnNode.typeId() != bezierCage::id) {
            MGlobal::displayError(fnNode.name() + " is not a bezierCage node.");
            return MS::kFailure;
        }
    }

    return MS::kSuccess;
}

MStatus cageCmd::redoIt() {
    MStatus status;

#if DEBUG_LOG
    MGlobal::displayInfo("Executing cage command");
#endif


    if (executedCommand == kCommandHelp) {
        DisplayHelp();
        return MS::kSuccess;
    }
    if (executedCommand == kCommandCreate) {
        status = dgMod_.doIt();
        CHECK_MSTATUS_AND_RETURN_IT(status);
        status = GetGeometryPaths();
        CHECK_MSTATUS_AND_RETURN_IT(status);
        status = GetLatestDeformerNode();
        MFnDependencyNode fnDeformerNode(oCageNode, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        setResult(fnDeformerNode.name());
    }

    if (executedCommand == kCommandRebind) {
#if DEBUG_LOG
        MGlobal::displayInfo("Rebinding deformer :)");
#endif
        MObject deformerObj = oCageNode;
        MFnDependencyNode fnDep(deformerObj, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        MPlug dirtyPlug(deformerObj, bezierCage::aDirty);
        status = dirtyPlug.setBool(true);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        MGlobal::executeCommand("dgdirty " + fnDep.name());
        setResult("Rebound " + fnDep.name());
    }
    return MS::kSuccess;
}


MStatus cageCmd::GetLatestDeformerNode() {
    MStatus status;
    MObject oMesh = deformedDagPaths[0].node();

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
        if (fnNode.typeId() == bezierCage::id) {
            oCageNode = oDeformerNode;
            return MS::kSuccess;
        }
    }
    return MS::kFailure;
}


MStatus cageCmd::undoIt() {
    MStatus status;
    status = dgMod_.undoIt();
    CHECK_MSTATUS_AND_RETURN_IT(status);
    return MS::kSuccess;
}
