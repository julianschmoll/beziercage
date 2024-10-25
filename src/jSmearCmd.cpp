#include "jSmearCmd.h"

#include <maya/MArgDatabase.h>
#include <maya/MSyntax.h>

const char* jSmearCmd::kName = "jSmear";

jSmearCmd::jSmearCmd() {
}


MSyntax jSmearCmd::newSyntax() {
    MSyntax syntax;
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
    return redoIt();
}

MStatus jSmearCmd::redoIt(){
    MStatus status;
    return MS::kSuccess;
}


MStatus jSmearCmd::undoIt(){
    MStatus status;
    return MS::kSuccess;
}
