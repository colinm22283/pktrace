#include <config.h>

#if AUDIO_ENABLED

#include <iostream>
#include <vector>

#include <SDL_audio.h>

#include <audio.h>

#include <misc/clamp.h>

#include <audio/audio.h>
#include <audio/channel.h>

bool Audio::playing = true;
unsigned short Audio::volume = 1;

track* emptyTrack;

std::vector<track*> tracks;

audioChannel channels[AUDIO_MAX_SOUNDS];

static inline void mixAudio(void* unused, unsigned char* stream, int len)
{
    for (unsigned int i = 0; i < len; i++) stream[i] = 0;

    if (Audio::playing)
    {
        for (unsigned int i = 0; i < AUDIO_MAX_SOUNDS; i++)
        {
            if (channels[i].playing)
            {
                unsigned int amount = channels[i].t->len - channels[i].pos;

                if (amount > len) amount = len;
                for (unsigned int j = 0; j < amount; j++)
                {
                    stream[j] += CLAMP((channels[i].t->data + channels[i].pos)[j] * channels[i].volume * Audio::volume, 0, 255);
                }
                channels[i].pos += amount;

                if (channels[i].pos >= channels[i].t->len)
                {
                    if (channels[i].flags & CHANNEL_FLAGS_LOOPING)
                    {
                        channels[i].pos = 0;

                        for (unsigned int j = amount; j < len; j++)
                        {
                            stream[j] += CLAMP((channels[i].t->data + channels[i].pos)[j] * channels[i].volume * Audio::volume, 0, 255);
                        }

                        channels[i].pos += len - amount;
                    }
                    else channels[i].playing = false;
                }
            }
        }
    }
}

#pragma region Engine Functions

bool Audio::init()
{
    emptyTrack = new track { nullptr, 0 };

    for (unsigned int i = 0; i < AUDIO_MAX_SOUNDS; i++)
    {
        channels[i].t = emptyTrack;
        channels[i].pos = 0;
        channels[i].volume = 1;
        channels[i].playing = false;
    }

    SDL_AudioSpec fmt;

    fmt.freq = AUDIO_FREQUENCY;
    fmt.format = AUDIO_FORMAT;
    fmt.channels = AUDIO_CHANNELS;
    fmt.samples = AUDIO_SAMPLES;
    fmt.callback = mixAudio;
    fmt.userdata = nullptr;

    if (SDL_OpenAudio(&fmt, NULL) < 0)
    {
        std::cout << "Unable to open SDL audio: " << SDL_GetError() << '\n';
        return false;
    }

    SDL_PauseAudio(0);

    return true;
}

void Audio::cleanup()
{
    SDL_CloseAudio();

    delete emptyTrack;
}

#pragma endregion

track* Audio::loadWav(const char* path)
{
    SDL_AudioSpec wave;
    unsigned char* data;
    unsigned int len;
    SDL_AudioCVT cvt;

    if (SDL_LoadWAV(path, &wave, &data, &len) == NULL) {
        std::cout << "Couldn't load WAV file: " << SDL_GetError() << '\n';
        return nullptr;
    }
    SDL_BuildAudioCVT(
        &cvt,
        wave.format, wave.channels, wave.freq,
        AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_FREQUENCY
    );

    cvt.buf = (unsigned char*)malloc(len * cvt.len_mult);
    memcpy(cvt.buf, data, len);
    cvt.len = len;

    SDL_ConvertAudio(&cvt);
    SDL_FreeWAV(data);

    track* proto = new track
    {
        cvt.buf,
        (unsigned int)cvt.len_cvt
    };

    return proto;
}
bool Audio::freeTrack(track* t)
{
    unsigned int i;
    for (i = 0; i < (unsigned int)tracks.size(); i++)
    {
        if (tracks[i] == t)
        {
            free(t->data);
            delete t;
            tracks.erase(tracks.begin() + i);

            break;
        }
    }
    if (i == (unsigned int)tracks.size()) return false;
    return true;
}

bool Audio::playTrack(track *t, unsigned char flags, unsigned short _volume, unsigned int position)
{
    unsigned int index;
    for (index = 0; index < AUDIO_MAX_SOUNDS; index++)
    {
        if (channels[index].pos == channels[index].t->len) break;
    }
    if (index == AUDIO_MAX_SOUNDS)
    {
        std::cout << "Over audio limit\n";
        return false;
    }

    SDL_LockAudio();

    channels[index].t = t;
    channels[index].pos = position;

    channels[index].volume = _volume;
    channels[index].playing = true;
    channels[index].flags = flags;

    SDL_UnlockAudio();

    return true;
}
bool Audio::playTrack(track *t, unsigned char flags, unsigned short _volume) { return Audio::playTrack(t, flags, _volume, 0); }
bool Audio::playTrack(track *t, unsigned char flags) { return Audio::playTrack(t, flags, 1); }
bool Audio::playTrack(track *t) { return Audio::playTrack(t, false); }

void Audio::stopAll() { for (unsigned int i = 0; i < AUDIO_MAX_SOUNDS; i++) channels[i].pos = channels[i].t->len; }

#endif