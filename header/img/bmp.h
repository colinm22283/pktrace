#pragma once

#include <string>

#include "render/color.h"

#include <img/img.h>

class bmp: public img
{
public:
    bmp();
    bmp(const char* path);

    void load(const char* path);
};