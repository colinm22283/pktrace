#pragma once

#include <fcolor.h>

class PostEffect
{
public:
    PostEffect();

    virtual void activate(fcolor** pixelBuf, int width, int height);
};