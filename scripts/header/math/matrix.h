#pragma once

#include <math/vector.h>

struct matrix3
{
    matrix3();
    matrix3(TRACER_FLOAT values[9]);

    TRACER_FLOAT values[9];

    vector3 operator*(vector3 v);
    matrix3 operator*(matrix3 m);

    static matrix3 rotMat(float x, float y, float z);
};