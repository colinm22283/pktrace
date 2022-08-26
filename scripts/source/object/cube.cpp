#include <object/cube.h>

Cube::Cube() : min(VECTOR3(0.0, 0.0, 0.0)), max(VECTOR3(0.0, 0.0, 0.0))
{ }

Cube::Cube(vector3 _min, vector3 _max) : min(_min), max(_max)
{ }

collisionResult Cube::checkCollision(ray r)
{
    TRACER_FLOAT tMin = (min.x - r.origin.x) / r.direction.x;
    TRACER_FLOAT tMax =(max.x - r.origin.x) / r.direction.x;

    if (tMin > tMax)
    {
        TRACER_FLOAT temp = tMin;
        tMin = tMax;
        tMax = temp;
    }

    // TODO: finish this
}