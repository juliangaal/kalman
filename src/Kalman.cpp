//
// Created by Julian on 11.03.18.
//

#include "Kalman.hpp"

constexpr double Kalman::pow2(double val) const
{
    return val * val;
}

void Kalman::run() noexcept
{
    x = dot(A, x);

    P = dot(dot(A, P), xt::transpose(A)) + Q;

    auto S = dot(dot(H, P), xt::transpose(H)) + R;

    auto K = dot(dot(P, xt::transpose(H)), xt::linalg::pinv(S));

    x = x + dot(K, (Z - dot(H, x)));

    P = dot((I - dot(K, H)), P);
}
