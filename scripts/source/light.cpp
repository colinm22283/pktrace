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

float Light::intensityAt(vector3 pos)
{
    return intensity / (4 * M_1_PIf * (
        powf32(pos.x - position.x, 2) +
        powf32(pos.y - position.y, 2) +
        powf32(pos.z - position.z, 2)
   ));
}