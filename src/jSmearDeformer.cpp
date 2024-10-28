#include "jSmearDeformer.h"
#include <maya/MItGeometry.h>

/* According to https://mayaid.autodesk.io/ the numeric range 0 - 0x7ffff
(524288 ids) is reserved for plugins that will be internal. Since
registration is mostly for companies, this is a random number in this range. */
MTypeId jSmear::id(0x6ccc);

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
