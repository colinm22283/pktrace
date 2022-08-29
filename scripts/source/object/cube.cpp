#include <object/cube.h>

Cube::Cube() : min(VECTOR3(0.0, 0.0, 0.0)), max(VECTOR3(0.0, 0.0, 0.0))
{ }

Cube::Cube(vector3 _min, vector3 _max) : min(_min), max(_max)
{ }

collisionResult Cube::checkCollision(ray r)
{
    TRACER_FLOAT tMin = (min.x - r.origin.x) / r.direction.x;
    TRACER_FLOAT tMax = (max.x - r.origin.x) / r.direction.x;

    if (tMin > tMax)
    {
        TRACER_FLOAT temp = tMin;
        tMin = tMax;
        tMax = temp;
    }

    TRACER_FLOAT tyMin = (min.y - r.origin.y) / r.direction.y;
    TRACER_FLOAT tyMax = (max.y - r.origin.y) / r.direction.y;

    if (tyMin > tyMax)
    {
        TRACER_FLOAT temp = tyMin;
        tyMin = tMax;
        tyMax = temp;
    }

    if (tMin > tyMax || tyMin > tMax) return { false };

    if (tyMin > tMin) tMin = tyMin;
    if (tyMax < tMax) tMax = tyMax;

    TRACER_FLOAT tzMin = (min.z - r.origin.z) / r.direction.z;
    TRACER_FLOAT tzMax = (max.z - r.origin.z) / r.direction.z;

    if (tzMin > tzMax)
    {
        TRACER_FLOAT temp = tzMin;
        tzMin = tMax;
        tzMax = temp;
    }

    if (tMin > tzMax || tzMin > tMax) return { false };

    if (tzMin > tMin) tMin = tzMin;
    if (tzMax < tMax) tMax = tzMax;

    // TODO: finish this

    return (collisionResult){
        true,
        VECTOR3(0, 0, 0),
        0,
        VECTOR3(0, 0, 0),
        0.0,
        0.0,
        FGS(200)
    };
}