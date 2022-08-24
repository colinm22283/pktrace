#pragma once

#include <object/object.h>

class Triangle : public Object
{
public:
    Triangle();
    Triangle(vector3 p1, vector3 p2, vector3 p3);

    vector3 p1, p2, p3;

    collisionResult checkCollision(ray r);
};