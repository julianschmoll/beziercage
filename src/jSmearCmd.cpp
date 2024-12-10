#include "jSmearCmd.h"

const char* jSmearCmd::kName = "jSmear";

const char* jSmearCmd::kNameFlagShort = "-n";
const char* jSmearCmd::kNameFlagLong = "-name";

const char* jSmearCmd::kHelpFlagShort = "-h";
const char* jSmearCmd::kHelpFlagLong = "-help";


void DisplayHelp() {
    MString help;
    help += "Flags:\n";
    help += "-name (-n):          String     Name of the jsmear node to create.\n";
    help += "-help (-h)           N/A        Display this text.\n";
    MGlobal::displayInfo(help);
}

jSmearCmd::jSmearCmd() : name_("jSmear#") {
}


MSyntax jSmearCmd::newSyntax() {
    MSyntax syntax;

    syntax.addFlag(kNameFlagShort, kNameFlagLong, MSyntax::kString);

    // Allows between 1 and 255 objects to be deformed
    syntax.setObjectType(MSyntax::kSelectionList, 1, 255);
    syntax.useSelectionAsDefault(true);

    return syntax;
}


void* jSmearCmd::creator() {
    return new jSmearCmd;
}


bool jSmearCmd::isUndoable() const {
    return true;
}


MStatus jSmearCmd::doIt(const MArgList& args) {
    MStatus status;

    MGlobal::displayInfo("entering jSmearCmd::doIt");

    status = GatherCommandArguments(args);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    status = GetGeometryPaths();
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MString command = "deformer -type jSmear -n \"" + name_ + "\"";

    // Add all of the meshes to be driven
    for (unsigned int i = 0; i < pathDriven_.length(); ++i) {
        MFnDagNode fnDriven(pathDriven_[i]);
        command += " " + fnDriven.partialPathName();
    }

    MGlobal::displayInfo("Running: " + command);

    status = dgMod_.commandToExecute(command);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    return redoIt();
}

MStatus jSmearCmd::GetGeometryPaths() {
    MStatus status;

    MGlobal::displayInfo("entering jSmearCmd::GetGeometryPaths");

    MItSelectionList iter(selectionList_);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    pathDriven_.clear();

    MGlobal::displayInfo("Items Selected: " + selectionList_.length());

    for (unsigned int i = 0; i < selectionList_.length(); ++i, iter.next()) {
        MDagPath path;
        MObject component;
        iter.getDagPath(path, component);

        MGlobal::displayInfo("Getting Shape Node of :" + path.fullPathName());

        status = GetShapeNode(path);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        pathDriven_.append(path);
  }
  return MS::kSuccess;
}

MStatus jSmearCmd::GatherCommandArguments(const MArgList& args){
    MStatus status;

    MGlobal::displayInfo("entering jSmearCmd::GatherCommandArguments");

    MArgDatabase argData(syntax(), args);
    argData.getObjects(selectionList_);

    if (argData.isFlagSet(kHelpFlagShort)) {
        DisplayHelp();
        return MS::kSuccess;
    } else if (argData.isFlagSet(kNameFlagShort)){
        name_ = argData.flagArgumentString(kNameFlagShort, 0, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
    }

    return MS::kSuccess;
}

MStatus jSmearCmd::redoIt(){
    MStatus status;

    status = dgMod_.doIt();
    CHECK_MSTATUS_AND_RETURN_IT(status);
    return MS::kSuccess;
}


MStatus jSmearCmd::undoIt(){
    MStatus status;
    status = dgMod_.undoIt();
    CHECK_MSTATUS_AND_RETURN_IT(status);
    return MS::kSuccess;
}
