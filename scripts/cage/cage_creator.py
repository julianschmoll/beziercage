import copy
from maya import OpenMaya
from maya import cmds
import logging
import json

from cage.bezier_control import BezierControl
from cage import curve_from_view
from cage import cage_utils


LOGGER = logging.getLogger("Cage Creator")


class CageCreator:
    """A class to create a cage for deforming objects in Maya.

    Attributes:
        proximity_threshold (float): The distance threshold to merge points.
        cage_name (str): The name of the cage to be created.
        points (list): List of BezierControl points in the cage.
        edge_data (list): List of edges in the cage, each edge is a tuple of point indices.
        patches_controls (list): List of maya transforms for each patch.
        current_patch_edge_tuples (list): List of edge tuples for the current patch being created.
        current_patch_anchors (list): List of point indices for the current patch.
        current_edge_anchors (list): List of point indices for the current edge being created.
        undo_stack (list): Stack to keep track of undo states.
        redo_stack (list): Stack to keep track of redo states.
    """
    def __init__(self, proximity_threshold=1, cage_name="deform_cage_0"):
        """Initializes Cage creator.

        Args:
            proximity_threshold (float): The distance to merge points.
            cage_name (str): The name of the cage to be created.
        """
        self.proximity_threshold = proximity_threshold
        self.cage_name = cage_name
        self.offset_distance = 0.1

        self.points = []
        self.edge_data = []
        self.patches_controls = []

        self.current_patch_edge_tuples = []
        self.current_patch_anchors = []
        self.current_edge_anchors = []

        self.undo_stack = []
        self.redo_stack = []

    def _current_state(self):
        """Returns the current state of the class."""
        return {
            "points": [p.to_dict() for p in self.points],
            "edge_data": copy.deepcopy(self.edge_data),
            "patches_controls": copy.deepcopy(self.patches_controls),
            "current_patch_edge_tuples": copy.deepcopy(self.current_patch_edge_tuples),
            "current_patch_anchors": copy.deepcopy(self.current_patch_anchors),
            "current_edge_anchors": copy.deepcopy(self.current_edge_anchors),
        }

    def _save_state(self):
        """Saves the current state for undo."""
        self.undo_stack.append(self._current_state())
        self.redo_stack.clear()

    def _restore_state(self, state):
        """Restores the class state from a saved snapshot.

        Args:
            state (dict): The state to restore.
        """
        self.points = [BezierControl.from_dict(p) for p in state["points"]]
        self.edge_data = state["edge_data"]
        self.patches_controls = state["patches_controls"]
        self.current_patch_edge_tuples = state["current_patch_edge_tuples"]
        self.current_patch_anchors = state["current_patch_anchors"]
        self.current_edge_anchors = state["current_edge_anchors"]

    def _create_edge_or_patch(self, idx):
        """Checks if 4 points are collected and creates a patch.

        Args:
            idx (int): Index of the last added point.
        """
        self.current_edge_anchors.append(idx)
        self.current_patch_anchors.append(idx)

        if len(self.current_edge_anchors) == 2:
            self._add_edge(self.current_edge_anchors)
            self.current_edge_anchors = [self.current_edge_anchors[-1]]

        if len(self.current_patch_anchors) == 4:
            self._add_edge([self.current_patch_anchors[-1], self.current_patch_anchors[0]])
            self._add_patch(self.current_patch_anchors)
            self.current_patch_anchors = []
            self.current_edge_anchors = []

    def _add_patch(self, point_indices):
        """Adds a patch to the cage.

        Args:
            point_indices (list of int): Indices of 4 points forming the patch.
        """
        if len(point_indices) != 4:
            raise ValueError("A patch must consist of exactly 4 points.")

        edges = [edge["edge"] for edge in self.edge_data]
        clockwise_patch_controls = []

        for edge_tuple in self.current_patch_edge_tuples:
            reversed_edge = [edge_tuple[1], edge_tuple[0]]
            if edge_tuple in edges:
                edge_index = edges.index(edge_tuple)
                edge = self.edge_data[edge_index]
                clockwise_patch_controls.extend([edge["anchor1"], edge["handle1"], edge["handle2"]])
            elif reversed_edge in edges:
                edge_index = edges.index(reversed_edge)
                edge = self.edge_data[edge_index]
                clockwise_patch_controls.extend([edge["anchor2"], edge["handle2"], edge["handle1"]])
            else:
                raise RuntimeError("Patch construction went wrong.")

        self.patches_controls.append({
            "points": point_indices[:],
            "controls": [
                clockwise_patch_controls[0],
                clockwise_patch_controls[1],
                clockwise_patch_controls[2],
                clockwise_patch_controls[3],
                clockwise_patch_controls[11],
                clockwise_patch_controls[4],
                clockwise_patch_controls[10],
                clockwise_patch_controls[5],
                clockwise_patch_controls[9],
                clockwise_patch_controls[8],
                clockwise_patch_controls[7],
                clockwise_patch_controls[6],
            ]
        })

        self.current_patch_edge_tuples = []

    def _add_edge(self, point_indices, display=True):
        """Adds an edge to the cage.

        Args:
            point_indices (list of int): Indices of 2 points forming the edge.
            display (bool): Whether to add display curve in maya.
        """
        if len(point_indices) != 2:
            raise ValueError("An edge must consist of exactly 2 points.")

        edge = point_indices

        for created_edge in self.edge_data:
            if sorted(created_edge["edge"]) == sorted(edge):
                created_edge["new"] = False
                for patch_edge in self.current_patch_edge_tuples:
                    if sorted(patch_edge) == sorted(edge):
                        LOGGER.info(f"Edge {patch_edge} already exists in the current patch.")
                        return created_edge
                LOGGER.info(f"Edge {edge} already exists.")
                self.current_patch_edge_tuples.append(edge)
                return created_edge

        anchor1, handle1, handle2, anchor2 = self._add_handles(point_indices)
        self.current_patch_edge_tuples.append(edge)
        edge_to_append = {
            "edge": edge,
            "anchor1": anchor1,
            "anchor2": anchor2,
            "handle1": handle1,
            "handle2": handle2,
            "new": True,
        }
        self.edge_data.append(edge_to_append)

        if not display:
            return edge_to_append

        display_curve = cage_utils.draw_display_line(
            [anchor1["ctl"], handle1["ctl"], handle2["ctl"], anchor2["ctl"]],
            name=f"{self.cage_name}_edge_{len(self.edge_data)}_display_crv",
            override_type=1,
        )
        edge_display = f"{self.cage_name}_edge_display"

        if not cmds.objExists(edge_display):
            cmds.group(empty=True, name=edge_display)
            cmds.parent(edge_display, f"{self.cage_name}_display")

        cmds.parent(display_curve, edge_display)

        return edge_to_append

    def _add_handles(self, point_indices):
        """Adds handles to the edge defined by the given point indices.

        Args:
            point_indices (list of int): Indices of the two points defining the edge.
        """
        point1 = self.points[point_indices[0]]
        point2 = self.points[point_indices[1]]
        _, pos1, pos2, _ = curve_from_view.get_bezier_points(
            OpenMaya.MPoint(
                point1.position[0],
                point1.position[1],
                point1.position[2] - self.offset_distance
            ),
            OpenMaya.MPoint(
                point2.position[0],
                point2.position[1],
                point2.position[2] - self.offset_distance
            ),
            display_curve=False
        )

        pos1 = (pos1[0], pos1[1], pos1[2] + self.offset_distance)
        pos2 = (pos2[0], pos2[1], pos2[2] + self.offset_distance)

        m_script_util = OpenMaya.MScriptUtil()
        point1_matrix = OpenMaya.MMatrix()
        m_script_util.createMatrixFromList(point1.matrix, point1_matrix)
        point2_matrix = OpenMaya.MMatrix()
        m_script_util.createMatrixFromList(point2.matrix, point2_matrix)

        handle1_matrix = OpenMaya.MTransformationMatrix(point1_matrix)
        handle2_matrix = OpenMaya.MTransformationMatrix(point2_matrix)

        handle1_matrix.setTranslation(
            OpenMaya.MVector(*pos1),
            OpenMaya.MSpace.kWorld
        )
        handle2_matrix.setTranslation(
            OpenMaya.MVector(*pos2),
            OpenMaya.MSpace.kWorld
        )

        handle1 = point1.add_handle(handle1_matrix.asMatrix())
        handle2 = point2.add_handle(handle2_matrix.asMatrix())

        return point1.anchor, handle1, handle2, point2.anchor

    def _update_edges_and_patches(self):
        self.current_patch_edge_tuples = []
        self.current_patch_anchors = []
        self.current_edge_anchors = []
        valid_edges = []
        for created_edge in self.edge_data:
            edge_tuple = created_edge["edge"]
            if self.points[edge_tuple[0]].valid and self.points[edge_tuple[1]].valid:
                valid_edges.append(created_edge)
            else:
                LOGGER.info(f"Removing edge {edge_tuple} due to invalid points.")
        self.edge_data = valid_edges
        valid_patches = []
        for patch in self.patches_controls:
            is_valid = all(self.points[p_idx].valid for p_idx in patch["points"])
            if is_valid:
                valid_patches.append(patch)
            else:
                LOGGER.info(f"Removing patch with points {patch['points']} due to invalid points.")
        self.patches_controls = valid_patches

    def _update_point_positions(self):
        for point in self.points:
            control = point.anchor["ctl"]
            if cmds.objExists(control):
                matrix = cmds.getAttr(f"{control}.worldMatrix[0]")
                point.matrix = matrix
                point.position = (matrix[12], matrix[13], matrix[14])
                LOGGER.info(f"Updated point {point.name} at position {point.position}")
            else:
                point.valid = False
                LOGGER.warning(f"Point {point.name} does not exist. Marking as invalid.")

    def undo(self):
        """Reverts the last operation."""
        if not self.undo_stack:
            LOGGER.warning("No more actions to undo.")
            return

        self.redo_stack.append(self._current_state())
        last_state = self.undo_stack.pop()
        self._restore_state(last_state)

    def redo(self):
        """Reapplies the last undone operation."""
        if not self.redo_stack:
            LOGGER.warning("No more actions to redo.")
            return

        self.undo_stack.append(self._current_state())
        last_state = self.redo_stack.pop()
        self._restore_state(last_state)

    def update_state(self):
        """Updates data based on the Maya scene."""
        LOGGER.info("Updating cage state...")
        state_node = f"{self.cage_name}_state_node"
        if cmds.objExists(state_node):
            json_str = cmds.getAttr(f"{state_node}.state")
            if json_str:
                self._restore_state(json.loads(json_str))
                LOGGER.info("Restored state from scene file.")
            else:
                LOGGER.warning("State node exists but has no data.")
        self._update_point_positions()
        self._update_edges_and_patches()

    def save_state_to_scenefile(self):
        json_str = json.dumps(self._current_state())
        state_node = f"{self.cage_name}_state_node"
        if not cmds.objExists(state_node):
            state_node = cmds.createNode("network", name=state_node)
            cmds.addAttr(state_node, ln="state", dt="string")
            # connect message attribute so on export the state node is exported as well
            # create message attribute on the state node
            cmds.addAttr(state_node, ln="deformMessage", at="message")
            deformer = f"{self.cage_name}_deformer"
            if cmds.objExists(deformer):
                cmds.connectAttr(f"{deformer}.message", f"{state_node}.deformMessage", force=True)

        cmds.setAttr(f"{state_node}.state", json_str, type="string")


    def add_point(self, matrix, mesh):
        """Adds a point to the cage, reusing if close to an existing point.

        Args:
            matrix (OpenMaya.MMatrix): The transformation matrix of the point.
            mesh (OpenMaya.MDagPath): The mesh to which the point will be connected.

        Returns:
            int: Index of the reused or newly added point.
        """
        self._save_state()
        cmds.select(clear=True)
        position = OpenMaya.MPoint(matrix(3, 0), matrix(3, 1), matrix(3, 2))

        for idx in self.current_patch_anchors:
            if cage_utils.is_close(
                    self.proximity_threshold,
                    position,
                    OpenMaya.MPoint(*self.points[idx].position)
            ):
                OpenMaya.MGlobal.displayWarning(
                    f"Every point in the patch must be unique."
                )
                return

        for existing_index, existing_point in enumerate(self.points):
            if not existing_point.valid:
                continue
            point_position = OpenMaya.MPoint(*existing_point.position)
            if cage_utils.is_close(self.proximity_threshold, position, point_position):
                self._create_edge_or_patch(existing_index)
                LOGGER.info(f"Reusing point at {existing_point.position}")
                cmds.select(existing_point.name)
                return

        self.points.append(BezierControl(matrix, mesh, cage_name=self.cage_name))
        LOGGER.info(f"Created point at {position.x}, {position.y}, {position.z}")
        self._create_edge_or_patch(len(self.points) - 1)
        return

    def create(self):
        """Creates the cage in Maya using the stored points and patches."""
        if not self.points:
            LOGGER.warning("No points in the cage to create.")
            return
        LOGGER.info("Creating cage with the following data:")
        LOGGER.info(f"Points: {len(self.points)}")
        LOGGER.info(f"Patches: {len(self.patches_controls)}")
        meshes = set(point.mesh for point in self.points if point.valid)
        deformer = f"{self.cage_name}_deformer"

        if not cmds.pluginInfo("cage", query=True, loaded=True):
            LOGGER.info("Loading bezierCage plugin.")
            try:
                cmds.loadPlugin("cage")
            except RuntimeError as e:
                LOGGER.error(f"Failed to load cage plugin: {e}")
                return

        if not cmds.objExists(deformer):
            LOGGER.info(f"Creating deformer {deformer} for meshes: {meshes}")
            deformer = cmds.deformCage(list(meshes), name=f"{self.cage_name}_deformer")
        else:
            connected_meshes = set(cmds.deformer(deformer,q=True, g=True))
            missing_meshes = meshes - connected_meshes
            for mesh in missing_meshes:
                LOGGER.info(f"Adding mesh {mesh} to {deformer}")
                cmds.deformer(deformer, edit=True, geometry=mesh)

        offset_pin = f"{self.cage_name}_control_node"
        if not cmds.objExists(offset_pin):
            offset_pin = cmds.createNode(
                "offsetPin", name=f"{self.cage_name}_control_node"
            )

        match_geometry_connections(offset_pin, deformer)

        for anchor in self.points:
            plug = f"{anchor.name}_srt.offsetParentMatrix"
            try:
                anchor_connected = cmds.listConnections(plug, s=True, d=False)
            except Exception as e:
                LOGGER.error(f"Error checking connections for {plug}: {e}")
                continue

            if not anchor.valid or anchor_connected:
                continue

            index = cage_utils.get_next_available_idx(f"{offset_pin}.inputMatrix")
            cmds.setAttr(f"{offset_pin}.inputMatrix[{index}]", *anchor.matrix, type="matrix")
            cmds.connectAttr(f"{offset_pin}.outputMatrix[{index}]", plug)

        for patch_idx, patch_data in enumerate(self.patches_controls):
            patch_controls = patch_data["controls"]
            for point_idx, control in enumerate(patch_controls):
                LOGGER.info(
                    f"Connecting {control['ctl']} to patch {patch_idx} and point {point_idx}"
                )
                cmds.connectAttr(
                    f"{control['ctl']}.worldMatrix[0]",
                    f"{deformer}.patchMatrices[{patch_idx}].Matrix[{point_idx}]",
                    force=True
                )
                cmds.connectAttr(
                    f"{control['srt']}.worldMatrix[0]",
                    f"{deformer}.patchBindPreMatrices[{patch_idx}].bindPreMatrix[{point_idx}]",
                    force=True
                )
        cmds.deformCage(name=deformer, rebind=True)

    def set_proximity_threshold(self, threshold):
        """Sets the proximity threshold for point reuse.

        Args:
            threshold (float): New proximity threshold.
        """
        self.proximity_threshold = threshold


def match_geometry_connections(control_node, deformer):
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
        print(f"Connecting {mesh_plug} to {control_node}.inputGeometry[{index}]")
        cmds.connectAttr(
            mesh_plug, f"{control_node}.inputGeometry[{index}]", force=True
        )
        shape_node = mesh_plug.split('.')[0]
        mesh_transform = cmds.listRelatives(shape_node, parent=True, fullPath=True)
        if not mesh_transform:
            continue
        mesh_transform = mesh_transform[0]

        orig_shape = get_orig_shape(mesh_transform)
        if orig_shape:
            print(f"Connecting {orig_shape}.worldMesh[0] to {control_node}.originalGeometry[{index}]")
            cmds.connectAttr(
                f"{orig_shape}.worldMesh[0]",
                f"{control_node}.originalGeometry[{index}]",
                force=True
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


def get_orig_shape(mesh):
    shapes = cmds.listRelatives(mesh, shapes=True, fullPath=True) or []
    for shape in shapes:
        if cmds.getAttr(f"{shape}.intermediateObject"):
            return shape
    return None
