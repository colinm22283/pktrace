#pragma once

#include <string>

#include "SDL.h"

namespace Script
{
    void start()                                        __attribute__((weak));
    void update()                                       __attribute__((weak));
    void keyDown(SDL_Keysym keysym)                     __attribute__((weak));
    void keyUp(SDL_Keysym keysym)                       __attribute__((weak));
    void mouseDown(int button)                          __attribute__((weak));
    void mouseClick(int button)                         __attribute__((weak));
    void exit()                                         __attribute__((weak));
    bool setVar(std::string var, std::string value)     __attribute__((weak));
    bool command(std::string cmd, std::string params)   __attribute__((weak));
}