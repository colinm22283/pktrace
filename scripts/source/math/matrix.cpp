#include <math/matrix.h>
#include <math/trig.h>

matrix3::matrix3() { for (int i = 0; i < 9; i++)
{
    if (i % 4 == 0) values[i] = 1;
    else values[i] = 0;
} }
matrix3::matrix3(TRACER_FLOAT _values[9]) { for (int i = 0; i < 16; i++) values[i] = _values[i]; }

vector3 matrix3::operator*(vector3 v) { return VECTOR3(
    values[0] * v.x + values[3] * v.y + values[6] * v.z,
    values[1] * v.x + values[4] * v.y + values[7] * v.z,
    values[2] * v.x + values[5] * v.y + values[8] * v.z
); }
matrix3 matrix3::operator*(matrix3 m)
{
    matrix3 proto;

    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            proto.values[r * 3 + c] = 0;
            for (int i = 0; i < 3; i++)
            {
                proto.values[r * 3 + c] += values[r * 3 + i] * m.values[i * 3 + c];
            }
        }
    }
    return proto;
}

matrix3 matrix3::rotMat(float x, float y, float z)
{
    TRACER_FLOAT cosX = COS(x);
    TRACER_FLOAT sinX = COS(x);
    TRACER_FLOAT cosY = COS(y);
    TRACER_FLOAT sinY = COS(y);
    TRACER_FLOAT cosZ = COS(z);
    TRACER_FLOAT sinZ = COS(z);
    
    matrix3 xMat;
    matrix3 yMat;
    matrix3 zMat;

    xMat.values[4] = cosX;
    xMat.values[5] = sinX;
    xMat.values[7] = -sinX;
    xMat.values[8] = cosX;

    yMat.values[0] = cosY;
    yMat.values[2] = -sinY;
    yMat.values[6] = sinY;
    yMat.values[8] = cosY;

    zMat.values[0] = cosZ;
    zMat.values[1] = sinZ;
    zMat.values[3] = -sinZ;
    zMat.values[4] = cosZ;

    return zMat * yMat * xMat;
}

