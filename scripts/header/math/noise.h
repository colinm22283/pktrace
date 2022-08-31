#pragma once

#include <tracerConfig.h>

class Noise1D
{
public:
    Noise1D();
    Noise1D(int loopLength);

    TRACER_FLOAT getValue(TRACER_FLOAT i);

protected:
    TRACER_FLOAT* randoms;
    int loopLength
};