#include <math/lerp.h>

TRACER_FLOAT lerp(TRACER_FLOAT low, TRACER_FLOAT high, TRACER_FLOAT t)
{
    return low * (1 - t) + high * t;
}

TRACER_FLOAT bilerp(TRACER_FLOAT x1, TRACER_FLOAT x2, TRACER_FLOAT y1, TRACER_FLOAT y2, TRACER_FLOAT x, TRACER_FLOAT y)
{
    return (
        (x1 * (1.0 - x)) +
        (x2 * x) +
        (y1 * (1.0 - y)) +
        (y2 * y)
    ) / (4);
}