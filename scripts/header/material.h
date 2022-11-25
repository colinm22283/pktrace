#pragma once

#include <tracerConfig.h>
#include <fcolor.h>

struct Material
{
    Material();
    Material(TRACER_FLOAT reflectivity, TRACER_FLOAT refractionIndex, TRACER_FLOAT diffuse);
    Material(TRACER_FLOAT reflectivity, TRACER_FLOAT refractionIndex, TRACER_FLOAT diffuse, TRACER_FLOAT opacity);
    Material(TRACER_FLOAT reflectivity, TRACER_FLOAT refractionIndex, TRACER_FLOAT diffuse, TRACER_FLOAT opacity, fcolor col);

    TRACER_FLOAT reflectivity;
    TRACER_FLOAT refractionIndex;
    TRACER_FLOAT diffuse;
    TRACER_FLOAT opacity;

    fcolor col;
};