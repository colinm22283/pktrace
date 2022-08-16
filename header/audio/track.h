#pragma once

#include <config.h>

#if AUDIO_ENABLED

struct track
{
    unsigned char* data;
    unsigned int len;
};

#endif