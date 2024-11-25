#include "jSmearCmd.h"

#include <maya/MArgDatabase.h>
#include <maya/MSyntax.h>

const char* jSmearCmd::kName = "jSmear";
const char* jSmearCmd::kNameFlagShort = "-n";
const char* jSmearCmd::kNameFlagLong = "-name";

jSmearCmd::jSmearCmd() : name_("jSmear#") {
}


MSyntax jSmearCmd::newSyntax() {
    MSyntax syntax;

    syntax.addFlag(kNameFlagShort, kNameFlagLong, MSyntax::kString);
    syntax.setObjectType(MSyntax::kSelectionList, 0, 255);
    syntax.useSelectionAsDefault(true);

    return syntax;
}


void* jSmearCmd::creator() {
    return new jSmearCmd;
}


bool jSmearCmd::isUndoable() const {
    return false;
}


MStatus jSmearCmd::doIt(const MArgList& args) {
    MStatus status;

    // Get geo
    status = GatherCommandArguments(args);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    // get geometry paths

    // create deformer

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
}

MStatus jSmearCmd::redoIt(){
    MStatus status;
    return MS::kSuccess;
}


MStatus jSmearCmd::undoIt(){
    MStatus status;
    return MS::kSuccess;
}
