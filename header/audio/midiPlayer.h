#pragma once

#include <config.h>

#if AUDIO_ENABLED

#include <audio.h>

#include <audio/midi.h>

struct midiChannel
{
    MIDI* midi;
    unsigned int position;
    unsigned short time;
};

namespace MIDIPlayer
{
    void play(MIDI* midi);

    void init();
    void update();
}

#endif