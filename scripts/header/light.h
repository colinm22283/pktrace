#pragma once

#include <math/vector.h>

#include <render/color.h>

class Light
{
public:
    Light();
    Light(float intensity, vector3 position, color col);
    ~Light();

    float intensity;
    vector3 position;
    color col;

    virtual float intensityAt(float distance);
    virtual float intensityAt(vector3 pos);
};