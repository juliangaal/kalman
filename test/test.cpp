//
// Created by Julian on 13.03.18.
//

#include "Kalman.hpp"
#include "Kalman2d.hpp"
#include "Kalman6d.hpp"

bool result6dOk(xt::xarray<double>& x)
{
    return std::abs(x(0, 0) - 6.876175) <= 1.0 &&
           std::abs(x(1, 0) - 0.005916) <= 1.0 &&
           std::abs(x(2, 0) - 0.930954) <= 1.0;
}

bool result2dOk(xt::xarray<double>& x)
{
    return std::abs(x(0, 0) - 398.727037) <= 1.0 &&
           std::abs(x(1, 0) - 199.245777) <= 1.0 ;
}

int main()
{
    Kalman2d k2d;
    k2d.run();
    auto x2d = k2d.getX();

    Kalman6d k6d;
    k6d.run();
    auto x6d = k6d.getX();

    bool success = result6dOk(x6d) && result2dOk(x2d);

    if (!success)
        return EXIT_FAILURE;

    std::cout << "Test successful" << std::endl;
    return EXIT_SUCCESS;
}