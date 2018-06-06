//
// Created by Julian on 11.03.18.
//

#include "Kalman.hpp"

void Kalman::run() noexcept
{
    this->predict();
    this->update();
}

void Kalman::predict() noexcept 
{
    x = dot(A, x);
    predicted_state = x;
    
    P = dot(dot(A, P), xt::transpose(A)) + Q;
}

void Kalman::update() noexcept 
{
    auto S = dot(dot(H, P), xt::transpose(H)) + R;

    auto K = dot(dot(P, xt::transpose(H)), xt::linalg::pinv(S));

    x = x + dot(K, (Z - dot(H, x)));
    updated_state = x;

    P = dot((I - dot(K, H)), P);
}
