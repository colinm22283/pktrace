#pragma once

#include <config.h>

#if AUDIO_ENABLED

#pragma region CHANNEL_FLAG_DEFINES

#define CHANNEL_FLAGS_NONE         (0x00) // 00000000
#define CHANNEL_FLAGS_LOOPING      (0x01) // 00000001
#define CHANNEL_FLAGS_FLAG2        (0x02) // 00000010
#define CHANNEL_FLAGS_FLAG3        (0x04) // 00000100
#define CHANNEL_FLAGS_FLAG4        (0x08) // 00001000
#define CHANNEL_FLAGS_FLAG5        (0x10) // 00010000
#define CHANNEL_FLAGS_FLAG6        (0x20) // 00100000
#define CHANNEL_FLAGS_FLAG7        (0x40) // 01000000
#define CHANNEL_FLAGS_FLAG8        (0x80) // 10000000

#pragma endregion

#include <audio/track.h>

namespace Audio
{
    extern bool playing;
    extern unsigned short volume;

    bool init();
    void cleanup();

    track* loadWav(const char* path);
    bool freeTrack(track* t);

    bool playTrack(track* t, unsigned char flags, unsigned short volume, unsigned int position);
    bool playTrack(track* t, unsigned char flags, unsigned short volume);
    bool playTrack(track* t, unsigned char flags);
    bool playTrack(track* t);

    void stopAll();
}

#endif