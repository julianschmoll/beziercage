#ifndef JSMEARDEFORMER_H
#define JSMEARDEFORMER_H


#include <maya/MPxDeformerNode.h>
#include <maya/MItGeometry.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MGlobal.h>


class jSmear : public MPxDeformerNode {
    public:
        jSmear();
        virtual
        virtual MStatus doIt(const MArgList&);
        virtual MStatus undoIt();
        virtual MStatus redoIt();
        virtual bool isUndoable() const;
        static void* creator();
        static  MStatus initialize();
        static MSyntax newSyntax();
        virtual MStatus deform(MDataBlock& data, MItGeometry& iter, const MMatrix& mat,
                           unsigned int mIndex);
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
};
#endif
