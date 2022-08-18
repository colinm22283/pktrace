#pragma once

#include <math/vector.h>

class Light
{
public:
    Light();
    Light(float intensity, vector3 position);
    ~Light();

    float intensity;
    vector3 position;

    virtual float intensityAt(float distance);
    virtual float intensityAt(vector3 pos);
};