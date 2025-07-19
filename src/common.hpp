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
#include <maya/MFloatArray.h>

#include <map>
#include <vector>
#include <set>

/* Convenience macros for logging.
 * Verbosity can be defined by setting LOG_LEVEL during compilation.
 *
 * 1: Only errors are logged.
 * 2: Errors and info messages are logged.
 * 3: Errors, info, and debug messages are logged.
*/
#if LOG_LEVEL > 0
#define ERROR_LOG 1
#endif

#if LOG_LEVEL > 1
#define INFO_LOG 1
#endif

#if LOG_LEVEL > 2
#define DEBUG_LOG 1
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

/**
  Creates a rotation matrix based on three points of a triangle.
  @param[in] a First point of the triangle.
  @param[in] b Second point of the triangle.
  @param[in] c Third point of the triangle.
  @param[out] m The computed rotation matrix.
*/
void RotationMatrixFromTri(const MPoint &a, const MPoint &b, const MPoint &c, MMatrix &m);

MPoint deCasteljau(const std::vector<MPoint> &points, float t);
MPoint evaluateBezierPatch(const std::vector<MPoint> &controlPoints, float u, float v);
