#include <cmath>
#include <iostream>

#include <post/bloomEffect.h>

BloomEffect::BloomEffect(TRACER_FLOAT _radius) : radius(_radius)
{ }

void BloomEffect::activate(fcolor** pixelBuf, int width, int height)
{
    fcolor** newBuffer = new fcolor*[width];
    for (int x = 0; x < width; x++)
    {
        newBuffer[x] = new fcolor[height];
        for (int y = 0; y < height; y++) newBuffer[x][y] = pixelBuf[x][y];
    }

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            TRACER_FLOAT avgCol = (pixelBuf[x][y].r + pixelBuf[x][y].g + pixelBuf[x][y].b) / 3;

            for (TRACER_FLOAT rad = 1; rad < avgCol * radius; rad++)
            {
                int offsetX = 0;
                int offsetY = rad;
                int d = rad - 1;

                while (offsetY >= offsetX)
                {
                    if (x - offsetY >= 0.0 && x - offsetY < width && y + offsetX >= 0.0 && y + offsetX < height)
                    { newBuffer[x][y] += pixelBuf[x - offsetY][y + offsetX] / rad; }
                    if (x - offsetX >= 0.0 && x - offsetX < width && y + offsetY >= 0.0 && y + offsetY < height)
                    { newBuffer[x][y] += pixelBuf[x - offsetX][y + offsetY] / rad; }
                    if (x - offsetX >= 0.0 && x - offsetX < width && y - offsetY >= 0.0 && y - offsetY < height)
                    { newBuffer[x][y] += pixelBuf[x - offsetX][y - offsetY] / rad; }
                    if (x - offsetY >= 0.0 && x - offsetY < width && y - offsetX >= 0.0 && y - offsetX < height)
                    { newBuffer[x][y] += pixelBuf[x - offsetY][y - offsetX] / rad; }

                    if (d >= 2 * offsetX)
                    {
                        d -= 2 * offsetX + 1;
                        offsetX +=1;
                    }
                    else if (d < 2 * (radius - offsetY))
                    {
                        d += 2 * offsetY - 1;
                        offsetY -= 1;
                    }
                    else
                    {
                        d += 2 * (offsetY - offsetX - 1);
                        offsetY -= 1;
                        offsetX += 1;
                    }
                }
            }
        }
    }

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            pixelBuf[x][y] = newBuffer[x][y];
        }
        delete[] newBuffer[x];
    }
    delete[] newBuffer;
}