//
// Created by Julian on 11.03.18.
//

#include "../include/Kalman.hpp"

void Kalman::run() noexcept
{
    for (int n = 0; n < 200; n++)
    {
        x = dot(A, x);

        P = dot(dot(A, P), xt::transpose(A)) + Q;
        auto S = dot(dot(H, P), xt::transpose(H)) + R;

        auto K = dot(dot(P, xt::transpose(H)), xt::linalg::pinv(S));

        xt::xarray<double> Z = {measurements(0, n),measurements(1, n)};
        Z.reshape({2, 1});

        x = x + dot(K, (Z - dot(H, x)));
        P = dot((I - dot(K, H)), P);

        std::cout << x << std::endl;
    }
}
