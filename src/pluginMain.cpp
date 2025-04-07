#include "cageCmd.hpp"
#include "cageDeformer.hpp"
#include "cageMesh.hpp"

#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>

MStatus initializePlugin(MObject obj) {
  MStatus status;
  MFnPlugin plugin(obj, "Julian Schmoll", "1.0", "Any");

  status = plugin.registerNode(cage::kName, cage::id, cage::creator, cage::initialize, MPxNode::kDeformerNode);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  status = plugin.registerCommand(cageCmd::kName, cageCmd::creator, cageCmd::newSyntax);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  status = plugin.registerNode("animCube", animCube::id, animCube::creator, animCube::initialize);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  if (MGlobal::mayaState() == MGlobal::kInteractive) {
    MGlobal::executePythonCommandOnIdle("from maya.api.OpenMaya import MGlobal");
    MGlobal::executePythonCommandOnIdle(
      "try:import cage.menu;cage.menu.create()\nexcept:MGlobal.displayWarning('Could not add cage Menu')");
  }

  MGlobal::displayInfo("Initialized cage");

  return status;
}

MStatus uninitializePlugin(MObject obj) {
  MStatus status;
  MFnPlugin plugin(obj);

  status = plugin.deregisterCommand(cageCmd::kName);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  status = plugin.deregisterNode(cage::id);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  status = plugin.deregisterNode(animCube::id);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  if (MGlobal::mayaState() == MGlobal::kInteractive) {
    MGlobal::executePythonCommandOnIdle("from maya.api.OpenMaya import MGlobal");
    MGlobal::executePythonCommandOnIdle(
      "try:import cage.menu;cage.menu.destroy()\nexcept:MGlobal.displayWarning('Could not remove cage Menu')");
  }

  MGlobal::displayInfo("Uninitialized cage");

  return status;
}
