#pragma once

#include <render/color.h>
#include <math/degRad.h>

#include <tracerConfig.h>

namespace Tracer
{
    extern bool ready;
    extern bool indirectLighting;

    extern unsigned int width;
    extern unsigned int height;

    extern TRACER_FLOAT aspectRatio;
    extern TRACER_FLOAT exposure;
    extern TRACER_FLOAT dynamicRange;

    extern color** pixelBuf;

    void init();
    void draw();
    void update();
    void drawProgress();
}