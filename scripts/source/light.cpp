#include <cmath>

#include <light.h>

Light::Light()
{
    intensity = 0;
    position = { 0, 0, 0 };
}
Light::Light(float _intensity, vector3 _position) : intensity(_intensity), position(_position)
{ }
Light::~Light()
{ }

float Light::intensityAt(float distance)
{
    return intensity / (4 * M_1_PIf * distance);
}
float Light::intensityAt(vector3 pos)
{
    return intensityAt(magnitude(pos - position));
}
