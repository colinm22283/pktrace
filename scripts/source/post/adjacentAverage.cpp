#include <thread>

#include <post/adjacentAverage.h>

AdjacentAverage::AdjacentAverage(int _averageSize) : averageSize(_averageSize)
{ }

void AdjacentAverage::activate(fcolor **pixelBuf, int width, int height)
{
    fcolor** oldBuffer = new fcolor*[width];
    for (int x = 0; x < width; x++)
    {
        oldBuffer[x] = new fcolor[height];
        for (int y = 0; y < height; y++) oldBuffer[x][y] = pixelBuf[x][y];
    }

    int area = 4 * averageSize * averageSize + 4 * averageSize + 1;

    for (int x = averageSize; x < width - averageSize; x++)
    {
        for (int y = averageSize; y < height - averageSize; y++)
        {
            fcolor sum = FGS(0.0);

            for (int x2 = -averageSize; x2 <= averageSize; x2++)
            {
                for (int y2 = -averageSize; y2 <= averageSize; y2++)
                {
                    if (x2 != 0 || y2 != 0)
                    {
                        sum += oldBuffer[x + x2][y + y2];
                    }
                }
            }

            pixelBuf[x][y] = sum / area;
        }
    }

    for (int x = 0; x < width; x++) delete[] oldBuffer[x];
    delete[] oldBuffer;
}