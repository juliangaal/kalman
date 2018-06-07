//
// Created by Julian on 12.03.18.
//

#include "SickRobotDayTest.hpp"

int main()
{
    SickRobotDayTest sick;
    sick.run();

    std::cout << "Results in: \n" << sick.getX() << std::endl;
    return 0;
}