//
// Created by Julian on 12.03.18.
//

#include "Kalman6d.hpp"

int main()
{
    Kalman6d k6d;
    k6d.run();

    std::cout << "Results in: \n" << k6d.getX() << std::endl;

    return 0;
}