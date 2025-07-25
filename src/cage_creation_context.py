# We need to use the Maya API 2.0 for the viewport context to work in viewport 2.0.
import maya.api.OpenMaya as om
import maya.api.OpenMayaUI as omui
import maya.api.OpenMayaRender as omr

# As the other script run in API 1.0, we also import it here :(
from maya import OpenMaya
from maya import OpenMayaUI

from maya import cmds

try:
    from cage.cage_creator import CageCreator
except ImportError:
    CageCreator = None

kRadiusPressedCommandName = "CageMergeRadius"
kRadiusReleasedCommandName = "CageMergeRadiusReleased"
kRadiusPressedCommand = "CageMergeRadiusCommand"
kRadiusReleasedCommand = "CageMergeRadiusReleasedCommand"
kHotkeySetName = "CageCreatorHotkeys"


# this function tells maya that this plugin uses the new API
def maya_useNewAPI():
    pass


class CageCreationContext(omui.MPxContext):

    def __init__(self, cage_creator, name="CageCreatorContext"):
        super(CageCreationContext, self).__init__()
        self.setCursor(omui.MCursor.kCrossHairCursor)
        self.setImage("creation_context_32.png", 0)
        self.setTitleString("Cage Creation Tool")
        self.cage_creator = cage_creator
        self.start_position = None
        self.offset_distance = 0.1
        self.circle_diameter = 0.0
        self.original_b_pressed_command = None
        self.original_b_released_command = None
        self.job_ids = []
        self.name = name

    def toolOnSetup(self, event):
        cmds.undoInfo(openChunk=True)
        om.MGlobal.selectCommand(om.MSelectionList())

        if not cmds.hotkeySet(kHotkeySetName, exists=True):
            cmds.hotkeySet(kHotkeySetName, source='Maya_Default')

        cmds.hotkeySet(kHotkeySetName, current=True, edit=True)

        self.original_b_pressed_command = cmds.hotkey("b", query=True, name=True)
        self.original_b_released_command = cmds.hotkey("b", query=True, releaseName=True)

        if cmds.runTimeCommand(kRadiusPressedCommandName, q=True, exists=True):
            cmds.runTimeCommand(kRadiusPressedCommandName, e=True, delete=True)
        if cmds.runTimeCommand(kRadiusReleasedCommandName, q=True, exists=True):
            cmds.runTimeCommand(kRadiusReleasedCommandName, e=True, delete=True)

        count = cmds.assignCommand(query=True, numElements=True)
        for index in range(1, count + 1):
            if cmds.assignCommand(index, query=True, name=True) == kRadiusPressedCommand:
                cmds.assignCommand(edit=True, delete=index)
            if cmds.assignCommand(index, query=True, name=True) == kRadiusReleasedCommand:
                cmds.assignCommand(edit=True, delete=index)

        cmds.hotkey(k="b", alt=False, name="", releaseName="")

        cmds.runTimeCommand(
            kRadiusPressedCommandName,
            ann=kRadiusPressedCommandName,
            category='Custom Scripts',
            command='from maya import cmds;cmds.optionVar(intValue=("radiusToggle", True))',
            commandLanguage='python'
        )

        cmds.runTimeCommand(
            kRadiusReleasedCommandName,
            ann=kRadiusReleasedCommandName,
            category='Custom Scripts',
            command='from maya import cmds;cmds.optionVar(intValue=("radiusToggle", False))',
            commandLanguage='python'
        )

        cmds.nameCommand(kRadiusPressedCommand, ann=kRadiusPressedCommand, command=kRadiusPressedCommandName)
        cmds.nameCommand(kRadiusReleasedCommand, ann=kRadiusReleasedCommand, command=kRadiusReleasedCommandName)

        cmds.hotkey(k="b", alt=False, ctl=False, name=kRadiusPressedCommand)
        cmds.hotkey(k="b", alt=False, ctl=False, rn=kRadiusReleasedCommand)

        self.cage_creator.offset_distance = self.offset_distance

        self.undo_redo_script_job()

    def toolOffCleanup(self):
        if not cmds.hotkeySet(kHotkeySetName, exists=True):
            cmds.hotkeySet(kHotkeySetName, source='Maya_Default')

        cmds.hotkeySet(kHotkeySetName, current=True, edit=True)
        cmds.hotkey(k="b", alt=False, name="", releaseName="")
        cmds.hotkey(
            k="b",
            alt=False,
            ctl=False,
            name=self.original_b_pressed_command,
            releaseName=self.original_b_released_command
        )
        self.undo_redo_script_job(register=False)

        self.completeAction()
        self.cage_creator.undo_stack = []
        self.cage_creator.redo_stack = []
        cmds.undoInfo(closeChunk=True)

    def doPress(self, event, draw_manager, frame_context):
        if cmds.optionVar(q="radiusToggle"):
            self.start_position = event.position
            return

        self.start_position = None
        self.add_point(event)

    def add_point(self, event):
        x, y = event.position
        position = OpenMaya.MPoint()
        direction = OpenMaya.MVector()
        cam_dag_path = OpenMaya.MDagPath()
        view = OpenMayaUI.M3dView.active3dView()
        intersections = []
        view.viewToWorld(int(x), int(y), position, direction)
        view.getCamera(cam_dag_path)
        camera_matrix = cam_dag_path.inclusiveMatrix()

        intersection = calculate_closest_intersection(
            cam_dag_path, camera_matrix, direction, intersections, position, self.offset_distance
        )

        if not intersection:
            return

        cmds.undoInfo(openChunk=True)
        try:
            self.cage_creator.add_point(*intersection)
        finally:
            cmds.undoInfo(closeChunk=True)

    def undo_redo_script_job(self, register=True):
        if self.job_ids:
            for job_id in self.job_ids:
                cmds.scriptJob(kill=job_id, force=True)
            self.job_ids = []
        if register:
            self.job_ids.append(
                cmds.scriptJob(
                    event=["Undo", lambda: self.cage_creator.undo()],
                    killWithScene=True,
                )
            )
            self.job_ids.append(
                cmds.scriptJob(
                    event=["Redo", lambda: self.cage_creator.redo()],
                    killWithScene=True,
                )
            )

    def doDrag(self, event, draw_manager, frame_context):
        if cmds.optionVar(q="radiusToggle"):
            current_position = event.position
            dx = current_position[0] - self.start_position[0]
            dy = current_position[1] - self.start_position[1]
            self.circle_diameter = (dx ** 2 + dy ** 2) ** 0.5 * 2

            start_point = om.MPoint(self.start_position[0], self.start_position[1], 0)

            draw_manager.beginDrawable()
            draw_manager.setColor(om.MColor((120 / 255.0, 204 / 255.0, 239 / 255.0)))
            draw_manager.setLineStyle(omr.MUIDrawManager.kSolid)
            draw_manager.setLineWidth(2)
            draw_manager.circle2d(start_point, self.circle_diameter / 2, False)
            draw_manager.endDrawable()

            zoom_fac = get_camera_distance_to_center_of_interest()

            self.cage_creator.set_proximity_threshold(self.circle_diameter * (zoom_fac / 4000.0))

    def completeAction(self):
        self.cage_creator.create()


class CageCreationContextCmd(omui.MPxContextCommand):
    COMMAND_NAME = "CageCreatorContext"
    cage_creators = {}
    cage_name = None

    def __init__(self):
        super(CageCreationContextCmd, self).__init__()

    def makeObj(self):
        argParser = self.parser()
        if argParser.isFlagSet("-name"):
            self.cage_name = argParser.flagArgumentString("-name", 0)
        if self.cage_name:
            if self.cage_name in self.cage_creators:
                cage_creator = self.cage_creators[self.cage_name]
            else:
                cage_creator = CageCreator(cage_name=self.cage_name)
                self.cage_creators[self.cage_name] = cage_creator
        else:
            cage_creator = CageCreator(cage_name="default_cage")
        return CageCreationContext(cage_creator, name=self.cage_name)

    @classmethod
    def creator(cls):
        return CageCreationContextCmd()

    def appendSyntax(self):
        syntax = self.syntax()
        syntax.addFlag("-n", "-name", om.MSyntax.kString)

    def doEditFlags(self):
        argParser = self.parser()
        if argParser.isFlagSet("-name"):
            self.cage_name = argParser.flagArgumentString("-name", 0)

    def doQueryFlags(self):
        argParser = self.parser()
        if argParser.isFlagSet("-name"):
            return self.cage_name
        return None


def calculate_closest_intersection(cam_dag_path, camera_matrix, direction, intersections, position, offset_distance=0.1):
    for mesh in get_viewport_meshes(cam_dag_path):
        result = raycast_mesh_intersection(direction, mesh, position, camera_matrix)

        if result:
            matrix, dist = result
            intersections.append((dist, mesh, matrix))

    if not intersections:
        return None

    _, mesh, matrix = min(intersections, key=lambda distance: distance[0])

    transformation_matrix = OpenMaya.MTransformationMatrix(matrix)
    translation = transformation_matrix.getTranslation(OpenMaya.MSpace.kWorld)
    transformation_matrix.setTranslation(
        OpenMaya.MVector(translation.x, translation.y, translation.z + offset_distance), OpenMaya.MSpace.kWorld
    )

    return transformation_matrix.asMatrix(), mesh


def get_viewport_zoom():
    view = OpenMayaUI.M3dView.active3dView()
    cam_dag_path = OpenMaya.MDagPath()
    view.getCamera(cam_dag_path)

    camera_fn = OpenMaya.MFnCamera(cam_dag_path)
    view_width = view.portWidth()
    view_height = view.portHeight()

    horizontal_fov = camera_fn.horizontalFieldOfView()
    vertical_fov = camera_fn.verticalFieldOfView()

    zoom_x = view_width / (2 * horizontal_fov)
    zoom_y = view_height / (2 * vertical_fov)

    return zoom_x, zoom_y


def get_camera_distance_to_center_of_interest():
    view = OpenMayaUI.M3dView.active3dView()
    cam_dag_path = OpenMaya.MDagPath()
    view.getCamera(cam_dag_path)

    camera_fn = OpenMaya.MFnCamera(cam_dag_path)
    camera_position = camera_fn.eyePoint(OpenMaya.MSpace.kWorld)
    center_of_interest = camera_fn.centerOfInterestPoint(OpenMaya.MSpace.kWorld)

    return (camera_position - center_of_interest).length()


def get_viewport_meshes(cam_dag_path):
    """Returns a list of meshes currently visible in the viewport.

    Args:
        cam_dag_path (OpenMaya.MDagPath): Path to the camera geometry

    Returns:
        visible_meshes: list of mesh names
    """
    draw_traversal = OpenMayaUI.MDrawTraversal()
    draw_traversal.setFrustum(
        cam_dag_path,
        cmds.getAttr("defaultResolution.width"),
        cmds.getAttr("defaultResolution.height")
    )
    draw_traversal.traverse()
    visible_meshes = []

    for item_idx in range(draw_traversal.numberOfItems()):
        shape_dag_path = OpenMaya.MDagPath()
        draw_traversal.itemPath(item_idx, shape_dag_path)

        if shape_dag_path.hasFn(OpenMaya.MFn.kMesh):
            visible_meshes.append(shape_dag_path)

    return visible_meshes


def raycast_mesh_intersection(direction, mesh, position, camera_matrix):
    """Finds the intersection point of a ray with a mesh.

    Args:
        direction (OpenMaya.MVector): Direction of the ray.
        mesh (str): Name of the mesh to intersect with.
        position (OpenMaya.MPoint): Starting point of the ray.
        camera_matrix (OpenMaya.MMatrix): Camera matrix.

    Returns:
        OpenMaya.MFloatPoint: The intersection point if found, otherwise None.
        float: The distance from the ray source to the intersection point.
    """
    fn_mesh = OpenMaya.MFnMesh(mesh)
    hit_point = OpenMaya.MFloatPoint()
    hit_ray_param = OpenMaya.MScriptUtil()
    hit_ray_param_ptr = hit_ray_param.asFloatPtr()
    hit_face = OpenMaya.MScriptUtil()
    hit_face_ptr = hit_face.asIntPtr()
    hit_triangle = OpenMaya.MScriptUtil()
    hit_triangle_ptr = hit_triangle.asIntPtr()
    hit_bary1 = OpenMaya.MScriptUtil()
    hit_bary1_ptr = hit_bary1.asFloatPtr()
    hit_bary2 = OpenMaya.MScriptUtil()
    hit_bary2_ptr = hit_bary2.asFloatPtr()

    # as function does not take keyword arguments,
    # they are added as a comment for readability
    intersection = fn_mesh.closestIntersection(
        OpenMaya.MFloatPoint(position),  # raySource
        OpenMaya.MFloatVector(direction),  # rayDirection
        None,  # faceIds
        None,  # triIds
        False,  # idsSorted
        OpenMaya.MSpace.kWorld,  # space
        99999,  # maxParam
        False,  # testBothDirections
        None,  # accelParams
        hit_point,  # hitPoint
        hit_ray_param_ptr,  # hitRayParam
        hit_face_ptr,  # hitFace
        hit_triangle_ptr,  # hitTriangle
        hit_bary1_ptr,  # hitBary1
        hit_bary2_ptr  # hitBary2
    )

    if not intersection:
        return None

    distance = OpenMaya.MScriptUtil.getFloat(hit_ray_param_ptr)
    up_vector = OpenMaya.MVector(camera_matrix(0, 0), camera_matrix(0, 1), camera_matrix(0, 2))

    mat = build_surface_matrix(
        fn_mesh,
        OpenMaya.MScriptUtil.getInt(hit_face_ptr),
        OpenMaya.MScriptUtil.getInt(hit_triangle_ptr),
        OpenMaya.MPoint(hit_point),
        up_vector
    )

    return mat, distance


def build_surface_matrix(fn_mesh, face_id, tri_id, hit_point, up_vector):
    """Builds a transformation matrix for the surface at the intersection point.

    Args:
        fn_mesh (OpenMaya.MFnMesh): The mesh function set.
        face_id (int): The ID of the face where the intersection occurred.
        tri_id (int): The ID of the triangle within the face.
        hit_point (OpenMaya.MPoint): The point of intersection in world space.
        up_vector (OpenMaya.MVector): Up Vector for rotation matrix.

    Returns:
        OpenMaya.MMatrix: The transformation matrix for the surface.
    """
    tris_cnt = OpenMaya.MIntArray()
    tris_vtx = OpenMaya.MIntArray()
    fn_mesh.getTriangles(tris_cnt, tris_vtx)

    offset = sum(tris_cnt[i] for i in range(face_id)) * 3
    idx = offset + tri_id * 3
    vert_idxs = [tris_vtx[idx + i] for i in range(3)]

    verts = []
    for vert_id in vert_idxs:
        pt = OpenMaya.MPoint()
        fn_mesh.getPoint(vert_id, pt, OpenMaya.MSpace.kWorld)
        verts.append(pt)

    a, b, c = verts
    normal = (b - a) ^ (c - a)
    if normal.length() < 1e-8:
        normal = OpenMaya.MVector(0.0, 0.0, 1.0)
    normal.normalize()

    mat = rotation_matrix_from_normal(normal, up_vector=up_vector)
    tm = OpenMaya.MTransformationMatrix(mat)
    tm.setTranslation(OpenMaya.MVector(hit_point), OpenMaya.MSpace.kWorld)

    return tm.asMatrix()


def rotation_matrix_from_normal(normal, up_vector=OpenMaya.MVector(0.0, 1.0, 0.0)):
    """Creates a rotation matrix from a normal vector and an up vector.

    Args:
        normal (OpenMaya.MVector): The normal vector of the surface.
        up_vector (OpenMaya.MVector): The up vector to define the orientation.

    Returns:
        OpenMaya.MMatrix: The rotation matrix aligning the normal with the up vector.
    """
    if abs(normal * up_vector) > 0.999:
        # If up_vector is parallel to normal, choose a different axis.
        # The world X-axis is a common choice, but check if it's also parallel.
        if abs(normal.x) > 0.999:
            up_vector = OpenMaya.MVector(0.0, 1.0, 0.0)  # Use Y-axis
        else:
            up_vector = OpenMaya.MVector(1.0, 0.0, 0.0)  # Use X-axis

    tangent = (up_vector ^ normal).normal()
    bitangent = (normal ^ tangent).normal()

    lst = [
        tangent.x,   tangent.y,   tangent.z,   0.0,
        bitangent.x, bitangent.y, bitangent.z, 0.0,
        -normal.x,   -normal.y,   -normal.z,   0.0,
        0.0,         0.0,         0.0,         1.0
    ]
    matrix = OpenMaya.MMatrix()
    OpenMaya.MScriptUtil.createMatrixFromList(lst, matrix)

    return matrix


def initializePlugin(plugin):
    plugin_fn = om.MFnPlugin(plugin, "Julian Schmoll", "1.0", "Any")
    if not CageCreator:
        om.MGlobal.displayError("CageCreator module is not available. Please make sure plugin is loaded correctly.")
        return

    if om.MGlobal.mayaState() == om.MGlobal.kInteractive :
        try:
            import cage.menu
            cage.menu.create()
        except:
            om.MGlobal.displayWarning("Could not add cage Menu")

    try:
        plugin_fn.registerContextCommand(CageCreationContextCmd.COMMAND_NAME,
                                         CageCreationContextCmd.creator)
    except:
        om.MGlobal.displayError("Failed to register context command: %s"
                                % CageCreationContextCmd.COMMAND_NAME)


def uninitializePlugin(plugin):
    plugin_fn = om.MFnPlugin(plugin)

    if om.MGlobal.mayaState() == om.MGlobal.kInteractive :
        try:
            import cage.menu
            cage.menu.destroy()
        except:
            om.MGlobal.displayWarning("Could not remove cage Menu")

    try:
        plugin_fn.deregisterContextCommand(CageCreationContextCmd.COMMAND_NAME)
    except:
        om.MGlobal.displayError("Failed to deregister context command: %s"
                                % CageCreationContextCmd.COMMAND_NAME)
