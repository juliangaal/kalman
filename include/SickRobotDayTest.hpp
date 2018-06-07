//
// Created by Julian on 11.03.18.
//

#ifndef SICK_ROBOT_DAY_TEST_HPP
#define SICK_ROBOT_DAY_TEST_HPP

#include "Kalman.hpp"

class SickRobotDayTest : public Kalman
{
public:
    SickRobotDayTest(double dt = 0.1);

    ~SickRobotDayTest() final = default;

    void init(const double& dt) final;

    void run() noexcept final;

    void prepNextMeasurement(int data_index) noexcept final;

private:
    void generateData() noexcept final;
};


#endif //SICK_ROBOT_DAY_TEST_HPP
