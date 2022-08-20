#pragma once

#include <object/object.h>

#include <fcolor.h>

class Sphere : public Object
{
public:
    Sphere();
    Sphere(float radius, vector3 position, fcolor col, float reflectivity, float diffuse);

    float radius;
    vector3 position;

    fcolor col;
    float reflectivity;
    float diffuse;

    collisionResult checkCollision(ray r);
};