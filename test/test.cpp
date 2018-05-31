//
// Created by Julian on 13.03.18.
//

#include <iostream>
#include "Kalman.hpp"
#include "Kalman2d.hpp"
#include "Kalman6d.hpp"

using std::cout;
using std::endl;

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

    if (!result2dOk(x2d))
    {
        cout << "2d Kalman Filter error. Exiting" << endl;
        return EXIT_FAILURE;
    }
    
    Kalman6d k6d;
    k6d.run();
    auto x6d = k6d.getX();

    if (!result6dOk(x6d))
    {
        cout << "6d Kalman Filter error. Exiting" << endl;
        return EXIT_FAILURE;
    }
    

    cout << "Test successful" << endl;
    return EXIT_SUCCESS;
}
