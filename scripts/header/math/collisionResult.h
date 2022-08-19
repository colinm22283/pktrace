#pragma once

#include <math/vector.h>
#include <object/object.h>

struct collisionResult
{
    bool hit;
    vector3 position;
    float distance;
    vector3 result;
    float reflectivity;
};