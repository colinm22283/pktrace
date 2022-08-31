#include <math/lerp.h>

TRACER_FLOAT lerp(TRACER_FLOAT low, TRACER_FLOAT high, TRACER_FLOAT t)
{
    return low * (1 - t) + high * t;
}