#pragma once

#include <config.h>

#include <thread>

struct midiNote
{
    unsigned int pitch;
    unsigned int length;
};

struct midiStep
{
    unsigned int noteCount;
    midiNote* notes;
};

class MIDI
{
public:
    unsigned short deltaTime;
    unsigned int stepCount;
    midiStep* steps;

    MIDI();
    MIDI(unsigned int length, unsigned short _deltaTime);
    MIDI(const char* path);
    ~MIDI();
};