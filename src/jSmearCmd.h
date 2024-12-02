#ifndef JSMEARCMD_H
#define JSMEARCMD_H

#include <maya/MSelectionList.h>
#include <maya/MDagPath.h>
#include <maya/MDagPathArray.h>
#include <maya/MPlug.h>
#include <maya/MString.h>
#include <maya/MStringArray.h>
#include <maya/MGlobal.h>
#include <maya/MSyntax.h>
#include <maya/MString.h>
#include <maya/MArgList.h>
#include <maya/MArgDatabase.h>
#include <maya/MObject.h>
#include <maya/MDGModifier.h>

#include <maya/MItGeometry.h>
#include <maya/MItDependencyGraph.h>

#include <maya/MFnDagNode.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFn.h>
#include <maya/MFnData.h>
#include <maya/MFnMesh.h>
#include <maya/MFnTransform.h>

#include <maya/MPxCommand.h>

class jSmearCmd : public MPxCommand {
    public:
        jSmearCmd();
        static void* creator();
        static MStatus initialize();
        virtual MStatus	doIt(const MArgList&);
        virtual MStatus undoIt();
        virtual MStatus redoIt();
        virtual bool isUndoable() const;

        const static char* kName;
        const static char* kNameFlagShort;
        const static char* kNameFlagLong;
        const static char* kHelpFlagShort;
        const static char* kHelpFlagLong;

        static MTypeId id;
        static MSyntax newSyntax();

    private:
        MStatus GatherCommandArguments(const MArgList& args);
        MString name_;
        MDagPathArray drivenGeometry_;
        MDGModifier dgMod_;
        MObject jSmearNode_;
};
#endif
