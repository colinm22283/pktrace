#pragma once

#include <math/vector.h>

#include <fcolor.h>

class Light
{
public:
    Light();
    Light(TRACER_FLOAT intensity, vector3 position, fcolor col);
    ~Light();

    TRACER_FLOAT intensity;
    vector3 position;
    fcolor col;

    virtual TRACER_FLOAT intensityAt(TRACER_FLOAT distance);
    virtual TRACER_FLOAT intensityAt(vector3 pos);
};