#pragma once

#include <object/object.h>

class Cube : public Object
{
public:
    Cube();
    Cube(vector3 min, vector3 max);

    vector3 min, max;

    collisionResult checkCollision(ray r);
};