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
    const auto Bu = bernstein(u);
    const auto Bv = bernstein(v);

    MPoint point(0, 0, 0);
    for (int i = 0; i <= uDegree; ++i)
        for (int j = 0; j <= vDegree; ++j)
            point += patchControlPoints[i * (vDegree + 1) + j] * Bu[i] * Bv[j];

    return point;
}

void BezierPatchDistance::derivatives(const double u, const double v, MVector &dPdu, MVector &dPdv) const {
    const auto Bu = bernstein(u);
    const auto Bv = bernstein(v);
    const auto dBu = bernsteinDerivative(u);
    const auto dBv = bernsteinDerivative(v);

    dPdu = MVector::zero;
    dPdv = MVector::zero;

    for (int i = 0; i <= uDegree; ++i) {
        for (int j = 0; j <= vDegree; ++j) {
            const MVector cp(patchControlPoints[i * (vDegree + 1) + j]);
            dPdu += cp * dBu[i] * Bv[j];
            dPdv += cp * Bu[i] * dBv[j];
        }
    }
}

double BezierPatchDistance::operator()(const Eigen::VectorXd &uv, Eigen::VectorXd &gradient) {
    const double u = uv[0];
    const double v = uv[1];

    const MVector diff = evaluate(u, v) - targetPoint;

    MVector dPdu, dPdv;
    derivatives(u, v, dPdu, dPdv);

    gradient.resize(2);
    gradient[0] = 2.0 * (diff * dPdu);
    gradient[1] = 2.0 * (diff * dPdv);

    return diff * diff; // squared distance
}
