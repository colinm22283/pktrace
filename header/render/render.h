#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "global.h"
#include "color.h"

#pragma region RENDER_FLAG_DEFINES

#define RENDER_FLAGS_NONE         (0x00) // 00000000
#define RENDER_FLAGS_CULLING      (0x01) // 00000001
#define RENDER_FLAGS_FLAG2        (0x02) // 00000010
#define RENDER_FLAGS_FLAG3        (0x04) // 00000100
#define RENDER_FLAGS_FLAG4        (0x08) // 00001000
#define RENDER_FLAGS_FLAG5        (0x10) // 00010000
#define RENDER_FLAGS_FLAG6        (0x20) // 00100000
#define RENDER_FLAGS_FLAG7        (0x40) // 01000000
#define RENDER_FLAGS_FLAG8        (0x80) // 10000000

#pragma endregion

namespace Render
{
    extern color c;
    extern unsigned char flags;

    void setColor(color c); //                                         Set the color of the renderer
    void present(); //                                                 Present new pixels to the screen

    void clearScreen(); //                                             Clear the screen
    void clearScreen(color c);
    void drawPixel(int x, int y); //                                   Draw a pixel on screen
    void drawPixel(int x, int y, color c);
    void drawLine(int x1, int y1, int x2, int y2); //                  Draw a line on screen
    void drawLine(int x1, int y1, int x2, int y2, color c);
    void drawRect(int x, int y, int w, int h); //                      Draw a rectangle on screen
    void drawRect(int x, int y, int w, int h, color c);
    void fillRect(int x, int y, int w, int h); //                      Draw a filled rectangle on screen
    void fillRect(int x, int y, int w, int h, color c);
    void drawText(int x, int y, TTF_Font* font, const std::string str); //    Draw a text string
    void drawText(int x, int y, TTF_Font* font, const std::string str, float scale);
}