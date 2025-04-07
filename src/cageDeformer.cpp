#include "cageDeformer.hpp"


// This ID is registered with Autodesk and should not clash with other nodes.
MTypeId cage::id(0x0013f8c0);

MObject cage::aTime;
MObject cage::aNormalOffset;
MObject cage::aAngleMagnitude;
MObject cage::aStartFrame;
MObject cage::aSmearFrames;
MObject cage::aMinSmearVelocity;
MObject cage::aMaxSmearVelocity;
MObject cage::aWorldMatrix;

const char *cage::kName = "cage";


MStatus cage::initialize() {
    MFnMatrixAttribute mAttr;
    MFnNumericAttribute nAttr;
    MFnUnitAttribute uAttr;
    MStatus status;

    aTime = uAttr.create("time", "time", MFnUnitAttribute::kTime, 0.0);
    addAttribute(aTime);
    attributeAffects(aTime, outputGeom);

    aWorldMatrix = mAttr.create("worldMatrix", "worldMatrix");
    addAttribute(aWorldMatrix);
    attributeAffects(aWorldMatrix, outputGeom);

    aSmearFrames = nAttr.create("smearFrames", "smearFrames", MFnNumericData::kInt, 1, &status);
    nAttr.setMin(1);
    nAttr.setMax(100);
    nAttr.setKeyable(true);
    addAttribute(aSmearFrames);
    attributeAffects(aSmearFrames, outputGeom);

    aMinSmearVelocity = nAttr.create("minVelocity", "minVelocity", MFnNumericData::kDouble, 0, &status);
    nAttr.setMin(0.0);
    nAttr.setKeyable(true);
    addAttribute(aMinSmearVelocity);
    attributeAffects(aMinSmearVelocity, outputGeom);

    aMaxSmearVelocity = nAttr.create("maxVelocity", "maxVelocity", MFnNumericData::kDouble, 5, &status);
    nAttr.setMin(0.0);
    nAttr.setKeyable(true);
    addAttribute(aMaxSmearVelocity);
    attributeAffects(aMaxSmearVelocity, outputGeom);

    // add attribute to make shape of smear editable

    // Makes the deformer weight paintable
    MGlobal::executeCommand("makePaintable -attrType multiFloat -sm deformer cage weights");

    return MS::kSuccess;
}


cage::cage() {
    m_initialized = false;
    MThreadPool::init();
}


cage::~cage() {
    MThreadPool::release();
}


void *cage::creator() {
    return new cage();
}


MStatus cage::deform(MDataBlock &data, MItGeometry &itGeo, const MMatrix &localToWorldMatrix,
                       unsigned int geomIndex) {
    MStatus status;

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


bool cage::isUndoable() const {
    return false;
}

MStatus cage::doIt(const MArgList &args) {
    MStatus status;
    return redoIt();
}

MStatus cage::redoIt() {
    MStatus status;
    return MS::kSuccess;
}


MStatus cage::undoIt() {
    MStatus status;
    return MS::kSuccess;
}
