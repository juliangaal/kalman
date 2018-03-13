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

class Kalman
{
protected:
    xt::xarray<double> x;
    xt::xarray<double> P;
    xt::xarray<double> A;
    xt::xarray<double> Q;
    xt::xarray<double> H;
    xt::xarray<double> R;
    xt::xarray<double> I;

    xt::xarray<double> Z; // incoming measurments, set in child class

    xt::xarray<double> measurements;
    xt::xarray<double> mx;
    xt::xarray<double> my;

public:
    Kalman() = default;

    virtual ~Kalman() = default;

    virtual void generateData() = 0;

    virtual void init(const double& dt) = 0;

    virtual void run() noexcept;

    inline auto getX() const { return x; }
};

#endif //KALMAN_KALMAN_HPP
