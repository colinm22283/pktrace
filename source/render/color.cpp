#include <misc/clamp.h>

#include <render/color.h>

#define COLOR_COLOR_CLAMP 1

#if COLOR_COLOR_CLAMP
    #define COLOR_VALUE_MOD(x) CLAMP(x, 0, 255)
#else
    #define COLOR_VALUE_MOD(x) x
#endif

color color::operator+(color c)
{
    return RGBA(
        (uint8_t)COLOR_VALUE_MOD(r + c.r),
        (uint8_t)COLOR_VALUE_MOD(g + c.g),
        (uint8_t)COLOR_VALUE_MOD(b + c.b),
        (uint8_t)COLOR_VALUE_MOD(a + c.a)
    );
}


color color::operator-(color c)
{
    return RGBA(
        (uint8_t)COLOR_VALUE_MOD(r - c.r),
        (uint8_t)COLOR_VALUE_MOD(g - c.g),
        (uint8_t)COLOR_VALUE_MOD(b - c.b),
        (uint8_t)COLOR_VALUE_MOD(a - c.a)
    );
}

color color::operator*(color c)
{
    return RGBA(
        (uint8_t)COLOR_VALUE_MOD(r * c.r),
        (uint8_t)COLOR_VALUE_MOD(g * c.g),
        (uint8_t)COLOR_VALUE_MOD(b * c.b),
        (uint8_t)COLOR_VALUE_MOD(a * c.a)
    );
}
color color::operator*(float x)
{
    return RGBA(
        (uint8_t)COLOR_VALUE_MOD(r * x),
        (uint8_t)COLOR_VALUE_MOD(g * x),
        (uint8_t)COLOR_VALUE_MOD(b * x),
        (uint8_t)COLOR_VALUE_MOD(a * x)
    );
}

color color::operator/(float x)
{
    return RGBA(
            (uint8_t)COLOR_VALUE_MOD(r / x),
            (uint8_t)COLOR_VALUE_MOD(g / x),
            (uint8_t)COLOR_VALUE_MOD(b / x),
            (uint8_t)COLOR_VALUE_MOD(a / x)
    );
}

color color::operator+=(color c)
{
    r = COLOR_VALUE_MOD(r + c.r);
    g = COLOR_VALUE_MOD(g + c.g);
    b = COLOR_VALUE_MOD(b + c.b);
    a = COLOR_VALUE_MOD(a + c.a);

    return *this;
}

color color::operator-=(color c)
{
    r = COLOR_VALUE_MOD(r - c.r);
    g = COLOR_VALUE_MOD(g - c.g);
    b = COLOR_VALUE_MOD(b - c.b);
    a = COLOR_VALUE_MOD(a - c.a);
    return *this;
}