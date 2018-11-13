#pragma once
#include <SDL.h>

const int WINDOW_W		= 1024;
const int WINDOW_H		= 600;

const float WINDOW_Wf		= (float)WINDOW_W;
const float WINDOW_Hf		= (float)WINDOW_H;

const int PIXEL_ZOOM	= 2;

extern SDL_Window		*gSDL_Window;
extern SDL_Renderer		*gSDL_Renderer;
//extern SDL_Surface		*gSDL_ScreenSurface;

extern int CanvasByteSz ;
