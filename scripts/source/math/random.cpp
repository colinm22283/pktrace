#include <random>

#include <math/random.h>

unsigned int currentPos = 0;
TRACER_FLOAT randValues[RANDOM_VALUE_COUNT];

void randomInit()
{
    std::default_random_engine generator;
    std::uniform_real_distribution<TRACER_FLOAT> distribution(0.0, 1.0);

    for (unsigned int i = 0; i < RANDOM_VALUE_COUNT; i++) randValues[i] = distribution(generator);
}

TRACER_FLOAT randomRange()
{
    currentPos++;
    if (currentPos > RANDOM_VALUE_COUNT) currentPos = 0;

    return randValues[currentPos];
}
TRACER_FLOAT randomRange(const double max)
{
    currentPos++;
    if (currentPos > RANDOM_VALUE_COUNT) currentPos = 0;

    return randValues[currentPos] * max;
}
TRACER_FLOAT randomRange(const double min, const double max)
{
    currentPos++;
    if (currentPos > RANDOM_VALUE_COUNT) currentPos = 0;

    return randValues[currentPos] * (max - min) + min;
}