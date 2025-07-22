#include "cageCmd.hpp"
#include "cageDeformer.hpp"
#include "offsetPin.hpp"
#include "common.hpp"

#include <maya/MFnPlugin.h>


MStatus initializePlugin(MObject obj) {
  MStatus status;
  MFnPlugin plugin(obj, "Julian Schmoll", "1.0", "Any");

  status = plugin.registerNode(bezierCage::typeName, bezierCage::id, bezierCage::creator, bezierCage::initialize,
                               MPxNode::kDeformerNode);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  status = plugin.registerCommand(cageCmd::kName, cageCmd::creator, cageCmd::newSyntax);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  status = plugin.registerNode(offsetPin::typeName, offsetPin::id, offsetPin::creator, offsetPin::initialize);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  MThreadPool::init();

  MGlobal::displayInfo("Initialized cage");

  return status;
}

MStatus uninitializePlugin(MObject obj) {
  MStatus status;
  MFnPlugin plugin(obj);

  status = plugin.deregisterCommand(cageCmd::kName);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  status = plugin.deregisterNode(bezierCage::id);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  status = plugin.deregisterNode(offsetPin::id);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  MThreadPool::release();

  MGlobal::displayInfo("Uninitialized cage");

  return status;
}
