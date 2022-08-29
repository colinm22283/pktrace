#pragma once

#include <light.h>
#include <object/object.h>
#include <atmo/atmo.h>

namespace World
{
    extern unsigned int objectCount;
    extern Object** objects;
    extern unsigned int lightCount;
    extern Light* lights;
    extern unsigned int atmoCount;
    extern Atmo** atmos;

    void cleanup();

    collisionResult raycast(ray r);
}