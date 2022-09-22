#pragma once

#include <light.h>
#include <object/object.h>

namespace World
{
    extern unsigned int objectCount;
    extern Object** objects;
    extern unsigned int lightCount;
    extern Light* lights;
    extern unsigned int atmoCount;

    void cleanup();

    collisionResult raycast(ray r);
    collisionResult raycast(ray r, Object* maskObject);
    collisionResult raycast(ray r, Object** maskObjects, int maskCount);
}