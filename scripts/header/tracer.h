#pragma once

#include <color.h>
#include <math/degRad.h>

#include <tracerConfig.h>

namespace Tracer
{
    extern bool ready;
    extern unsigned int width;
    extern unsigned int height;
    extern color** pixelBuf;

    void init();
    void draw();
    void update();
    void drawProgress();
}