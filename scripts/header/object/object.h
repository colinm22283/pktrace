#pragma once

#include <math/ray.h>
#include <math/collisionResult.h>

class Object
{
public:
    virtual collisionResult checkCollision(ray r);
};