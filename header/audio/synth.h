#pragma once

#include <audio/track.h>

#if AUDIO_ENABLED

namespace Synth
{
    track* sineWave(unsigned int frequency, unsigned int length);
}

#endif