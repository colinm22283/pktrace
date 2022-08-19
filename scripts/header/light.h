#pragma once

#include <math/vector.h>

#include <fcolor.h>

class Light
{
public:
    Light();
    Light(float intensity, vector3 position, fcolor col);
    ~Light();

    float intensity;
    vector3 position;
    fcolor col;

    virtual float intensityAt(float distance);
    virtual float intensityAt(vector3 pos);
};