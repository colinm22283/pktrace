#pragma once

#include <atmo/atmo.h>

#include <math/atmoResult.h>

class GlobalHaze : public Atmo
{
public:
    GlobalHaze();
    GlobalHaze(fcolor col);

    fcolor col;
    
    atmoResult checkPos(vector3 pos);
};