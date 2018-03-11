//
// Created by Julian on 11.03.18.
//

#ifndef KALMAN_KALMAN2D_HPP
#define KALMAN_KALMAN2D_HPP

#include "Kalman.hpp"

class Kalman2d: public Kalman
{
public:
    Kalman2d(double dt = 0.1);

    ~Kalman2d() final = default;

    void init(const double& dt) final;

private:
    void generateData() noexcept final;
};


#endif //KALMAN_KALMAN2D_HPP