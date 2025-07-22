from maya import cmds

from bezier_cage_playground.scripts.cage_creator import control
from bezier_cage_playground.scripts.cage_creator import cage_utils


class BezierControl:
    def __init__(self, matrix, mesh, name="anchor_0", cage_name="cage"):
        """Initializes the BezierControl."""
        self.cage_name = cage_name
        self.name = self.generate_unique_name(name)
        self.matrix = [matrix(i, j) for i in range(4) for j in range(4)]
        self.position = (matrix(3, 0), matrix(3, 1), matrix(3, 2))
        self.handles = []
        self.handle_group = None
        self.anchor = self._create_anchor_control()
        self.mesh = mesh.fullPathName() if hasattr(mesh, 'fullPathName') else mesh

    def _create_anchor_control(self):
        """Creates the anchor control for the Bézier curve."""
        if not cmds.objExists(self.cage_name):
            cmds.group(empty=True, name=self.cage_name)

        anchor_control = control.create(
            "box", name=f"{self.name}_ctl", line_width=3, color=[0.744, 0.0, 0.867]
        )

        group = cmds.group(anchor_control["null"], name=f"{self.name}")
        cmds.xform(anchor_control["srt"], ws=True, matrix=self.matrix)
        cmds.parent(group, self.cage_name)
        self.handle_group = cmds.group(empty=True, name=f"{self.name}_handles")
        cmds.parent(self.handle_group, self.name)
        cmds.xform(self.handle_group, ws=True, matrix=self.matrix)

        cmds.connectAttr(
            f"{anchor_control['srt']}.worldMatrix[0]",
            f"{self.handle_group}.offsetParentMatrix"
        )

        return anchor_control

    def add_handle(self, matrix):
        """Adds a handle to the Bezier control.

        Args:
            OpenMaya.MMatrix matrix: Matrix of the handle in world space.

        Returns:
            str: Name of the created handle control.
        """
        cage_display = f"{self.cage_name}_display"
        handle_display = f"{self.name}_handle_display"
        point = (matrix(3, 0), matrix(3, 1), matrix(3, 2))

        if not cmds.objExists(f"{self.cage_name}|{cage_display}"):
            cage_display = cmds.group(empty=True, name=cage_display)
            cmds.parent(cage_display, self.cage_name)

        if not cmds.objExists(f"{self.cage_name}|{cage_display}|{handle_display}"):
            handle_display = cmds.group(empty=True, name=handle_display)
            cmds.parent(handle_display, cage_display)

        handle_count = len(self.handles)
        handle_control = control.create(
            "box",
            name=f"{self.name}_handle_{handle_count}_ctl",
            size=0.2,
            line_width=1.5,
            color=[0.364, 0.014, 1.0]
        )
        matrix_list = [matrix(i, j) for i in range(4) for j in range(4)]
        cmds.parent(handle_control["null"], self.handle_group)
        cmds.xform(handle_control["srt"], ws=True, matrix=matrix_list)

        offset_group = cmds.group(
            handle_control["ctl"], name=f"{self.name}_handle_{handle_count}_offset"
        )
        cmds.xform(
            offset_group,
            pivots=(self.matrix[12], self.matrix[13], self.matrix[14]),
            worldSpace=True
        )
        cmds.connectAttr(
            f"{self.anchor['ctl']}.translate", f"{offset_group}.translate"
        )
        cmds.connectAttr(
            f"{self.anchor['ctl']}.rotate", f"{offset_group}.rotate"
        )
        cmds.connectAttr(
            f"{self.anchor['ctl']}.scale", f"{offset_group}.scale"
        )
        display_curve = cage_utils.draw_display_line(
            [self.anchor["ctl"], handle_control["ctl"]],
            name=f"{self.name}_handle_{handle_count}_display_crv"
        )
        cmds.parent(display_curve, handle_display)
        self.handles.append(
            {
                "name": handle_control,
                "display": display_curve,
                "matrix": matrix_list,
                "point": point
            }
        )

        for attr in ["scaleX", "scaleY", "scaleZ", "rotateX", "rotateY", "rotateZ"]:
            cmds.setAttr(f"{handle_control['ctl']}.{attr}", lock=1, k=0)

        return handle_control

    def generate_unique_name(self, name):
        """Generates a unique name by appending an index to the base name."""
        base_name = f"{self.cage_name}_{name}"
        if cmds.objExists(base_name):
            base_name = "_".join(base_name.split("_")[:-1])
            index = 0
            while cmds.objExists(f"{base_name}_{index}"):
                index += 1
            return f"{base_name}_{index}"
        return base_name
