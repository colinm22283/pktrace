#include <iostream>
#include <thread>

#include <SDL.h>

#include "global.h"
#include "engine.h"
#include "event.h"
#include "script.h"
#include "console.h"
#include <config.h>
#include "debug.h"

#include <render/font.h>
#include <render/render.h>

#include "ui/menu.h"

#include <audio/audio.h>
#include <audio/midiPlayer.h>

double prevTime = 0;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool Engine::quit = false;
double Engine::currentTime = 0;
double Engine::deltaTime = 0;

bool Engine::init()
{
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    {
        debugError("Could not initialize SDL video, Error: " << SDL_GetError());
        return false;
    }

#if AUDIO_ENABLED

    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
    {
        debugError("Could not initialize SDL audio, Error: " << SDL_GetError());
        return false;
    }

    MIDIPlayer::init();

#endif

    SDL_CreateWindowAndRenderer(
        Global::windowWidth, Global::windowHeight, 0,
        &window, &renderer
    );
    if (window == nullptr)
    {
        debugError("Window could not be created, Error: " << SDL_GetError());
        return false;
    }

    return true;
}
void Engine::close()
{
#if AUDIO_ENABLED
    Audio::cleanup();
#endif

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}
bool Engine::start()
{
    debugPrint("Engine thread started at " << Engine::getTimeAsString().c_str());

    if (!Font::init())
    {
        debugError("Failed to initialize fonts");
        return false;
    }

#if AUDIO_ENABLED

    if (!Audio::init())
    {
        debugError("Failed to initialize audio");
        return false;
    }

    MIDIPlayer::init();

#endif

    if (Script::start) Script::start();

    std::thread eventThread(Event::init);
    std::thread timerThread(timerUpdate);

    while (!Engine::quit)
    {
        if (Global::fpsLimit != 0)
        {
            while ((double)(Engine::currentTime - prevTime) <= 1000.0 / Global::fpsLimit && !Engine::quit);
        }
        Engine::deltaTime = Engine::currentTime - prevTime;
        prevTime = Engine::currentTime;
        Engine::update();
    }

    if (Script::exit) Script::exit();

    eventThread.join();
    timerThread.join();

    debugPrint("Engine thread killed at " << Engine::getTimeAsString().c_str());

    return true;
}
int fpsTimer = 500;
float fpsRead = 0;
void Engine::update()
{
    Render::clearScreen(CLEAR_COLOR);

#ifdef PEAK_ENGINE_MENU_ENABLED

    Menu::update();

#endif

    if (Script::update) Script::update();
    Console::update();

#if AUDIO_ENABLED

    MIDIPlayer::update();

#endif

    if (Global::fpsOutput)
    {
        if (fpsTimer > 500)
        {
            fpsRead = 1000.0f / (float)Engine::deltaTime;
            fpsTimer -= 500;
        }

        Render::setColor({ 0, 0, 0, 255 });
        Render::fillRect(0, Global::windowHeight - 25, 150, 25, { 255, 255, 255, 255 });
        Render::drawText(10, Global::windowHeight - 20, // draw fps output
            Font::consolas,
            std::to_string(fpsRead) + " fps",
            0.7
        );

        fpsTimer += (int)Engine::deltaTime;
    }

    Render::present();
}
void Engine::timerUpdate()
{
    debugPrint("Timer thread started at " << Engine::getTimeAsString().c_str());
    while (!Engine::quit) {
        currentTime++;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    debugPrint("Timer thread killed at " << Engine::getTimeAsString().c_str());
}

void Engine::exit()
{ Engine::quit = true; }

void Engine::resizeWindow(unsigned int w, unsigned int h)
{
    Global::windowWidth = w;
    Global::windowHeight = h;
    SDL_SetWindowSize(window, w, h);
}

FixedString Engine::getTimeAsString()
{
    FixedString proto(23);

    proto.insert((FixedString::toString((long)Engine::currentTime / 86400000, 2) + "d ").c_str(), 0);
    proto.insert((FixedString::toString((long)Engine::currentTime / 3600000 % 24, 2) + "h ").c_str(), 4);
    proto.insert((FixedString::toString((long)Engine::currentTime / 60000 % 60, 2) + "m ").c_str(), 8);
    proto.insert((FixedString::toString((long)Engine::currentTime / 1000 % 60, 2) + "s ").c_str(), 12);
    proto.insert((FixedString::toString((long)Engine::currentTime % 1000, 4) + "ms").c_str(), 16);

    return proto;
}