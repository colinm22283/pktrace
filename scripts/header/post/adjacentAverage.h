#pragma once

#include <post/postEffect.h>

class AdjacentAverage : public PostEffect
{
public:
    AdjacentAverage(int averageSize);

    int averageSize;

    void activate(fcolor **pixelBuf, int width, int height);
};