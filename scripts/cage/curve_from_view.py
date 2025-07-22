from maya import OpenMaya
from maya import OpenMayaUI
from maya import cmds

import numpy as np


def dag_path_from_name(name):
    """Returns DAG path from name.

    Args:
        name (str): The name of the node.

    Returns:
        OpenMaya.MDagPath: The DAG path.
    """
    sel = OpenMaya.MSelectionList()
    sel.add(name)
    dag = OpenMaya.MDagPath()
    sel.getDagPath(0, dag)
    return dag


def sample_curve_points(curve_name, num_samples=10):
    """Samples points from a curve.

    Args:
        curve_name (str): The name of the curve.
        num_samples (int): The number of points to sample.

    Returns:
        list of tuple: List of points.
    """
    dag = dag_path_from_name(curve_name)
    curve_fn = OpenMaya.MFnNurbsCurve(dag)

    knot_array = OpenMaya.MDoubleArray()
    curve_fn.getKnots(knot_array)
    start, end = knot_array[0], knot_array[knot_array.length() - 1]
    step = (end - start) / float(num_samples - 1)

    points = []
    for i in range(num_samples):
        param = start + i * step
        point = OpenMaya.MPoint()
        curve_fn.getPointAtParam(param, point, OpenMaya.MSpace.kWorld)
        points.append((point.x, point.y, point.z))

    return points


def bernstein_matrix(t_values):
    """Returns Bernstein matrix.

    Args:
        t_values (list): List of t values.

    Returns:
        np.ndarray: Bernstein matrix.
    """
    B = []
    for t in t_values:
        B.append([
            (1 - t) ** 3,
            3 * t * (1 - t) ** 2,
            3 * t ** 2 * (1 - t),
            t ** 3
        ])
    return np.array(B)


def fit_bezier_least_squares(points):
    """Fits a Bézier curve to points with least squares.

    Args:
        points (list): List of points.

    Returns:
        list of tuple: List of points.
    """
    t_values = np.linspace(0, 1, len(points))
    B = bernstein_matrix(t_values)
    P = np.array(points)
    control_points = np.linalg.lstsq(B, P, rcond=None)[0]
    return [tuple(pt) for pt in control_points]


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


def raycast_mesh_intersection(direction, mesh, position):
    """Finds the intersection point of a ray with a mesh.

    Args:
        direction (OpenMaya.MVector): Direction of the ray.
        mesh (str): Name of the mesh to intersect with.
        position (OpenMaya.MPoint): Starting point of the ray.

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

    return OpenMaya.MPoint(hit_point), distance


def project_curve_from_view(start_point, end_point, num_ctrl_points=100, display_curve=False):
    """Projects a curve from start_point to end_point.

    Args:
        start_point (OpenMaya.MPoint): Starting point of the curve.
        end_point (OpenMaya.MPoint): Ending point of the curve.
        num_ctrl_points (int): Number of control points.
        display_curve (bool): Whether the curve should be created in viewport.

    Returns:
        list of tuple: The curve points
    """
    view = OpenMayaUI.M3dView.active3dView()
    cam_path = OpenMaya.MDagPath()
    view.getCamera(cam_path)

    cam_matrix = cam_path.inclusiveMatrix()
    cam_transform = OpenMaya.MTransformationMatrix(cam_matrix)
    cam_position = cam_transform.getTranslation(OpenMaya.MSpace.kWorld)

    control_points = []
    start_vec = OpenMaya.MVector(start_point)
    end_vec = OpenMaya.MVector(end_point)

    meshes = get_viewport_meshes(cam_path)

    for i in range(num_ctrl_points):
        t = float(i) / (num_ctrl_points - 1)
        interp_vec = start_vec * (1.0 - t) + end_vec * t
        world_point = OpenMaya.MPoint(interp_vec)
        direction = OpenMaya.MVector(world_point - cam_position).normal()

        closest_distance = float('inf')
        closest_pos = None

        for mesh in meshes:
            result = raycast_mesh_intersection(direction, mesh, cam_position)
            if not result:
                continue
            pos, distance = result
            if distance < closest_distance:
                closest_distance = distance
                closest_pos = pos

        if closest_pos:
            control_points.append((closest_pos.x, closest_pos.y, closest_pos.z))
        else:
            control_points.append((world_point.x, world_point.y, world_point.z))

    if display_curve:
        cmds.curve(degree=3, p=control_points, name="projectedCurve")

    return control_points


def get_bezier_points(start_point, end_point, display_curve=False):
    """Creates a Bézier curve from start_point to end_point on viewport surfaces.

    Args:
        start_point (OpenMaya.MPoint): Starting point of the curve.
        end_point (OpenMaya.MPoint): Ending point of the curve.
        display_curve (bool): Whether the curve should be created in viewport.

    Returns:
        list of tuple: The bezier control points.
    """
    original_curve_points = project_curve_from_view(start_point, end_point, display_curve=display_curve)
    bezier_control_points = fit_bezier_least_squares(original_curve_points)
    if display_curve:
        cmds.curve(degree=3, p=bezier_control_points, name="bezierCurve")
    return bezier_control_points
