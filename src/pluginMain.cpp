#include "jSmearCmd.h"
#include "jSmearDeformer.h"

#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>

MStatus initializePlugin(MObject obj) {
  MStatus status;
  MFnPlugin plugin(obj, "Julian Schmoll", "1.0", "Any");

  status = plugin.registerNode(jSmear::kName, jSmear::id, jSmear::creator, jSmear::initialize, MPxNode::kDeformerNode);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  status = plugin.registerCommand(jSmearCmd::kName, jSmearCmd::creator, jSmearCmd::newSyntax);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  MGlobal::displayInfo("Initialized jSmear");

  if (MGlobal::mayaState() == MGlobal::kInteractive) {
    MGlobal::executePythonCommandOnIdle("from maya.api.OpenMaya import MGlobal");
    MGlobal::executePythonCommandOnIdle(
      "try:import jsmear.menu;jsmear.menu.create()\nexcept:MGlobal.displayWarning('Could not add jSmear Menu')");
  }

  return status;
}

MStatus uninitializePlugin(MObject obj) {
  MStatus status;
  MFnPlugin plugin(obj);

  status = plugin.deregisterCommand(jSmearCmd::kName);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  status = plugin.deregisterNode(jSmear::id);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  if (MGlobal::mayaState() == MGlobal::kInteractive) {
    MGlobal::executePythonCommandOnIdle("from maya.api.OpenMaya import MGlobal");
    MGlobal::executePythonCommandOnIdle(
      "try:import jsmear.menu;jsmear.menu.destroy()\nexcept:MGlobal.displayWarning('Could not remove jSmear Menu')");
  }

  return status;
}
