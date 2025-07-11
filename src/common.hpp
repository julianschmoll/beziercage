/**
  Contains various helper functions.
*/

#pragma once

#include "cageCmd.hpp"
#include "cageDeformer.hpp"

#include <maya/MDagPath.h>
#include <maya/MDoubleArray.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MIntArray.h>
#include <maya/MMatrix.h>
#include <maya/MPoint.h>
#include <maya/MPointArray.h>
#include <maya/MString.h>
#include <maya/MGlobal.h>
#include <maya/MStreamUtils.h>

#include <map>
#include <vector>
#include <set>

#ifdef DEBUG
    #define DEBUG_MSG(x) MStreamUtils::stdOutStream() << x << "\n";
#else
#define DEBUG_MSG(x)
#endif

/**
  Checks if provided path is for a shape node.
  @param[in] path the dag path.
  @return true if provided path is for a shape node.
 */
bool IsShapeNode(MDagPath &path);


/**
  Sets dag path to shape node path from transform.
  @param[in,out] path Path to a dag node.
  @param[in] intermediate setting to get intermediate nodes.
  @return MStatus.
 */
MStatus GetShapeNode(MDagPath &path, bool intermediate = false);


/**
  Gets Dag Path of an object by name.
  @param[in] name Name of a dag node.
  @param[out] path Storage for the dag path.
 */
MStatus GetDagPath(MString &name, MDagPath &path);


/**
  Delete intermediate shape nodes of the given dag path.
  @param[in] path DagPath.
 */
MStatus DeleteIntermediateObjects(MDagPath &path);

/**
  Calculates the barycentric coordinates of a point P in the triangle specified by points A,B,C.
  @param[in] p The sample point.
  @param[in] a Triangle point.
  @param[in] b Triangle point.
  @param[in] c Triangle point.
  @param[out] coords Barycentric coordinates.
*/
void GetBarycentricCoordinates(const MPoint &p, const MPoint &a, const MPoint &b, const MPoint &c, MFloatArray &coords);

MStatus GetDagPathFromMesh(const MObject &meshObj, MDagPath &dagPath);

void RotationMatrixFromTri(const MPoint &a, const MPoint &b, const MPoint &c, MMatrix &m);
