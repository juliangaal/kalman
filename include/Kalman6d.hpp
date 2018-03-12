//
// Created by Julian on 12.03.18.
//

#ifndef KALMAN_KALMAN6D_HPP
#define KALMAN_KALMAN6D_HPP

#include "Kalman.hpp"
#include <cmath>

class Kalman6d: public Kalman
{
public:
    Kalman6d(double dt = 0.01);

    ~Kalman6d() final = default;

    void run() noexcept final;

private:
    void generateData() final;

    void init(const double& dt) final;
};


#endif //KALMAN_KALMAN6D_HPP
