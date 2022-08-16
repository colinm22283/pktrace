#pragma once

#include <config.h>

#if AUDIO_ENABLED

#include <stdint.h>

#include "track.h"

struct audioChannel
{
    track* t;

    unsigned int pos;

    unsigned short volume;
    bool playing;
    unsigned char flags;
};

#endif