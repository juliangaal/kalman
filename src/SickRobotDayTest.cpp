//
// Created by Julian on 11.03.18.
//

#include <random>
#include <iostream>
#include "SickRobotDayTest.hpp"

void SickRobotDayTest::generateData() noexcept
{
    std::random_device rseed;
    std::mt19937 rng(rseed());
    std::uniform_int_distribution<int> dist(-1,1);

    auto toRadian = [](int& deg) { return (deg * M_PI) / 180; };
    auto randVal = [](std::mt19937& rng, std::uniform_int_distribution<int>& dist) { return dist(rng); };

    constexpr double radius = 10.0;

    for (int degree = 0; degree < 360; degree++)
    {
        mx[degree] = 0.0 + radius * std::cos(toRadian(degree)) + randVal(rng, dist);
        my[degree] = 0.0 + radius * std::sin(toRadian(degree)) + randVal(rng, dist);
    }
    measurements = xt::stack(xt::xtuple(mx, my), 0);
}

SickRobotDayTest::SickRobotDayTest(double dt)
{
    mx = xt::zeros<double>({360});
    my = xt::zeros<double>({360});
    this->init(dt);
    this->generateData();
}

void SickRobotDayTest::init(const double& dt)
{
    x = {0, 0, 0, 0};
    x.reshape({4, 1});

    P = xt::diag(xt::xarray<double>({1000, 1000, 1000, 1000}));

    A = xt::diag(xt::xarray<double>({1, 1, 1, 1}));
    A(0, 2) = dt;
    A(1, 3) = dt;

    const double sv = 8.8;
    xt::xarray<double> G = {0.5 * pow(dt, 2), 0.5 * pow(dt, 2), dt, dt};
    G.reshape({4, 1});
    Q = G * xt::transpose(G) * pow(sv, 2);

    H = {{1.0, 0.0, 0.0, 0.0},
         {0.0, 1.0, 0.0, 0.0}};

    double ra = pow(100.0, 2);
    R  = xt::diag(xt::xarray<double>({ra, ra}));

    I = xt::eye<double>(4);
}

void SickRobotDayTest::prepNextMeasurement(int data_index) noexcept
{
    Z = { measurements(0, data_index), measurements(1, data_index)};
    Z.reshape({2, 1});
}

void SickRobotDayTest::run() noexcept
{
    for (int data_index = 0; data_index < 200; data_index++)
    {
        this->prepNextMeasurement(data_index);
        Kalman::run();
    }
}
