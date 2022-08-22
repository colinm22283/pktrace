#pragma once

#include <tracerConfig.h>

#define VECTOR2(x, y) (vector2){x,y}
#define VECTOR3(x, y, z) (vector3){x,y,z}

#define VECTOR_PRINT(v) "("<<v.x<<", "<<v.y<<", "<<v.z<<")"

struct vector2
{
    TRACER_FLOAT x;
    TRACER_FLOAT y;
};
struct vector3
{
    TRACER_FLOAT x;
    TRACER_FLOAT y;
    TRACER_FLOAT z;

    vector3 operator+(vector3 v);
    vector3 operator-(vector3 v);
    vector3 operator*(TRACER_FLOAT x);
    vector3 operator/(TRACER_FLOAT x);
};

TRACER_FLOAT transformedDotProd(vector3 a, vector3 b);
TRACER_FLOAT dotProd(vector3 a, vector3 b);
TRACER_FLOAT magnitude(vector3 v);
vector3 normalize(vector3 v);
vector3 vecMultiply(vector3 a, vector3 b);