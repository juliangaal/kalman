//
// Created by Julian on 13.03.18.
//

#ifndef KALMAN_HELPERS_HPP
#define KALMAN_HELPERS_HPP
#include <cmath>
namespace Helpers
{

constexpr double pow2(double val)
{
    return val * val;
}

constexpr double acc(double val)
{
    return 0.5 * pow2(val);
}

} // namespace Helpers

#endif //KALMAN_HELPERS_HPP
