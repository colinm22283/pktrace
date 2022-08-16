#include <iostream>

#include <misc/strLen.h>

#include <ui/menuElement.h>

#pragma region Menu Element

MenuElement::MenuElement() { type = menuElementType::NONE; };
menuElementType MenuElement::getType() { return type; }

int MenuElement::w() { return 0; };
int MenuElement::h() { return 0; };

#pragma endregion

#pragma region Label Element

LabelElement::LabelElement()
{
    type = menuElementType::LABEL;

    font = nullptr;

    label = new char[1];
    label[0] = 0x00;
}
LabelElement::LabelElement(int _x, int _y, const char* _label, TTF_Font* _font) : LabelElement(_x, _y, _label, _font, GS(255))
{ }
LabelElement::LabelElement(int _x, int _y, const char* _label, TTF_Font* _font, color _col)
{
    type = menuElementType::LABEL;
    x = _x;
    y = _y;

    font = _font;

    unsigned int length = strLen(_label) + 1;

    label = new char[length];
    for (unsigned int i = 0; i < length; i++) label[i] = _label[i];

    TTF_SizeText(font, label, &_w, &_h);

    col = _col;
}
LabelElement::~LabelElement()
{
    delete[] label;
}

int LabelElement::w()
{
    return _w;
}
int LabelElement::h()
{
    return _h;
}

#pragma endregion

#pragma region Button Element

ButtonElement::ButtonElement()
{
    type = menuElementType::BUTTON;

    label = nullptr;

    pressed = false;
}
ButtonElement::ButtonElement(int _x, int _y, const char* _label, TTF_Font* _font) : LabelElement(_x, _y, _label, _font)
{
    type = menuElementType::BUTTON;

    pressed = false;

    TTF_SizeText(font, label, &w, &h);
    w += 4;

    backgroundColor = GS(255);
    foregroundColor = GS(0);
}
ButtonElement::ButtonElement(int _x, int _y, const char* _label, TTF_Font* _font, color _foregroundColor, color _backgroundColor) : ButtonElement(_x, _y, _label, _font)
{ foregroundColor = _foregroundColor; backgroundColor = _backgroundColor; }

void ButtonElement::press() { pressed = true; }
bool ButtonElement::isPressed()
{
    if (pressed)
    {
        pressed = false;
        return true;
    }
    return false;
}

#pragma endregion

#pragma region Input Element

InputElement::InputElement(int _x, int _y, const std::string* _value, TTF_Font* _font, color _foregroundColor, color _backgroundColor)
{
    type = menuElementType::INPUT;

    x = _x;
    y = _y;

    value = _value;
    font = _font;

    TTF_SizeText(font, value->c_str(), &w, &h);
    w += 4;

    foregroundColor = _foregroundColor;
    backgroundColor = _backgroundColor;

    active = false;
}
InputElement::InputElement(int _x, int _y, const std::string* _value, TTF_Font *_font) : InputElement(_x, _y, _value, _font, GS(0), GS(255)) { }
InputElement::InputElement() : InputElement(0, 0, nullptr, nullptr) { }

void InputElement::keyDown(SDL_Keysym keysym) { if (active)
{
    std::cout << keysym.sym << '\n';

    switch (keysym.sym)
    {
        case 8:
        {
            if (value->length() > 0) *((std::string*)value) = value->substr(0, value->length() - 1);
        } break;
        default:
        {
            if (keysym.sym >= 97 && keysym.sym <= 122)
            {
                *((std::string*)value) += (char)keysym.sym;
            }
        }
    }

    TTF_SizeText(font, value->c_str(), &w, &h);
    w += 4;
} }

#pragma endregion