//
// Created by Julian on 11.03.18.
//

#include "Kalman.hpp"

xarray<double> Kalman::operator*(xarray<double>& a, xarray<double>& b)
{
    return dot(a, b);
}

void Kalman::run() noexcept
{
    this->predict();
    this->update();
}

void Kalman::predict() noexcept 
{
    x = A * x;
    predicted_state = x;
    
    P = dot((A * P), transpose(A)) + Q;
}

void Kalman::update() noexcept 
{
    auto S = dot((H * P), transpose(H)) + R;

    xarray<double> temps = P * transpose(H);
    xarray<double> K = dot(temps, pinv(S));

    xarray<double> temp = Z - (H * x);
    x = x + (K * temp);
    updated_state = x;

    P = (I - (K * H)) * P;
}
