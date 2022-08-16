#pragma once

#include <string>

#include "render/font.h"
#include "render/color.h"

enum menuElementType { NONE, LABEL, BUTTON, INPUT };

class MenuElement
{
public:
    MenuElement();

    int x;
    int y;
    virtual int w();
    virtual int h();

    menuElementType getType();

protected:
    menuElementType type;
};

class LabelElement : public MenuElement
{
public:
    LabelElement();
    LabelElement(int x, int y, const char* label, TTF_Font* _font);
    LabelElement(int x, int y, const char* label, TTF_Font* _font, color col);
    ~LabelElement();

    int w();
    int h();

    color col;

    TTF_Font* font;
    char* label;

    int _w;
    int _h;
};

class ButtonElement : public LabelElement
{
public:
    ButtonElement();
    ButtonElement(int x, int y, const char* label, TTF_Font* font);
    ButtonElement(int x, int y, const char* label, TTF_Font* font, color foregroundColor, color backgroundColor);

    int w;
    int h;

    TTF_Font* font;

    color foregroundColor;
    color backgroundColor;

    void press();
    bool isPressed();

private:
    bool pressed;
};

class InputElement : public MenuElement
{
public:
    InputElement();
    InputElement(int x, int y, const std::string* value, TTF_Font* font);
    InputElement(int x, int y, const std::string* value, TTF_Font* font, color foregroundColor, color backgroundColor);

    bool active;

    int w;
    int h;

    TTF_Font* font;
    const std::string* value;

    color foregroundColor;
    color backgroundColor;

    void keyDown(SDL_Keysym keysym);
};