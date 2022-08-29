#include <valarray>

#include <world.h>

#include <math/random.h>

#include <atmo/sphereHaze.h>

SphereHaze::SphereHaze() : SphereHaze(FGS(0), VECTOR3(0.0, 0.0, 0.0), 0.0)
{ }

SphereHaze::SphereHaze(fcolor _col, vector3 _position, double _radius) : col(_col), position(_position), radius(_radius)
{ }

atmoResult SphereHaze::checkPos(vector3 pos)
{
    TRACER_FLOAT lightIntensity = 0.0;
    for (unsigned int i = 0; i < World::lightCount; i++) lightIntensity += World::lights[i].intensityAt(pos);

    if (abs(magnitude(pos - position)) < radius) return {
        true,
        col * lightIntensity * randomRange()
    };
    else return { false };

}