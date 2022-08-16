#pragma once

#include <SDL.h>
#include <string>
#include <vector>

namespace Console
{
    extern bool visible;
    extern std::string output;
    extern std::string input;
    extern std::vector<std::string> history;

    void print(const std::string message);
    void update();
    void keyDown(SDL_Keysym keysym);
}