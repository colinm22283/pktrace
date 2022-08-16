#include <cmath>
#include <iostream>

#include <audio.h>

#include <audio/synth.h>

track* Synth::sineWave(unsigned int frequency, unsigned int length)
{
    unsigned char* data = new unsigned char[length / 1000 * AUDIO_FREQUENCY * AUDIO_CHANNELS];

    for (unsigned int i = 0; i < length / 1000 * AUDIO_FREQUENCY * AUDIO_CHANNELS; i += AUDIO_CHANNELS)
    {
        for (unsigned int j = 0; j < AUDIO_CHANNELS; j++)
        {
            data[i + j] = (char)(sinf32((float) i / AUDIO_CHANNELS / AUDIO_FREQUENCY * M_PI * 2 * frequency) * 10);
        }
    }

    return new track {
        data,
        length / 1000 * AUDIO_FREQUENCY * AUDIO_CHANNELS
    };
}