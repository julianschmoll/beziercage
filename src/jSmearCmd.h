#ifndef JSMEARCMD_H
#define JSMEARCMD_H

#include <maya/MArgList.h>
#include <maya/MPxCommand.h>


class jSmearCmd : public MPxCommand {
    public:
        jSmearCmd();
        virtual ~jSmear();
        virtual MStatus deform(MDataBlock& data, MItGeometry& iter, const MMatrix& mat, unsigned int mIndex);
        static void* creator();
        static MStatus initialize();

        const static char* kName;
        static MTypeId id;

};
#endif
