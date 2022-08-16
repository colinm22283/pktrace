#pragma once

#include <SDL.h>

#include <misc/fixedString.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;

namespace Engine
{
    extern bool quit;
    extern double currentTime;
    extern double deltaTime;

    bool init(); //                                        Initialize the engine
    void close(); //                                       Stop the engine

    bool start();
    void update();

    void timerUpdate();

    void exit();
    void resizeWindow(unsigned int w, unsigned int h);

    FixedString getTimeAsString();
}