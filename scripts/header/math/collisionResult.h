#pragma once

#include <fcolor.h>

#include <math/vector.h>

#include <object/object.h>

struct collisionResult
{
    bool hit;
    vector3 position;
    TRACER_FLOAT distance;
    vector3 result;
    TRACER_FLOAT reflectivity;
    TRACER_FLOAT diffuse;
    fcolor col;
    TRACER_FLOAT transparency;
    vector3 transparencyResult;
};