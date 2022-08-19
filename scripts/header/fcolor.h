#pragma once

#include <render/color.h>

#define FGS(gs) (fcolor){gs,gs,gs,1.0f}
#define FRGB(r,g,b) (fcolor){r,g,b,1.0f}
#define FRGBA(r,g,b,a) (fcolor){r,g,b,a}

#define FGS255(gs) (fcolor){gs/255.0f,gs/255.0f,gs/255.0f,1.0f}
#define FRGB255(r,g,b) (fcolor){r/255.0f,g/255.0f,b/255.0f,1.0f}
#define FRGBA255(r,g,b,a) (fcolor){r/255.0f,g/255.0f,b/255.0f,a/255.0f}

struct fcolor
{
    float r, g, b, a;

    fcolor operator+(fcolor fc);
    fcolor operator+=(fcolor fc);
    fcolor operator-(fcolor fc);
    fcolor operator*(float x);
    fcolor operator*(fcolor fc);
    fcolor operator/(float x);
    fcolor operator/(fcolor fc);
};

color fcolorToColor(fcolor fc);