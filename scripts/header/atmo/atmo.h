#pragma once

#include <math/ray.h>
#include <math/atmoResult.h>

class Atmo
{
public:
    virtual atmoResult checkPos(vector3 pos);
};