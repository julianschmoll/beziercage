#include "cageDeformer.hpp"


// This ID is registered with Autodesk and should not clash with other nodes.
MTypeId bezierCage::id(0x0013f8c0);

const char *bezierCage::typeName = "bezierCage";


MStatus bezierCage::initialize() {
    // Makes the deformer weight paintable
    // MGlobal::executeCommand("makePaintable -attrType multiFloat -sm deformer bezierCage weights");

    return MS::kSuccess;
}

void *bezierCage::creator() {
    return new bezierCage();
}


MStatus bezierCage::deform(MDataBlock &dataBlock, MItGeometry &geometryIterator, const MMatrix &localToWorldMatrix,
                     unsigned int geometryIndex) {

    // get velocity vector of each vert first
    // get normalized velocity vector as well (by dividing each component by the original length)

    // get normal vector of each vert

    // calculate dot product between normalized vel vector and normal vector
    // if this dot product is less or equal to zero we can leave vert where it is

    // if not, we want to move it it in the opposite direction of velocity vector
    // to make sure verts are moved further, if they are closer in the direction of vel vector,
    // we want to multiply by dot product

    return MS::kSuccess;
}
