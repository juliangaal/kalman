//
// Created by Julian on 11.03.18.
//
#ifndef KALMAN_KALMAN_HPP
#define KALMAN_KALMAN_HPP

#include <iostream>
#include "xtensor/xarray.hpp"
#include "xtensor/xstrided_view.hpp"
#include "xtensor/xbuilder.hpp"
#include "xtensor/xio.hpp"
#include "xtensor/xrandom.hpp"
#include "xtensor-blas/xlinalg.hpp"

using std::cout;
using std::endl;
using xt::linalg::dot;
using xt::xarray;
using xt::zeros;
using xt::transpose;
using xt::linalg::pinv;

class Kalman
{
protected:
    xarray<double> x;
    xarray<double> P;
    xarray<double> A;
    xarray<double> Q;
    xarray<double> H;
    xarray<double> R;
    xarray<double> I;

    xarray<double> Z; // incoming measurments, set in child class

    xarray<double> measurements;
    xarray<double> mx;
    xarray<double> my;

public:
    Kalman() = default;

    virtual ~Kalman() = default;

    virtual void generateData() = 0;

    virtual void init(const double& dt) = 0;

    virtual void run() noexcept;

    virtual void prepNextMeasurement(int data_index) noexcept = 0;

    inline auto getX() const { return x; }

protected:
    xarray<double> predicted_state;

    xarray<double> updated_state;

private:
    void predict() noexcept;

    void update() noexcept;

};

#endif //KALMAN_KALMAN_HPP
