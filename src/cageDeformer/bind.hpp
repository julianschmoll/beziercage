#pragma once

#include "bind.hpp"

#include <array>
#include <vector>

#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMessageAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MGlobal.h>
#include <maya/MArrayDataBuilder.h>
#include <maya/MArrayDataHandle.h>
#include <maya/MFnNumericData.h>
#include <maya/MStatus.h>
#include <maya/MPlug.h>
#include <maya/MPoint.h>
#include <maya/MVector.h>
#include <maya/MMatrix.h>
#include <maya/MItGeometry.h>
#include <maya/MDataBlock.h>
#include <maya/MObject.h>
#include <maya/MTypeId.h>
#include <maya/MPxDeformerNode.h>
#include <maya/MThreadPool.h>

#include <LBFGSB.h>
#include <Eigen/Core>

#include <thread>
#include <vector>

/// Functor that computes the squared distance from a point on a cubic Bezier patch
/// to a fixed target point, together with its gradient w.r.t. the (u, v) parameters.
///
/// Intended for use with LBFGSpp as the objective in findBindingUV().
class BezierPatchDistance {
public:
    BezierPatchDistance(const std::vector<MPoint> &controlPoints, const MPoint &targetPoint);

    /// Evaluate the patch surface at (u, v).
    [[nodiscard]] MPoint evaluate(double u, double v) const;

    /// Compute the first-order partial derivatives of the patch surface at (u, v).
    void derivatives(double u, double v, MVector &dPdu, MVector &dPdv) const;

    /// LBFGSpp-compatible call operator.
    /// Returns squared distance; writes the 2-element gradient into @p gradient.
    double operator()(const Eigen::VectorXd &uv, Eigen::VectorXd &gradient);

private:
    // Cubic Bezier basis functions evaluated at @p t.
    static std::array<double, 4> bernstein(double t);

    // First derivative of the cubic Bezier basis at @p t.
    static std::array<double, 4> bernsteinDerivative(double t);

    const std::vector<MPoint> &patchControlPoints;
    const MPoint              &targetPoint;

    static constexpr int uDegree = 3;
    static constexpr int vDegree = 3;
};
