#include <iostream>

#include "input.h"
#include "render/render.h"
#include "render/font.h"
#include "console.h"

#include <ui/menu.h>

std::vector<Menu*> menus;

#pragma region Static Members

MenuElement* Menu::activeElement = nullptr;

void Menu::update()
{
    for (unsigned int i = 0; i < (unsigned int)menus.size(); i++)
    {
        menus[i]->draw();
    }
}

void Menu::mouseClick()
{
    bool foundEle = false;

    for (unsigned int i = 0; i < (unsigned int)menus.size(); i++)
    {
        for (unsigned int j = 0; j < (unsigned int) menus[i]->elements.size(); j++)
        {
            switch (menus[i]->elements[j]->getType())
            {
                case BUTTON: {
                    ButtonElement *ele = (ButtonElement *) menus[i]->elements[j];

                    if (
                        Input::mouseX >= menus[i]->x + ele->x &&
                        Input::mouseY >= menus[i]->y + ele->y &&
                        Input::mouseX <= menus[i]->x + ele->x + ele->w &&
                        Input::mouseY <= menus[i]->y + ele->y + ele->h
                    ) ele->press();
                } break;
                case INPUT: {
                    InputElement *ele = (InputElement *) menus[i]->elements[j];

                    if (
                        Input::mouseX >= menus[i]->x + ele->x &&
                        Input::mouseY >= menus[i]->y + ele->y &&
                        Input::mouseX <= menus[i]->x + ele->x + ele->w &&
                        Input::mouseY <= menus[i]->y + ele->y + ele->h
                    )
                    {
                        std::cout << "test\n";
                        Menu::activeElement = ele;
                        ele->active = true;
                        foundEle = true;
                    }
                } break;
            }
        }
    }

    if (!foundEle) Menu::activeElement = nullptr;
}

void Menu::keyDown(SDL_Keysym keysym) { if (!Console::visible)
{
    for (unsigned int i = 0; i < (unsigned int)menus.size(); i++)
    {
        if (menus[i]->active)
        {
            for (unsigned int j = 0; j < (unsigned int) menus[i]->elements.size(); j++)
            {
                switch (menus[i]->elements[j]->getType())
                {
                    case INPUT: {
                        InputElement *ele = (InputElement*)menus[i]->elements[j];

                        ele->keyDown(keysym);
                    } break;
                }
            }
        }
    }
} }

#pragma endregion

Menu::Menu() : Menu(0, 0) { }
Menu::Menu(unsigned int _x, unsigned int _y)
{
    active = true;
    x = _x;
    y = _y;

    listPos = menus.size();
    menus.push_back(this);
}
Menu::~Menu()
{
    menus.erase(menus.begin() + listPos);
}

void Menu::addElement(MenuElement* ele) { elements.push_back(ele); }

void Menu::draw() { if (active)
{
    for (unsigned int i = 0; i < (unsigned int)elements.size(); i++)
    {
        switch (elements[i]->getType())
        {
            case LABEL:
            {
                LabelElement* ele = (LabelElement*)elements[i];

                Render::setColor(ele->col);
                Render::drawText(x + ele->x, y + ele->y, ele->font, ele->label);
            } break;
            case BUTTON:
            {
                ButtonElement* ele = (ButtonElement*)elements[i];

                Render::fillRect(x + ele->x, y + ele->y, ele->w, ele->h, ele->backgroundColor);
                Render::setColor(ele->foregroundColor);
                Render::drawText(x + ele->x + 2, y + ele->y, ele->font, ele->label);
                Render::drawRect(x + ele->x, y + ele->y, ele->w, ele->h);
            } break;
            case INPUT:
            {
                InputElement* ele = (InputElement*)elements[i];

                if (ele->active)
                {
                    Render::fillRect(x + ele->x, y + ele->y, ele->w + 20, ele->h, ele->backgroundColor);
                    Render::setColor(ele->foregroundColor);
                    Render::drawText(x + ele->x + 2, y + ele->y, ele->font, *ele->value + "|");
                }
                else
                {
                    Render::fillRect(x + ele->x, y + ele->y, ele->w, ele->h, ele->backgroundColor);
                    Render::setColor(ele->foregroundColor);
                    Render::drawText(x + ele->x + 2, y + ele->y, ele->font, *ele->value);
                }
                Render::drawRect(x + ele->x, y + ele->y, ele->w, ele->h);
            } break;
        }
    }
} }