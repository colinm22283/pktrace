#pragma once

#include <material.h>

#include <object/object.h>

class Plane : public Object
{
public:
    Plane();
    Plane(vector3 position, vector3 normal, Material* mat);

    vector3 position, normal;

    Material* mat;

    collisionResult checkCollision(ray r);
};