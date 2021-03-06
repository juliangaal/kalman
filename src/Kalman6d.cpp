//
// Created by Julian on 12.03.18.
//

#include "Kalman6d.hpp"
#include "Helpers.hpp"

Kalman6d::Kalman6d(double dt)
{
    this->init(dt);
    this->generateData();
}

void Kalman6d::init(const double& dt)
{
    x = {0.0, 0.0, 1.0, 10.0, 0.0, 0.0, 0.0, 0.0, -9.81};
    x.reshape({9, 1});
    

    constexpr double sigma = 100.0;
    P = xt::diag(xt::ones<double>({9, 1}));
    P *= sigma;

    const double dtt = 0.5 * Helpers::pow2(dt);
    A = {{1.0, 0.0, 0.0,  dt, 0.0, 0.0, dtt, 0.0, 0.0},
         {0.0, 1.0, 0.0, 0.0,  dt, 0.0, 0.0, dtt, 0.0},
         {0.0, 0.0, 1.0, 0.0, 0.0,  dt, 0.0, 0.0, dtt},
         {0.0, 0.0, 0.0, 1.0, 0.0, 0.0,  dt, 0.0, 0.0},
         {0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,  dt, 0.0},
         {0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,  dt},
         {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0},
         {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0},
         {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0}};

    const double acc = Helpers::acc(dt);
    xt::xarray<double> G = {acc, acc, acc, dt, dt, dt, 1.0, 1.0, 1.0};
    G.reshape({9, 1});

    constexpr double sv = Helpers::pow2(1.0);
    Q = G * xt::transpose(G) * sv;

    H = {{1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
         {0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
         {0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,}};

    // constexpr version
    constexpr double ra = Helpers::pow2(1.0);

    R = xt::diag(xt::ones<double>({3, 1}) * ra);

    I = xt::eye<double>(9);
}

void Kalman6d::generateData()
{
    constexpr double Hz = 100.0; // Frequency of Vision System
    const double dt = 1.0/Hz;
    constexpr double T = 1.0; // s measuremnt time
    const int m = static_cast<int>(T/dt); // number of measurements

    double px = 0.0; // x Position Start
    double py = 0.0;
    double pz= 1.0; // z Position Start

    double vx = 10.0; // m/s Velocity at the beginning
    double vz = 0.0; // m/s Velocity

    constexpr double c = 0.1; // Drag Resistance Coefficient
    constexpr double d = 0.9; // Damping

//    std::vector<double> Xr, Yr, Zr;
    xt::xarray<double> Xr = xt::zeros<double>({m});
    xt::xarray<double> Yr = xt::zeros<double>({m});
    xt::xarray<double> Zr = xt::zeros<double>({m});

    constexpr float sp = 0.1; // Sigma for position noise

    for (int i = 0; i < m; i++)
    {
        double accx = -c * std::pow(vx, 2); // Drag Resistance

        vx += accx * dt;
        px += vx * dt;

        double accz = -9.806 + c * pow(vz,2);// Gravitation + Drag
        vz += accz * dt;
        pz += vz * dt;

        if (pz < 0.01)
        {
            vz = -vz * d;
            pz += 0.02;
        }

        if (vx < 0.1)
        {
            accx = 0.0;
            accz = 0.0;
        }

        Xr(i) = px;
        Yr(i) = py;
        Zr(i) = pz;
    }

    xt::xarray<double> Xm = Xr + sp * (xt::random::randn<double>({m, }, -10, 10));
    xt::xarray<double> Ym = Yr + sp * (xt::random::randn<double>({m, }, -10, 10));
    xt::xarray<double> Zm = Zr + sp * (xt::random::randn<double>({m, }, -10, 10));
    measurements = xt::stack(xt::xtuple(Xr, Yr, Zr), 0);
}

void Kalman6d::prepNextMeasurement(int data_index) noexcept
{
    Z = { measurements(0, data_index), measurements(1, data_index), measurements(2, data_index) };
    Z.reshape({3, 1});
}

void Kalman6d::run() noexcept
{
    bool hitGround = false;

    for (int data_index = 0; data_index < 100; data_index++)
    {
        if (x(2) < 0.01 && !hitGround)
        {
            x(5) *= -1.0;
            hitGround = true;
        }
        else
        {
            hitGround = false;
        }

        this->prepNextMeasurement(data_index);

        Kalman::run();
    }
}