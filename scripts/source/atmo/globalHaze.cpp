#include <world.h>

#include <math/random.h>

#include <atmo/globalHaze.h>

GlobalHaze::GlobalHaze() : GlobalHaze(FGS(50.0))
{ }

GlobalHaze::GlobalHaze(fcolor _col) : col(_col)
{ }

atmoResult GlobalHaze::checkPos(vector3 pos)
{
    TRACER_FLOAT lightIntensity = 0.0;
    for (unsigned int i = 0; i < World::lightCount; i++) lightIntensity += World::lights[i].intensityAt(pos);

    return {
        true,
        col * lightIntensity * randomRange()
    };
}