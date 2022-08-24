#pragma once

#include <render/color.h>
#include <tracerConfig.h>

#define FGS(gs) (fcolor){gs,gs,gs,1.0}
#define FRGB(r,g,b) (fcolor){r,g,b,1.0}
#define FRGBA(r,g,b,a) (fcolor){r,g,b,a}

#define FGS255(gs) (fcolor){gs/255.0,gs/255.0,gs/255.0,1.0}
#define FRGB255(r,g,b) (fcolor){r/255.0,g/255.0,b/255.0,1.0}
#define FRGBA255(r,g,b,a) (fcolor){r/255.0,g/255.0,b/255.0,a/255.0}

struct fcolor
{
    TRACER_FLOAT r, g, b, a;

    fcolor operator+(fcolor fc);
    fcolor operator+=(fcolor fc);
    fcolor operator-(fcolor fc);
    fcolor operator*(TRACER_FLOAT x);
    fcolor operator*(fcolor fc);
    fcolor operator/(TRACER_FLOAT x);
    fcolor operator/(fcolor fc);
};

color fcolorToColor(fcolor fc);
fcolor colorToFColor(color c);