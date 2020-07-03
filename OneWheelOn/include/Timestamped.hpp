#pragma once

template <typename T>
class Timestamped
{
public:
    float time;
    T value;
};