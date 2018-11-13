#include <memory.h>
#include "Core.h"

SDL_Window		*gSDL_Window		= NULL;
SDL_Renderer	*gSDL_Renderer		= NULL;
SDL_Surface		*gSDL_ScreenSurface = NULL;

void CreateRenderer()
{
}

Vec2 &Vec2::operator+=(const Vec2 &vec)
{
    x+=vec.x;
    y+=vec.y;
    return *this;
}

Vec2 &Vec2::operator-=(const Vec2 &vec)
{
    x-=vec.x;
    y-=vec.y;
    return *this;
}

Vec2 &Vec2::operator*=(float value)
{
    x*=value;
    y*=value;
    return *this;
}

Vec2 Vec2::operator*(float value)
{
    return Vec2(x*value,y*value);
}
