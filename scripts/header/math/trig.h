#pragma once

#include <cmath>
#include <tracerConfig.h>

#if TRACER_TRIG_FAST_MODE

    #define COS(x) fastCos(x)
    #define SIN(x) fastSin(x)
    #define TAN(x) fastTan(x)

    #define ACOS(x) fastACos(x)
    #define ASIN(x) fastASin(x)
    #define ATAN(x) fastATan(x)
    #define ATAN2(y, x) fastATan2(y, x)

TRACER_FLOAT fastCos(TRACER_FLOAT x);
TRACER_FLOAT fastSin(TRACER_FLOAT x);
TRACER_FLOAT fastTan(TRACER_FLOAT x);

TRACER_FLOAT fastACos(TRACER_FLOAT x);
TRACER_FLOAT fastASin(TRACER_FLOAT x);
TRACER_FLOAT fastATan(TRACER_FLOAT x);
TRACER_FLOAT fastATan2(TRACER_FLOAT y, TRACER_FLOAT x);

constexpr void trigInit();

#else

    #if TRACER_TRIG_DOUBLE_PRECISION
        #define COS(x) cosf64(x)
        #define SIN(x) sinf64(x)
        #define TAN(x) tanf64(x)
        #define ACOS(x) acosf64(x)
        #define ASIN(x) asinf64(x)
        #define ATAN(x) atanf64(x)
        #define ATAN2(y,x) atan2f64(y,x)

    #else
        #define COS(x) cosf(x)
        #define SIN(x) sinf32(x)
        #define TAN(x) tanf32(x)
        #define ACOS(x) acosf32(x)
        #define ASIN(x) asinf32(x)
        #define ATAN(x) atanf32(x)
        #define ATAN2(y,x) atan2f32(y, x);
    #endif

#endif