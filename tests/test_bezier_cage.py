from maya import cmds
from pathlib import Path
import tempfile
from tests import decorators

import unittest

SUBDIVISIONS = 200
CONTROL_PATCHES = [
    [
        "test_cage_anchor_0_ctl",
        "test_cage_anchor_0_handle_0_ctl",
        "test_cage_anchor_1_handle_0_ctl",
        "test_cage_anchor_1_ctl",
        "test_cage_anchor_0_handle_1_ctl",
        "test_cage_anchor_1_handle_1_ctl",
        "test_cage_anchor_3_handle_1_ctl",
        "test_cage_anchor_2_handle_0_ctl",
        "test_cage_anchor_3_ctl",
        "test_cage_anchor_3_handle_0_ctl",
        "test_cage_anchor_2_handle_1_ctl",
        "test_cage_anchor_2_ctl",
    ],
    [
        "test_cage_anchor_0_ctl",
        "test_cage_anchor_0_handle_2_ctl",
        "test_cage_anchor_4_handle_0_ctl",
        "test_cage_anchor_4_ctl",
        "test_cage_anchor_0_handle_1_ctl",
        "test_cage_anchor_4_handle_1_ctl",
        "test_cage_anchor_3_handle_1_ctl",
        "test_cage_anchor_5_handle_0_ctl",
        "test_cage_anchor_3_ctl",
        "test_cage_anchor_3_handle_2_ctl",
        "test_cage_anchor_5_handle_1_ctl",
        "test_cage_anchor_5_ctl",
    ],
    [
        "test_cage_anchor_0_ctl",
        "test_cage_anchor_0_handle_0_ctl",
        "test_cage_anchor_1_handle_0_ctl",
        "test_cage_anchor_1_ctl",
        "test_cage_anchor_0_handle_3_ctl",
        "test_cage_anchor_1_handle_2_ctl",
        "test_cage_anchor_7_handle_1_ctl",
        "test_cage_anchor_6_handle_0_ctl",
        "test_cage_anchor_7_ctl",
        "test_cage_anchor_7_handle_0_ctl",
        "test_cage_anchor_6_handle_1_ctl",
        "test_cage_anchor_6_ctl",
    ],
    [
        "test_cage_anchor_0_ctl",
        "test_cage_anchor_0_handle_3_ctl",
        "test_cage_anchor_7_handle_1_ctl",
        "test_cage_anchor_7_ctl",
        "test_cage_anchor_0_handle_2_ctl",
        "test_cage_anchor_7_handle_2_ctl",
        "test_cage_anchor_4_handle_0_ctl",
        "test_cage_anchor_8_handle_0_ctl",
        "test_cage_anchor_4_ctl",
        "test_cage_anchor_4_handle_2_ctl",
        "test_cage_anchor_8_handle_1_ctl",
        "test_cage_anchor_8_ctl",
    ]
]
PLUGINS = ["cage", "cage_creation_context"]


class TestBezierCage(unittest.TestCase):
    @decorators.plugin_loaded(PLUGINS)
    def test_bezier_cage(self):
        test_file = Path(Path(__file__).parent.parent, "data", "cage_plane_test.ma")
        cmds.file(test_file, open=1, force=True)
        temp_file = Path(tempfile.gettempdir(), "temp.ma")
        cmds.file(rename=temp_file)

        test_mesh = cmds.polyPlane(
            height=14,
            name="pp",
            subdivisionsX=SUBDIVISIONS,
            subdivisionsY=SUBDIVISIONS,
            width=14
        )[0]
        cmds.move(0, -0.1, 0, test_mesh)
        cmds.setAttr(f"{test_mesh}.overrideEnabled", 1)
        cmds.setAttr(f"{test_mesh}.overrideDisplayType", 2)

        deformer = cmds.deformer(test_mesh, type="bezierCage")[0]
        control_node = cmds.createNode("offsetPin")
        connect_control_node(control_node, deformer)

        anchor_points = set()
        for patch in CONTROL_PATCHES:
            for control in patch:
                if not "handle" in control:
                    anchor_points.add(control)

        for idx, point in enumerate(sorted(anchor_points)):
            offset_grp = point.replace("ctl", "srt")
            matrix = cmds.getAttr(f"{offset_grp}.worldMatrix[0]")
            cmds.setAttr(
                f"{control_node}.inputMatrix[{idx}]", *matrix, type="matrix"
            )
            cmds.connectAttr(
                f"{control_node}.outputMatrix[{idx}]",
                f"{offset_grp}.offsetParentMatrix"
            )

        for patch_idx, patch in enumerate(CONTROL_PATCHES):
            for point_idx, point in enumerate(patch):
                point_srt = point.replace("ctl", "srt")
                cmds.connectAttr(
                    f"{point}.worldMatrix[0]",
                    f"{deformer}.patchMatrices[{patch_idx}].Matrix[{point_idx}]"
                )
                cmds.connectAttr(
                    f"{point_srt}.worldMatrix[0]",
                    f"{deformer}.patchBindPreMatrices[{patch_idx}].bindPreMatrix[{point_idx}]"
                )
        joint = cmds.joint(position=(0, 0, 0), name="joint1")
        skin_cluster = cmds.skinCluster(joint, test_mesh, name="skinCluster1")[0]

        cmds.reorderDeformers(deformer, skin_cluster, test_mesh)

        # we just check the first bind UV to see if it is set correctly
        bind_uv = cmds.getAttr(f"{deformer}.gbd[0].vbd[0].bindUV")
        assert bind_uv == [(1.0, 1.0)]

        # we also check the first bind offset vector as the cage is in 0.1 y distance from the mesh, y should be 0.1
        bind_offset_vector = cmds.getAttr(f"{control_node}.bindData[0].bindOffsetVector")
        assert bind_offset_vector == [(0.0, 0.1, 0.0)]


def connect_control_node(control_node, deformer):
    """Connects the control node with matching inputs from deformer.

    Args:
        control_node (str): The name of the control node to connect.
        deformer (str): The name of the deformer to mimic connections.
    """
    for index in cmds.getAttr(f"{deformer}.input", multiIndices=True) or []:
        mesh_plug = cmds.listConnections(
            f"{deformer}.input[{index}].inputGeometry",
            s=True,
            d=False,
            plugs=True
        )[0] or None
        if not mesh_plug:
            continue
        cmds.connectAttr(
            mesh_plug, f"{control_node}.inputGeometry[{index}]", force=True
        )

    for index in cmds.getAttr(f"{deformer}.originalGeometry", multiIndices=True) or []:
        mesh_plug = cmds.listConnections(
            f"{deformer}.originalGeometry[{index}]",
            s=True,
            d=False,
            plugs=True
        )[0] or None
        if not mesh_plug:
            continue
        cmds.connectAttr(
            mesh_plug, f"{control_node}.originalGeometry[{index}]", force=True
        )
    cmds.connectAttr(f"{control_node}.message", f"{deformer}.controlMessage", force=True)
