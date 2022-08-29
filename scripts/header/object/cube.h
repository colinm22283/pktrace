#pragma once

#include <material.h>
#include <texture.h>

#include <object/object.h>

class Cube : public Object
{
public:
    Cube();
    Cube(vector3 min, vector3 max);
    Cube(vector3 min, vector3 max, Material* mat, Texture* tex);

    vector3 min, max;

    Material* mat;
    Texture* tex;

    collisionResult checkCollision(ray r);
};