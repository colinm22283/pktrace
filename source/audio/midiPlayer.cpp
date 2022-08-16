#include <config.h>

#if AUDIO_ENABLED

#include <vector>

#include <engine.h>

#include <audio/audio.h>
#include <audio/synth.h>
#include <audio/midiPlayer.h>

std::vector<track*> trackBuffers[AUDIO_MAX_MIDIS];
midiChannel midiChannels[AUDIO_MAX_MIDIS];

void MIDIPlayer::play(MIDI* midi)
{
    for (unsigned int i = 0; i < AUDIO_MAX_MIDIS; i++)
    {
        if (midiChannels[i].midi == nullptr)
        {
            midiChannels[i] = { midi, 0, 0 };
        }
    }
}

void MIDIPlayer::init()
{
    for (unsigned int i = 0; i < AUDIO_MAX_MIDIS; i++)
    {
        midiChannels[i] = { nullptr, 0, 0 };
    }
}

void MIDIPlayer::update()
{
    for (unsigned int i = 0; i < AUDIO_MAX_MIDIS; i++)
    {
        if (midiChannels[i].midi != nullptr)
        {
            midiChannels[i].time += Engine::deltaTime;

            if (midiChannels[i].time > midiChannels[i].midi->deltaTime)
            {
                for (unsigned int j = 0; j < midiChannels[i].midi->steps[midiChannels[i].position].noteCount; j++)
                {
                    track* temp = Synth::sineWave(
                        midiChannels[i].midi->steps[midiChannels[i].position].notes[j].pitch,
                        midiChannels[i].midi->steps[midiChannels[i].position].notes[j].length
                    );
                    trackBuffers[i].push_back(temp);
                    Audio::playTrack(temp);
                }

                midiChannels[i].time -= midiChannels[i].midi->deltaTime;
                midiChannels[i].position++;

                if (midiChannels[i].position >= midiChannels[i].midi->stepCount)
                {
                    midiChannels[i].midi = nullptr;

                    for (unsigned int j = 0; j < (unsigned int)trackBuffers[i].size(); j++)
                    { Audio::freeTrack(trackBuffers[i][j]); }
                    trackBuffers[i].clear();
                }
            }
        }
    }
}

#endif