#include "jSmearDeformer.h"
#include <maya/MItGeometry.h>

MTypeId jSmear::id(0x0011580B);

const char* jSmear::kName = "jSmear";

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
