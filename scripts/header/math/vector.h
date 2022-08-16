#pragma once

#define VECTOR2(x, y) (vector2){x,y}
#define VECTOR3(x, y, z) (vector3){x,y,z}

#define VECTOR_PRINT(v) "("<<v.x<<", "<<v.y<<", "<<v.z<<")"

struct vector2
{
    float x;
    float y;
};
struct vector3
{
    float x;
    float y;
    float z;

    vector3 operator+(vector3 v);
    vector3 operator-(vector3 v);
    vector3 operator*(float x);
};

float transformedDotProd(vector3 a, vector3 b);
float dotProd(vector3 a, vector3 b);
float magnitude(vector3 v);
vector3 vecMultiply(vector3 a, vector3 b);