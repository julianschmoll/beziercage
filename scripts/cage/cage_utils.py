from maya import cmds

import math


def get_connected_plugs(node_attr):
    """Retrieves connected plugs from node attribute.

    Args:
        node_attr (str): The node attribute.

    Returns:
        connected_plugs (list of str): The connected plugs.
    """
    return cmds.listConnections(node_attr, s=True, d=False, plugs=True) or []


def get_next_available_idx(node_attr):
    """Returns next available index for node attribute.

    Args:
        node_attr (str): The node attribute.

    Returns:
        int: The next available index.
    """
    existing = cmds.getAttr(node_attr, multiIndices=True) or []
    return max(existing) + 1 if existing else 0


def connect_pin_node(pinned, mesh_dag_path):
    """Connects object to be pinned.

    Args:
        pinned (OpenMaya.MObject): The pinned object.
        mesh_dag_path (OpenMaya.MDagPath): The mesh dag path.
    """
    control_node = "baryPinNode"
    if not cmds.objExists(control_node):
        control_node = cmds.createNode("CageControlNode", name=control_node)

    shape_name = mesh_dag_path.partialPathName()
    input_geometry = f"{control_node}.inputGeometry"

    if f"{shape_name}.worldMesh" not in get_connected_plugs(input_geometry):
        cmds.connectAttr(
            f"{shape_name}.worldMesh[0]",
            f"{input_geometry}[{get_next_available_idx(input_geometry)}]",
            force=True
        )

    original_geometry = f"{control_node}.originalGeometry"
    if f"{shape_name}.outMesh" not in get_connected_plugs(original_geometry):
        cmds.connectAttr(
            f"{shape_name}.outMesh",
            f"{original_geometry}[{get_next_available_idx(original_geometry)}]",
            force=True
        )

    output_matrix = f"{control_node}.outputMatrix"
    plug_index = get_next_available_idx(output_matrix)

    matrix = cmds.getAttr(f"{pinned}.worldMatrix[0]")
    cmds.setAttr(
        f"{control_node}.inputMatrix[{plug_index}]", *matrix, type="matrix"
    )
    cmds.connectAttr(
        f"{output_matrix}[{plug_index}]",
        f"{pinned}.offsetParentMatrix",
        force=True
    )


def is_close(proximity_threshold, point1, point2):
    """Checks if two points are within the proximity threshold.

    Args:
        proximity_threshold (float): The distance threshold to consider points close.
        point1 (OpenMaya.MPoint): First point.
        point2 (OpenMaya.MPoint): Second point.

    Returns:
        bool: True if points are close, False otherwise.
    """
    return (point1 - point2).length() <= proximity_threshold


def draw_display_line(controls, name="displayLine", override_type=2, override_enabled=True):
    """Draws a display line between two controls.

    Args:
        controls: list of controls or a tuple of two controls (anchor, handle).
        name (str): Name of the display curve.
        override_type (int): Override type for the display curve.
        override_enabled (bool): Whether to enable the override.

    Returns:
        str: Name of the created display curve.
    """
    if not len(controls) > 1:
        raise ValueError("At least two controls are required to draw a display line.")

    points = []
    dcmps = []
    degree = len(controls)-1

    for control in controls:
        dcmp = f"{control}_dcmp"
        if not cmds.objExists(dcmp):
            cmds.createNode("decomposeMatrix", name=dcmp)
        dcmps.append(dcmp)

        already_connected = cmds.listConnections(
            f"{dcmp}.inputMatrix", source=True, destination=False
        )
        if not already_connected:
            cmds.connectAttr(f"{control}.worldMatrix[0]", f"{dcmp}.inputMatrix", force=True)

        points.append(cmds.getAttr(f"{dcmp}.outputTranslate")[0])

    display_curve = cmds.curve(
        d=degree,
        p=points,
        name=name
    )

    if degree > 2:
        cmds.displaySmoothness(
            display_curve,
            divisionsU=3,
            divisionsV=3,
            pointsWire=16,
            pointsShaded=4,
            polygonObject=3
        )

    for idx, dcmp in enumerate(dcmps):
        cmds.connectAttr(
            f"{dcmp}.outputTranslate", f"{display_curve}.cv[{idx}]", force=True)

    cmds.setAttr(f"{display_curve}.overrideDisplayType", override_type)
    cmds.setAttr(f"{display_curve}.overrideEnabled", override_enabled)

    return display_curve
