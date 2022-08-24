#include <texture.h>

#include <img/bmp.h>

Texture::Texture()
{ }
Texture::Texture(const char *bmpPath) : tex((img*)new bmp(bmpPath)), scale(1.0)
{ }
Texture::Texture(const char *bmpPath, double _scale) : tex((img*)new bmp(bmpPath)), scale(_scale)
{ }

color Texture::getPixel(int _x, int _y)
{
    int x = _x % tex->width;
    int y = _y % tex->height;

    if (x < 0) x += tex->width;
    if (y < 0) y += tex->height;
    return tex->getPixel(x, y);
}