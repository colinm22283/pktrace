#pragma once

#include <fcolor.h>
#include <texture.h>
#include <material.h>

#include <object/object.h>

class Sphere : public Object
{
public:
    Sphere();
    Sphere(TRACER_FLOAT radius, vector3 position, Texture* tex, Material* mat);

    TRACER_FLOAT radius;
    vector3 position;

    Texture* tex;
    Material* material;

    collisionResult checkCollision(ray r);
};