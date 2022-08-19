#pragma once

#include <object/object.h>

class Sphere : public Object
{
public:
    Sphere();
    Sphere(float radius, vector3 position, float reflectivity);

    float radius;
    vector3 position;

    float reflectivity;

    collisionResult checkCollision(ray r);
};