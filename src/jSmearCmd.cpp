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

    status = dgMod_.commandToExecute(command);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    return redoIt();
}

// implement function to get geo paths (selectionlist dag paths and then shape nodes from that)
// method to get shape node as well

MStatus jSmearCmd::GatherCommandArguments(const MArgList& args){
    MStatus status;

    MArgDatabase argData(syntax(), args);

    if (argData.isFlagSet(kNameFlagShort)){
        name_ = argData.flagArgumentString(kNameFlagShort, 0, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
    }

    return MS::kSuccess;
}

MStatus jSmearCmd::redoIt(){
    MStatus status;
    return MS::kSuccess;
}


MStatus jSmearCmd::undoIt(){
    MStatus status;
    status = dgMod_.undoIt();
    CHECK_MSTATUS_AND_RETURN_IT(status);
    return MS::kSuccess;
}
