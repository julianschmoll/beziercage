#include "cageDeformer/cageCmd.hpp"
#include "cageDeformer/cageDeformer.hpp"
#include "offsetPin/offsetPin.hpp"
#include "offsetPin/offsetCmd.hpp"
#include "common.hpp"

#include <maya/MFnPlugin.h>
#include <maya/MMessage.h>
#include <maya/MDGMessage.h>

static MCallbackId connectionCallbackId = 0;


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

  status = plugin.registerCommand(offsetCmd::kName, offsetCmd::creator, offsetCmd::newSyntax);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  connectionCallbackId = MDGMessage::addConnectionCallback(connectionMonitorCallback, nullptr, &status);
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

  status = plugin.deregisterCommand(offsetCmd::kName);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  status = plugin.deregisterNode(offsetPin::id);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  if (connectionCallbackId != 0) {
    status = MMessage::removeCallback(connectionCallbackId);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    connectionCallbackId = 0;
  }

  MThreadPool::release();

  MGlobal::displayInfo("Uninitialized cage");

  return status;
}
