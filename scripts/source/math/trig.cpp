#include <tracerConfig.h>

#if TRACER_TRIG_FAST_MODE

#include <math.h>

#include <math/trig.h>
#include <math/trigValues.h>

const TRACER_FLOAT cosValues[TRACER_TRIG_DIVISIONS] = COS_VALUES;
const TRACER_FLOAT sinValues[TRACER_TRIG_DIVISIONS] = SIN_VALUES;
const TRACER_FLOAT tanValues[TRACER_TRIG_DIVISIONS] = TAN_VALUES;

const TRACER_FLOAT acosValues[TRACER_TRIG_DIVISIONS] = ACOS_VALUES;
const TRACER_FLOAT asinValues[TRACER_TRIG_DIVISIONS] = ASIN_VALUES;
const TRACER_FLOAT atanValues[TRACER_TRIG_DIVISIONS] = ATAN_VALUES;

const double divisor = TRACER_TRIG_DIVISIONS / 2.0 / M_PIf64;

TRACER_FLOAT fastCos(TRACER_FLOAT x)
{
    if (isnan(x)) return 0.0;
    return cosValues[(int)(x * divisor)];
}
TRACER_FLOAT fastSin(TRACER_FLOAT x)
{
    if (isnan(x)) return 0.0;
    return sinValues[(int)(x * divisor)];
}
TRACER_FLOAT fastTan(TRACER_FLOAT x)
{
    if (isnan(x)) return 0.0;
    return tanValues[(int)(x * divisor)];
}

TRACER_FLOAT fastACos(TRACER_FLOAT x)
{
    return acosf64(x);
    if (isnan(x)) return 0.0;
    return acosValues[(int)(x * divisor)];
}
TRACER_FLOAT fastASin(TRACER_FLOAT x)
{
    return asinf64(x);
    if (isnan(x)) return 0.0;
    return asinValues[(int)(x * divisor)];
}
TRACER_FLOAT fastATan(TRACER_FLOAT x)
{
    return atanf64(x);
    if (isnan(x)) return 0.0;
    return atanValues[(int)(x * divisor)];
}
TRACER_FLOAT fastATan2(TRACER_FLOAT y, TRACER_FLOAT x)
{
    return atan2f64(y, x);
    if (isnan(x) || isnan(y)) return 0.0;
    if (x == 0)
    {
        return M_PIf64 / 2 * (y > 0 ? 1 : -1);
    }
    TRACER_FLOAT modVal = 2.0;
    return atanValues[(int)((modff64(y / x + 1.0, &modVal) - 1.0) * divisor)];
}

#endif