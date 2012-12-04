#include "Engine/Surface.h"
#include "Fallout/FrmFileType.h"

namespace Falltergeist
{

Surface::Surface(int width, int height, int x, int y) : _x(x), _y(y)
{
    needRedraw = true;
    _borderColor = 0;
    _surface = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xFF000000);
    clear();
    //SDL_SetColorKey(_surface, SDL_SRCCOLORKEY, 0);

    if (_surface == 0) throw Exception(SDL_GetError());
}

Surface::Surface(Surface * other)
{
    _surface = SDL_ConvertSurface(other->_surface, other->_surface->format, other->_surface->flags);
    _x = other->_x;
    _y = other->_y;
}

Surface::~Surface()
{
    SDL_FreeSurface(_surface);
}

int Surface::getX()
{
    return _x;
}

int Surface::getY()
{
    return _y;
}

int Surface::getWidth()
{
    return _surface->w;
}

int Surface::getHeight()
{
    return _surface->h;
}

void Surface::setX(int x)
{
    _x = x;
}

void Surface::setY(int y)
{
    _y = y;
}

void Surface::clear()
{
    fill(0);
}

SDL_Surface * Surface::getSurface()
{
    if (needRedraw)
    {
        draw();
        needRedraw = false;
    }
    return _surface;
}

void Surface::think()
{
}

void Surface::draw()
{
    if (_borderColor) border(_borderColor);
}

void Surface::fill(unsigned int color)
{
    SDL_FillRect(_surface, NULL, color);
}

void Surface::border(unsigned int color)
{
    _borderColor = color;
    _lock();
    unsigned int * pixels = (unsigned int *) _surface->pixels;
    for (int y = 0; y < getHeight(); y++)
    {
        pixels[(y * _surface->w)] = color;
        pixels[(y * _surface->w) + _surface->w - 1] = color;
    }
    for (int x = 0; x < getWidth(); x++)
    {
        pixels[1 + x] = color;
        pixels[_surface->w * (_surface->h - 1) + x] = color;
    }
    _unlock();

}

Surface * Surface::crop(int xOffset, int yOffset, int width, int height)
{
    if (width == 0) width = getWidth() - xOffset;
    if (height == 0) height = getHeight() - yOffset;

    Surface * surface = new Surface(width, height);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            surface->setPixel(x, y, this->getPixel(x + xOffset, y + yOffset));
        }
    }
    return surface;
}

void Surface::blit(Surface * surface)
{
    SDL_Rect dest;
    dest.x = _x;
    dest.y = _y;
    SDL_BlitSurface(getSurface(), NULL, surface->getSurface(), &dest);
}

void Surface::copyTo(Surface * surface)
{
    _lock();
    unsigned int * thisPixels = (unsigned int *) _surface->pixels;
    unsigned int * thatPixels = (unsigned int *) surface->_surface->pixels;
    for (int y = 0; y < getHeight(); y++)
    {
        for (int x = 0; x < getWidth(); x++)
        {
            thatPixels[((y + _y) * surface->_surface->w) + x + _x] = thisPixels[(y * _surface->w) + x];
        }
    }
    _unlock();
}

unsigned int Surface::getPixel(int x, int y)
{
    _lock();
    if (x < 0 || y < 0) return 0;
    if (x > getWidth() || y > getHeight()) return 0;
    if (getWidth()*getHeight() == 0) return 0;

    unsigned int * pixels = (unsigned int *) _surface->pixels;
    unsigned int color = pixels[(y * _surface->w) + x];
    _unlock();
    return color;
}

void Surface::setPixel(int x, int y, unsigned int color)
{
    _lock();
    if (x < 0 || y < 0) return;
    if (x > getWidth() || y > getHeight()) return;

    unsigned int * pixels = (unsigned int *) _surface->pixels;
    pixels[(y * _surface->w) + x] = color;
    _unlock();
}

void Surface::_lock()
{
    if(SDL_MUSTLOCK(_surface)) SDL_LockSurface(_surface);
}

void Surface::_unlock()
{
    if(SDL_MUSTLOCK(_surface)) SDL_UnlockSurface(_surface);
}

void Surface::loadFromSurface(Surface * surface)
{
    SDL_FreeSurface(_surface);
    _surface = surface->getSurface();
    _x = surface->getX();
    _y = surface->getY();
}

}