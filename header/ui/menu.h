#pragma once

#include <vector>

#include <ui/menuElement.h>

#define PEAK_ENGINE_MENU_ENABLED

class Menu
{
public:
    static MenuElement* activeElement;

    static void update();
    static void mouseClick();
    static void keyDown(SDL_Keysym keysym);

    bool active;
    unsigned int x;
    unsigned int y;

    std::vector<MenuElement*> elements;

    Menu();
    Menu(unsigned int x, unsigned int y);
    ~Menu();

    void addElement(MenuElement* ele);
    void draw();

private:
    unsigned int listPos;
};