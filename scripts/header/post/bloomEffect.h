#pragma once

#include <post/postEffect.h>

class BloomEffect : public PostEffect
{
public:
    BloomEffect(TRACER_FLOAT radius);

    TRACER_FLOAT radius;

    void activate(fcolor** pixelBuf, int width, int height);
};