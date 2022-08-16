#pragma once

#include <light.h>
#include <object/object.h>

namespace World
{
    extern unsigned int objectCount;
    extern Object** objects;
    extern unsigned int lightCount;
    extern Light* lights;

    void cleanup();

    collisionResult raycast(ray r);
}