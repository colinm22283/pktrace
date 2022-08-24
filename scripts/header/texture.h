#pragma once

#include <img/img.h>

class Texture
{
public:
    Texture();
    Texture(const char* bmpPath);
    Texture(const char* bmpPath, double scale);

    double scale;

    color getPixel(int x, int y);
protected:
    img* tex;
};