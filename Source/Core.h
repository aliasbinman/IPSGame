#pragma once
#include <SDL.h>

const int WINDOW_W		= 1024;
const int WINDOW_H		= 600;

const float WINDOW_Wf		= (float)WINDOW_W;
const float WINDOW_Hf		= (float)WINDOW_H;

extern SDL_Window		*gSDL_Window;
extern SDL_Renderer		*gSDL_Renderer;

struct Vec2
{
	Vec2() { x = 0.0f; y = 0.0f;}
	Vec2(float _x, float _y) { x = _x; y = _y;}

	float x,y;

	Vec2 operator*(float v);			//multiplication
	Vec2 &operator*=(float v);			//multiplication
	Vec2 &operator+=(const Vec2 &vec);  ////assigning new result to the vector
	Vec2 &operator-=(const Vec2 &vec);  ////assigning new result to the vector
};

const float PI = 3.1415926535897932384626433f;
inline float DEG2RAD(float x) { return x*PI/180.0f; }
