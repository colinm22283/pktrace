#pragma once

#include <tracerConfig.h>

struct Material
{
    Material();
    Material(TRACER_FLOAT reflectivity, TRACER_FLOAT diffuse, TRACER_FLOAT opacity);

    TRACER_FLOAT reflectivity;
    TRACER_FLOAT diffuse;
    TRACER_FLOAT opacity;
};