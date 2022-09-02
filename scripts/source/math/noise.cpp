#include <random>

#include <math/noise.h>
#include <math/lerp.h>

Noise1D::Noise1D() : Noise1D(10)
{ }

Noise1D::Noise1D(int _loopLength) : randoms(new TRACER_FLOAT[_loopLength])
{
    loopLength = _loopLength;

    std::default_random_engine generator;
    std::uniform_real_distribution<TRACER_FLOAT> distribution(0.0, 1.0);

    for (unsigned int i = 0; i < _loopLength; i++) randoms[i] = distribution(generator);
}

TRACER_FLOAT Noise1D::getValue(TRACER_FLOAT i)
{
    int iMin = (int)i % loopLength;
    TRACER_FLOAT t = i - iMin;

    return lerp(randoms[iMin], randoms[iMin + 1], t);
}