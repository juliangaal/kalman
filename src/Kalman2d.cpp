//
// Created by Julian on 11.03.18.
//

#include "../include/Kalman2d.hpp"

void Kalman2d::generateData() noexcept
{
    const int m = 200;
    const int vx = 20;
    const int vy = 10;

    mx = xt::random::randn<double>({m, }, vx);
    my = xt::random::randn<double>({m, }, vy);

    measurements = xt::stack(xt::xtuple(mx, my), 0);
}

Kalman2d::Kalman2d(double dt)
{
    this->init(dt);
    this->generateData();
}

void Kalman2d::init(const double& dt)
{
    x = {0, 0, 0, 0};
    x.reshape({4, 1});

    P = xt::diag(xt::xarray<double>({1000, 1000, 1000, 1000}));

    A = xt::diag(xt::xarray<double>({1, 1, 1, 1}));
    xt::view(A, 0, 2) = xt::view(A, 1, 3) = dt;

    const double sv = 8.8;
    xt::xarray<double> G = {0.5 * pow(dt, 2), 0.5 * pow(dt, 2), dt, dt};
    G.reshape({4, 1});
    Q = G * xt::transpose(G) * pow(sv, 2);

    H = {{0, 0, 1, 0},
         {0, 0, 0, 1}};

    double ra = pow(10.0, 2);
    R  = xt::diag(xt::xarray<double>({ra, ra}));

    I = xt::eye<double>(4);
}
