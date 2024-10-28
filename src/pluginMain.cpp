#include "jSmearDeformer.h"
#include "jSmearCmd.h"

#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>

MStatus initializePlugin(MObject obj) { 
  MStatus status;
  MFnPlugin plugin(obj, "Julian Schmoll", "1.0", "Any");

  status = plugin.registerNode(jSmear::kName, jSmear::id, jSmear::creator, jSmear::initialize, MPxNode::kDeformerNode);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  status = plugin.registerCommand(jSmearCmd::kName, jSmearCmd::creator, jSmearCmd::newSyntax);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  return status;
}

MStatus uninitializePlugin(MObject obj) {
  MStatus status;
  MFnPlugin plugin(obj);

  status = plugin.deregisterCommand(jSmearCmd::kName);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  status = plugin.deregisterNode(jSmear::id);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  return status;
}
