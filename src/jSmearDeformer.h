#ifndef JSMEARDEFORMER_H
#define JSMEARDEFORMER_H

#include <maya/MPxDeformerNode.h>


class jSmear : public MPxDeformerNode {
    public:
        jSmear();
        virtual 
        virtual MStatus doIt(const MArgList&);
        virtual MStatus undoIt();
        virtual MStatus redoIt();
        virtual bool isUndoable() const;
        static void* creator();
        static MSyntax newSyntax();

        const static char* kName;
    
};
#endif
