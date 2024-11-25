# include "jSmearDeformer.h"


// This ID is registered with Autodesk and should not clash with other nodes.
MTypeId jSmear::id(0x13f8c0);

MObject jSmear::aTime;
MObject jSmear::aNormalOffset;
MObject jSmear::aAngleMagnitude;
MObject jSmear::aStartFrame;
MObject jSmear::aSmearFrames;
MObject jSmear::aMinSmearVelocity;
MObject jSmear::aMaxSmearVelocity;
MObject jSmear::aWorldMatrix;

const char* jSmear::kName = "jSmear";


MStatus jSmear::initialize() {
    MFnMatrixAttribute      mAttr;
    MFnNumericAttribute     nAttr;
    MFnUnitAttribute        uAttr;
    MStatus				    status;

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

    // make shape editable here somehow

    // Makes the deformer weight paintable
    MGlobal::executeCommand("makePaintable -attrType multiFloat -sm deformer jSmear weights");

    return MS::kSuccess;
}


jSmear::jSmear() {
	m_initialized = false;
	MThreadPool::init();
}


jSmear::~jSmear() {
	MThreadPool::release();
}


void* jSmear::creator() {
    return new jSmear();
}


MStatus jSmear::deform(MDataBlock& data, MItGeometry& itGeo, const MMatrix& localToWorldMatrix, unsigned int geomIndex) {
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


bool jSmear::isUndoable() const {
    return false;
}

MStatus jSmear::doIt(const MArgList& args) {
    MStatus status;
    return redoIt();
}

MStatus jSmear::redoIt(){
    MStatus status;
    return MS::kSuccess;
}


MStatus jSmear::undoIt(){
    MStatus status;
    return MS::kSuccess;
}
