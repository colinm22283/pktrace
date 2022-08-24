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
Light::Light(TRACER_FLOAT _intensity, vector3 _position, fcolor _col) : intensity(_intensity), position(_position), col(_col)
{ }
Light::~Light()
{ }

TRACER_FLOAT Light::intensityAt(TRACER_FLOAT distance)
{
    return intensity / (4.0 * M_PIf64 * powf64(distance, 2.0));
}
TRACER_FLOAT Light::intensityAt(vector3 pos)
{
    return intensityAt(magnitude(pos - position));
}
