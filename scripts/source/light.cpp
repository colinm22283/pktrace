#include <cmath>

#include <light.h>

#include <misc/minMax.h>

#include <tracerConfig.h>

Light::Light()
{
    intensity = 0;
    position = { 0, 0, 0 };
    col = FGS(255);
}
Light::Light(float _intensity, vector3 _position, fcolor _col) : intensity(_intensity), position(_position), col(_col)
{ }
Light::~Light()
{ }

float Light::intensityAt(float distance)
{
    return intensity / LIGHT_DIV(distance);
}
float Light::intensityAt(vector3 pos)
{
    return intensityAt(magnitude(pos - position));
}
