#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include <config.h>

#include "global.h"
#include "render/render.h"
#include "engine.h"
#include "render/color.h"

#include "misc/minMax.h"

color Render::c = { 255, 255, 255, 255 };

unsigned char Render::flags = RENDER_DEFAULT_FLAGS;

void Render::setColor(color col)
{
    Render::c = col;
}

void Render::clearScreen()
{
    SDL_SetRenderDrawColor(renderer, Render::c.r, Render::c.g, Render::c.b, Render::c.a);
    SDL_RenderClear(renderer);
}
void Render::clearScreen(color col)
{
    SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
    SDL_RenderClear(renderer);
}
void Render::drawPixel(int x, int y)
{
    if (flags & RENDER_FLAGS_CULLING)
    {
        if (x >= 0 && y >= 0 && x < Global::windowWidth && y < Global::windowHeight)
        {
            SDL_SetRenderDrawColor(renderer, Render::c.r, Render::c.g, Render::c.b, Render::c.a);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, Render::c.r, Render::c.g, Render::c.b, Render::c.a);
        SDL_RenderDrawPoint(renderer, x, y);
    }
}
void Render::drawPixel(int x, int y, color col)
{
    if (flags & RENDER_FLAGS_CULLING)
    {
        if (x >= 0 && y >= 0 && x < Global::windowWidth && y < Global::windowHeight)
        {
            SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
        SDL_RenderDrawPoint(renderer, x, y);
    }
}
void Render::drawLine(int x1, int y1, int x2, int y2)
{
    SDL_SetRenderDrawColor(renderer, Render::c.r, Render::c.g, Render::c.b, Render::c.a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}
void Render::drawLine(int x1, int y1, int x2, int y2, color col)
{
    SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}
void Render::drawRect(int x, int y, int w, int h)
{
    if (flags & RENDER_FLAGS_CULLING)
    {
        x = MAX(x, 0);
        y = MAX(y, 0);
        w = (x + w > Global::windowWidth) ? Global::windowWidth - x : w;
        h = (y + h > Global::windowHeight) ? Global::windowHeight - y : h;

        if (w < 0 || h < 0 || x > Global::windowWidth - 1 || y > Global::windowHeight - 1) return;
    }

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_SetRenderDrawColor(renderer, Render::c.r, Render::c.g, Render::c.b, Render::c.a);
    SDL_RenderDrawRect(renderer, &rect);
}
void Render::drawRect(int x, int y, int w, int h, color col)
{
    if (flags & RENDER_FLAGS_CULLING)
    {
        x = MAX(x, 0);
        y = MAX(y, 0);
        w = (x + w > Global::windowWidth) ? Global::windowWidth - x : w;
        h = (y + h > Global::windowHeight) ? Global::windowHeight - y : h;

        if (w < 0 || h < 0 || x > Global::windowWidth - 1 || y > Global::windowHeight - 1) return;
    }

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
    SDL_RenderDrawRect(renderer, &rect);
}
void Render::fillRect(int x, int y, int w, int h)
{
    if (flags & RENDER_FLAGS_CULLING)
    {
        x = MAX(x, 0);
        y = MAX(y, 0);
        w = (x + w > Global::windowWidth) ? Global::windowWidth - x : w;
        h = (y + h > Global::windowHeight) ? Global::windowHeight - y : h;

        if (w < 0 || h < 0 || x > Global::windowWidth - 1 || y > Global::windowHeight - 1) return;
    }

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_SetRenderDrawColor(renderer, Render::c.r, Render::c.g, Render::c.b, Render::c.a);
    SDL_RenderFillRect(renderer, &rect);
}
void Render::fillRect(int x, int y, int w, int h, color col)
{
    if (flags & RENDER_FLAGS_CULLING)
    {
        x = MAX(x, 0);
        y = MAX(y, 0);
        w = (x + w > Global::windowWidth) ? Global::windowWidth - x : w;
        h = (y + h > Global::windowHeight) ? Global::windowHeight - y : h;

        if (w < 0 || h < 0 || x > Global::windowWidth - 1 || y > Global::windowHeight - 1) return;
    }

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
    SDL_RenderFillRect(renderer, &rect);
}

void Render::drawText(int x, int y, TTF_Font* font, const std::string str)
{
    int charHeight;

    TTF_SizeText(font, nullptr, nullptr, &charHeight);

    if (flags & RENDER_FLAGS_CULLING && !(x >= 0 && y >= -charHeight && x < Global::windowWidth && y < Global::windowHeight + charHeight)) return;

    if (str.length() == 0) return;

    const char *temp = str.c_str();
    SDL_Surface *textSurface;
    SDL_Color col = { Render::c.r, Render::c.g, Render::c.b, Render::c.a };

    textSurface = TTF_RenderText_Solid(font, temp, col);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, textSurface);
    int w = textSurface->w;
    int h = textSurface->h;

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_RenderCopy(renderer, tex, nullptr, &rect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(tex);
}
void Render::drawText(int x, int y, TTF_Font* font, const std::string str, float scale)
{
    int charHeight;

    TTF_SizeText(font, nullptr, nullptr, &charHeight);

    if (flags & RENDER_FLAGS_CULLING && !(x >= 0 && y >= -charHeight && x < Global::windowWidth && y < Global::windowHeight + charHeight)) return;

    if (str.length() == 0) return;

    const char *temp = str.c_str();
    SDL_Surface *textSurface;
    SDL_Color col = { Render::c.r, Render::c.g, Render::c.b, Render::c.a };

    textSurface = TTF_RenderText_Solid(font, temp, col);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, textSurface);
    int w = (int)(textSurface->w * scale);
    int h = (int)(textSurface->h * scale);

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_RenderCopy(renderer, tex, nullptr, &rect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(tex);
}

void Render::present()
{
    SDL_RenderPresent(renderer);
}