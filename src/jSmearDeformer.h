#ifndef JSMEARDEFORMER_H
#define JSMEARDEFORMER_H


#include <maya/MPlug.h>
#include <maya/MPoint.h>
#include <maya/MPointArray.h>
#include <maya/MMatrix.h>
#include <maya/MTypeId.h>
#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MArrayDataHandle.h>
#include <maya/MFloatArray.h>
#include <maya/MDoubleArray.h>
#include <maya/MIntArray.h>
#include <maya/MGlobal.h>
#include <maya/MTime.h>
#include <maya/MThreadPool.h>
#include <maya/MVector.h>
#include <maya/MVectorArray.h>

#include <maya/MItGeometry.h>

#include <maya/MPxDeformerNode.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnMessageAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MFnGenericAttribute.h>
#include <maya/MFnPointArrayData.h>
#include <maya/MFnDoubleArrayData.h>
#include <maya/MFnIntArrayData.h>
#include <maya/MFnMesh.h>
#include <maya/MFnNurbsSurface.h>
#include <maya/MFnNurbsCurve.h>
#include <maya/MFnSubd.h>
#include <maya/MFnData.h>
#include <array>



class jSmear : public MPxDeformerNode {
    public:
        jSmear();
        virtual	~jSmear();
        virtual MStatus doIt(const MArgList&);
        virtual MStatus undoIt();
        virtual MStatus redoIt();
        virtual bool isUndoable() const;
        static void* creator();
        static  MStatus initialize();
        static MSyntax newSyntax();
        virtual MStatus deform(MDataBlock& block, MItGeometry& iter, const MMatrix& mat, unsigned int multiIndex);
        const static char* kName;

        static MObject aDriverGeo; //driven geometry for deformer
        static MObject aBindData;
        static MObject aSampleComponents; //Vertex IDs
        static MObject aSampleWeights; // Vertex weights
        static MObject aBindMatrix;
        static MTypeId id;
        static MObject aTime;
        static MObject aStartFrame;
        static MObject aMinSmearVelocity;
        static MObject aMaxSmearVelocity;
        static MObject aWorldMatrix;
        static MObject aSmearFrames;
        static MObject aNormalOffset;
        static MObject aAngleMagnitude;

    private:
        bool m_initialized;
};
#endif
