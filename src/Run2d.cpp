//
// Created by Julian on 12.03.18.
//

#include "Kalman2d.hpp"
#include "Kalman6d.hpp"

int main()
{
    Kalman2d k2d;
    k2d.run();

    std::cout << "Results in: \n" << k2d.getX() << std::endl;

    return 0;
}
