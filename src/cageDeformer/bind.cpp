#include "bind.hpp"

std::array<double, 4> BezierPatchDistance::bernstein(const double t) {
    const double s = 1.0 - t;
    return {s * s * s, 3.0 * t * s * s, 3.0 * t * t * s, t * t * t};
}

std::array<double, 4> BezierPatchDistance::bernsteinDerivative(const double t) {
    const double s = 1.0 - t;
    return {-3.0 * s * s, 3.0 * s * (s - 2.0 * t), 3.0 * t * (2.0 * s - t), 3.0 * t * t};
}

BezierPatchDistance::BezierPatchDistance(const std::vector<MPoint> &controlPoints, const MPoint &targetPoint)
    : patchControlPoints(controlPoints), targetPoint(targetPoint) {}

MPoint BezierPatchDistance::evaluate(const double u, const double v) const {
    const auto bernsteinU = bernstein(u);
    const auto bernsteinV = bernstein(v);

    MPoint point(0, 0, 0);
    for (int i = 0; i <= uDegree; ++i)
        for (int j = 0; j <= vDegree; ++j)
            point += patchControlPoints[i * (vDegree + 1) + j] * bernsteinU[i] * bernsteinV[j];

    return point;
}

void BezierPatchDistance::derivatives(const double u, const double v, MVector &partialU, MVector &partialV) const {
    const auto bernsteinU = bernstein(u);
    const auto bernsteinV = bernstein(v);
    const auto derivativeBernsteinU = bernsteinDerivative(u);
    const auto derivativeBernsteinV = bernsteinDerivative(v);

    partialU = MVector::zero;
    partialV = MVector::zero;

    for (int i = 0; i <= uDegree; ++i) {
        for (int j = 0; j <= vDegree; ++j) {
            const MVector cp(patchControlPoints[i * (vDegree + 1) + j]);
            partialU += cp * derivativeBernsteinU[i] * bernsteinV[j];
            partialV += cp * bernsteinU[i] * derivativeBernsteinV[j];
        }
    }
}

double BezierPatchDistance::operator()(const Eigen::VectorXd &uv, Eigen::VectorXd &gradient) {
    const double u = uv[0];
    const double v = uv[1];

    const MVector distance = evaluate(u, v) - targetPoint;

    MVector partialU, partialV;
    derivatives(u, v, partialU, partialV);

    gradient.resize(2);
    gradient[0] = 2.0 * (distance * partialU);
    gradient[1] = 2.0 * (distance * partialV);

    return distance * distance;
}
