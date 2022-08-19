#include <misc/clamp.h>

#include <render/color.h>

color color::operator+(color c)
{
    return RGBA(
        (uint8_t)CLAMP(r + c.r, 0, 255),
        (uint8_t)CLAMP(g + c.g, 0, 255),
        (uint8_t)CLAMP(b + c.b, 0, 255),
        (uint8_t)CLAMP(a + c.a, 0, 255)
    );
}

color color::operator-(color c)
{
    return RGBA(
            (uint8_t)CLAMP(r - c.r, 0, 255),
            (uint8_t)CLAMP(g - c.g, 0, 255),
            (uint8_t)CLAMP(b - c.b, 0, 255),
            (uint8_t)CLAMP(a - c.a, 0, 255)
    );
}