import json
import os
import logging
from maya import cmds

LOGGER = logging.getLogger("Rig Control")


def create_ctl_from_json(file_path, name, ctl_size=1.0, line_width=1.0, color=[1, 0, 0], parent_structure=True):
    """Create a control from definition in a json file.

    Args:
        file_path (str): Path to the json file.
        name (str): Name of the control.
        ctl_size (float): Control size.
        line_width (float): Line width.
        color (list): Color.

    Returns:
        str: Name of created control.
    """
    with open(file_path, "r") as f:
        shape_data = json.load(f)

    shape_list = []
    base_name = "_".join(name.split("_")[:-1])

    for shape in shape_data:
        degree = shape.get("degree", 3)
        new_curve = cmds.curve(degree=degree, point=shape["points"])
        if shape.get("closed", True):
            cmds.closeCurve(new_curve, ch=False, ps=False, rpo=True)
        shape_list.append(cmds.rename(new_curve, shape["name"]))

    ctl = shape_list.pop(0)

    for shape in shape_list:
        shapes = cmds.listRelatives(shape, shapes=True, fullPath=True)
        cmds.parent(shapes, ctl, add=True, shape=True)
        cmds.delete(shape)

    cmds.scale(ctl_size, ctl_size, ctl_size, ctl)
    cmds.makeIdentity(ctl, apply=True, t=1, r=1, s=1, n=0)
    cmds.xform(ctl, zeroTransformPivots=True)
    ctl = cmds.rename(ctl, name, ignoreShape=True)
    colorize(ctl, color)

    srt = cmds.group(ctl, name=f"{base_name}_srt")
    null = cmds.group(srt, name=f"{base_name}_null")

    # This seems to be buggy depending on which maya i use
    cmds.setAttr(f"{ctl}.lineWidth", line_width)

    return {
        "null": null,
        "srt": srt,
        "ctl": ctl,
    }


def colorize(control, color=[1, 0, 0]):
    """Colorizes a control with given color.

    Args:
        control (str): Name of control.
        color (list): Color.
    """
    is_rgb = isinstance(color, (tuple, list))
    color_attribute = "overrideColorRGB" if is_rgb else "overrideColor"
    for shape in cmds.listRelatives(control, shapes=True, fullPath=True) or []:
        cmds.setAttr(f"{shape}.overrideEnabled", 1)
        cmds.setAttr(f"{shape}.overrideRGBColors", is_rgb)
        cmds.setAttr(f"{shape}.{color_attribute}", *color, type="double3" if is_rgb else "long")


def create(ctl_type, name="ctl", size=.4, line_width=1.0, color=[1, 0, 0], parent_structure=True):
    """Creates the specified control type.

    Args:
        ctl_type (str): Type of control.
        name (str): Name of control.
        size (float): Size of control.
        line_width (float): Line width of control.
        color (list): Color.

    Returns:
        str: Name of created control.
    """
    script_dir = os.path.dirname(__file__)
    json_dir = os.path.join(script_dir, "control_definitions")
    json_path = os.path.join(json_dir, f"{ctl_type}.json")

    if not os.path.exists(json_path):
        raise ValueError(f"Control type '{ctl_type}' not found in {json_dir}")

    LOGGER.info(f"Creating {ctl_type} control from json")
    return create_ctl_from_json(
        json_path, name, ctl_size=size, line_width=line_width, color=color, parent_structure=parent_structure
    )
