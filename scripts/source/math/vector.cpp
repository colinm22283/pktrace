#include <cmath>

#include <math/vector.h>
#include <math/trig.h>

vector3 vector3::operator+(vector3 v)
{
    return VECTOR3(x + v.x, y + v.y, z + v.z);
}
vector3 vector3::operator-(vector3 v)
{
    return VECTOR3(x - v.x, y - v.y, z - v.z);
}
vector3 vector3::operator*(float _)
{
    return VECTOR3(x * _, y * _, z * _);
}
vector3 vector3::operator/(float _)
{
    return VECTOR3(x / _, y / _, z / _);
}

float transformedDotProd(vector3 a, vector3 b)
{
    return ACOS(dotProd(a, b) / (magnitude(a) * magnitude(b)));
}

float dotProd(vector3 a, vector3 b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

float magnitude(vector3 v)
{
    return sqrtf32(
        powf32(v.x, 2) +
        powf32(v.y, 2) +
        powf32(v.z, 2)
    );
}

vector3 normalize(vector3 v)
{
    return v / magnitude(v);
}

vector3 vecMultiply(vector3 a, vector3 b)
{
    return VECTOR3(a.x * b.x, a.y * b.y, a.z * b.z);
}