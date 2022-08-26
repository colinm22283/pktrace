#pragma once

#include <material.h>
#include <texture.h>

#include <object/object.h>

class Plane : public Object
{
public:
    Plane();
    Plane(vector3 position, vector3 normal, Texture* tex, Material* mat);

    vector3 position, normal;

    Texture* tex;
    Material* mat;

    collisionResult checkCollision(ray r);
};