#pragma once

#include <atmo/atmo.h>

class SphereHaze : public Atmo
{
public:
    SphereHaze();
    SphereHaze(fcolor col, vector3 position, TRACER_FLOAT radius);

    fcolor col;
    vector3 position;
    TRACER_FLOAT radius;

    atmoResult checkPos(vector3 pos);
};