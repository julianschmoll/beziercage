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
// declare static attributes (MObject jSmear::aDriverGeo; ...)


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

    aStartFrame = nAttr.create("startFrame", "startFrame", MFnNumericData::kInt, 0, &status);
    nAttr.setKeyable(true);
    addAttribute(aStartFrame);

    aSmearFrames = nAttr.create("smearFrames", "smearFrames", MFnNumericData::kInt, 1, &status);
    nAttr.setMin(1);
    nAttr.setMax(100);
    nAttr.setKeyable(true);
    addAttribute(aSmearFrames);
    attributeAffects(aSmearFrames, outputGeom);

    aNormalOffset = nAttr.create("normalOffset", "normalOffset", MFnNumericData::kFloat, 0.0, &status);
    nAttr.setMin(0.0);
    nAttr.setKeyable(true);
    addAttribute(aNormalOffset);
    attributeAffects(aNormalOffset, outputGeom);

    aAngleMagnitude = nAttr.create("angleMagnitude", "angleMagnitude", MFnNumericData::kFloat, 1.0, &status);
    nAttr.setMin(0.0);
    nAttr.setKeyable(true);
    addAttribute(aAngleMagnitude);
    attributeAffects(aAngleMagnitude, outputGeom);

    aMinSmearVelocity = nAttr.create("minSmearVelocity", "minSmearVelocity", MFnNumericData::kDouble, 0, &status);
    nAttr.setMin(0.0);
    nAttr.setKeyable(true);
    addAttribute(aMinSmearVelocity);
    attributeAffects(aMinSmearVelocity, outputGeom);

    aMaxSmearVelocity = nAttr.create("maxSmearVelocity", "maxSmearVelocity", MFnNumericData::kDouble, 5, &status);
    nAttr.setMin(0.0);
    nAttr.setKeyable(true);
    addAttribute(aMaxSmearVelocity);
    attributeAffects(aMaxSmearVelocity, outputGeom);

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
