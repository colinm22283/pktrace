#include <post/pixelLerp.h>

#include <math/lerp.h>

PixelLerp::PixelLerp(int _sampleDistance) : sampleDistance(_sampleDistance)
{ }

void PixelLerp::activate(fcolor **pixelBuf, int width, int height)
{
    fcolor** newBuffer = new fcolor*[width];
    for (int x = 0; x < width; x++)
    {
        newBuffer[x] = new fcolor[height];
        for (int y = 0; y < height; y++) newBuffer[x][y] = pixelBuf[x][y];
    }

    for (int x = 0; x < width - sampleDistance; x += sampleDistance)
    {
        for (int y = 0; y < height - sampleDistance; y += sampleDistance)
        {
            fcolor px1 = newBuffer[x][y];
            fcolor px2 = newBuffer[x + sampleDistance][y];
            fcolor py1 = newBuffer[x][y];
            fcolor py2 = newBuffer[x][y + sampleDistance];

            for (int x2 = 0; x2 < sampleDistance; x2++)
            {
                for (int y2 = 0; y2 < sampleDistance; y2++)
                {
                    pixelBuf[x + x2][y + y2] = FRGB(
                        bilerp(px1.r, px2.r, py1.r, py2.r, (TRACER_FLOAT)x2 / sampleDistance, (TRACER_FLOAT)y2 / sampleDistance),
                        bilerp(px1.g, px2.g, py1.g, py2.g, (TRACER_FLOAT)x2 / sampleDistance, (TRACER_FLOAT)y2 / sampleDistance),
                        bilerp(px1.b, px2.b, py1.b, py2.b, (TRACER_FLOAT)x2 / sampleDistance, (TRACER_FLOAT)y2 / sampleDistance)
                    );
                }
            }
        }
    }
    for (int x = 0; x < width; x++) delete[] newBuffer[x];
    delete[] newBuffer;
}