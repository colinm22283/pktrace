#pragma once

#include <object/object.h>

class Sphere : public Object
{
public:
    Sphere();
    Sphere(float radius, vector3 position);

    float radius;
    vector3 position;

    collisionResult checkCollision(ray r);
};