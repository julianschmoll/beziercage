/**
  Contains various helper functions.
*/

#ifndef cage_COMMON_HPP
#define cage_COMMON_HPP

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
#include <map>
#include <vector>
#include <set>


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

#endif
