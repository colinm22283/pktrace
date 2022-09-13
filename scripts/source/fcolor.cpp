#include <fcolor.h>

#include <misc/clamp.h>

//#define FCOLOR_FUNCTION(x) CLAMP(x, 0.0f, 1.0f)
#define FCOLOR_FUNCTION(x) (x)

color fcolorToColor(fcolor fc)
{
    return RGBA(
        (uint8_t)CLAMP(fc.r * 255.0f, 0.0f, 255.0f),
        (uint8_t)CLAMP(fc.g * 255.0f, 0.0f, 255.0f),
        (uint8_t)CLAMP(fc.b * 255.0f, 0.0f, 255.0f),
        (uint8_t)CLAMP(fc.a * 255.0f, 0.0f, 255.0f)
    );
}
fcolor colorToFColor(color c)
{
    return FRGBA255(c.r, c.g, c.b, c.a);
}

fcolor fcolor::operator+(fcolor fc)
{
    return FRGBA(
        FCOLOR_FUNCTION(r + fc.r),
        FCOLOR_FUNCTION(g + fc.g),
        FCOLOR_FUNCTION(b + fc.b),
        FCOLOR_FUNCTION(a + fc.a)
    );
}
void fcolor::operator+=(fcolor fc)
{
    r = FCOLOR_FUNCTION(r + fc.r);
    g = FCOLOR_FUNCTION(g + fc.g);
    b = FCOLOR_FUNCTION(b + fc.b);
    a = FCOLOR_FUNCTION(a + fc.a);
}

fcolor fcolor::operator-(fcolor fc)
{
    return FRGBA(
        FCOLOR_FUNCTION(r - fc.r),
        FCOLOR_FUNCTION(g - fc.g),
        FCOLOR_FUNCTION(b - fc.b),
        FCOLOR_FUNCTION(a - fc.a)
    );
}

fcolor fcolor::operator*(TRACER_FLOAT x)
{
    return FRGBA(
        FCOLOR_FUNCTION(r * x),
        FCOLOR_FUNCTION(g * x),
        FCOLOR_FUNCTION(b * x),
        FCOLOR_FUNCTION(a * x)
    );
}
fcolor fcolor::operator*(fcolor fc)
{
    return FRGBA(
        FCOLOR_FUNCTION(r * fc.r),
        FCOLOR_FUNCTION(g * fc.g),
        FCOLOR_FUNCTION(b * fc.b),
        FCOLOR_FUNCTION(a * fc.a)
    );
}
void fcolor::operator*=(TRACER_FLOAT x)
{
    r *= x;
    g *= x;
    b *= x;
    a *= x;
}
void fcolor::operator*=(fcolor fc)
{
    r *= fc.r;
    g *= fc.g;
    b *= fc.b;
    a *= fc.a;
}

fcolor fcolor::operator/(TRACER_FLOAT x)
{
    return FRGBA(
        FCOLOR_FUNCTION(r / x),
        FCOLOR_FUNCTION(g / x),
        FCOLOR_FUNCTION(b / x),
        FCOLOR_FUNCTION(a / x)
    );
}
fcolor fcolor::operator/(fcolor fc)
{
    return FRGBA(
        FCOLOR_FUNCTION(r / fc.r),
        FCOLOR_FUNCTION(g / fc.g),
        FCOLOR_FUNCTION(b / fc.b),
        FCOLOR_FUNCTION(a / fc.a)
    );
}