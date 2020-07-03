#pragma once

template <typename T>
class PIDController
{
public:
    T kp, ki, kd;
    T p, i, d;

    T update(float dt, T input, T goal)
    {
        auto error = goal - input;
        i = i + (ki * p * dt);
        d = (error - p) / dt;
        p = error;

        return p * kp + i + d * kd;
    }

    PIDController(){};
    PIDController(T kpN, T kiN, T kdN) : kp(kpN), ki(kiN), kd(kdN)
    {
    }
};
