#pragma once

#include <post/postEffect.h>

class PixelLerp : public PostEffect
{
public:
    PixelLerp(int sampleDistance);

    int sampleDistance;

    void activate(fcolor** pixelBuf, int width, int height);
};