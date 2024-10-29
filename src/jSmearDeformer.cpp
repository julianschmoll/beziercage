#include "jSmearDeformer.h"
#include <maya/MItGeometry.h>
#include <maya/MFnCompoundAttribute.h>

// This ID is registered with Autodesk and should not clash with other nodes.
MTypeId jSmear::id(0x13f8c0);

const char* jSmear::kName = "jSmear";
// declare static attributes (MObject jSmear::aDriverGeo; ...)


MStatus jSmear::initialize() {
    return MS::kSuccess;
}


jSmear::jSmear() {
}


jSmear::~jSmear() {
}


void* jSmear::creator() {
    return new jSmear();
}

MStatus jSmear::deform(MDataBlock& data, MItGeometry& itGeo, const MMatrix& localToWorldMatrix, unsigned int geomIndex) {
    MStatus status;
    return MS::kSuccess;
}
