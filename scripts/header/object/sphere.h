#pragma once

#include <object/object.h>

#include <fcolor.h>

class Sphere : public Object
{
public:
    Sphere();
    Sphere(TRACER_FLOAT radius, vector3 position, fcolor col, TRACER_FLOAT reflectivity, TRACER_FLOAT diffuse);

    TRACER_FLOAT radius;
    vector3 position;

    fcolor col;
    TRACER_FLOAT reflectivity;
    TRACER_FLOAT diffuse;

    collisionResult checkCollision(ray r);
};