#include <SDL.h>
#include <iostream>

#include "script.h"
#include "event.h"
#include "console.h"
#include "consoleParser.h"
#include "engine.h"
#include "input.h"
#include "global.h"
#include "debug.h"

#include "ui/menu.h"

SDL_Event Event::event;

void Event::init()
{
    debugPrint("Event thread started at " << Engine::getTimeAsString().c_str());
    while (!Engine::quit)
    {
        Event::update();
    }
    debugPrint("Event thread killed at " << Engine::getTimeAsString().c_str());
}
void Event::update()
{
    if (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            Engine::quit = true;
            break;
        case SDL_KEYDOWN:
            ConsoleParser::keyDown(event.key.keysym);
            Console::keyDown(event.key.keysym);

#ifdef PEAK_ENGINE_MENU_ENABLED

            Menu::keyDown(event.key.keysym);

#endif

            if (Script::keyDown) Script::keyDown(event.key.keysym);
            if (Global::printKeys) Console::print("Key: " + std::to_string(event.key.keysym.sym));
            break;
        case SDL_KEYUP:
            if (Script::keyUp) Script::keyUp(event.key.keysym);
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&Input::mouseX, &Input::mouseY);
            break;
        case SDL_MOUSEBUTTONDOWN:
        {
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                Input::mouseLeft = true;

#ifdef PEAK_ENGINE_MENU_ENABLED

                Menu::mouseClick();

#endif
                break;
            case SDL_BUTTON_MIDDLE:
                Input::mouseMiddle = true;
                break;
            case SDL_BUTTON_RIGHT:
                Input::mouseRight = true;
                break;
            }
        } break;
        case SDL_MOUSEBUTTONUP:
        {
            if (Script::mouseClick) Script::mouseClick(event.button.button);

            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                Input::mouseLeft = false;
                break;
            case SDL_BUTTON_MIDDLE:
                Input::mouseMiddle = false;
                break;
            case SDL_BUTTON_RIGHT:
                Input::mouseRight = false;
                break;
            }
        } break;
        }
    }
    if (Script::mouseDown)
    {
        if (Input::mouseLeft) Script::mouseDown(SDL_BUTTON_LEFT);
        if (Input::mouseMiddle) Script::mouseDown(SDL_BUTTON_MIDDLE);
        if (Input::mouseRight) Script::mouseDown(SDL_BUTTON_RIGHT);
    }
}