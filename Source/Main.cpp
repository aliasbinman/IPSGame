// Main.CPP
//
// This is the main entrypoint to the program
// Here a window and SDL Renderer are created.
// The Games Init function is then called
//  It then goes into a loop which fill first call the games update function at a steady 60 FPS floowed by the Render Call

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "ExampleGame.h"
#include "CallumGame.h"
#include "Renderer.h"


// Comment out the define below to run Callum game
 #define EXAMPLEGAME 

ExampleGame exGame;
CallumGame  MainGame;
GameBase *pGame;

bool bQuit = false;
int CurrTime =0;
float LogicTime = 0.0f;


void Init()
{
#ifdef EXAMPLEGAME
	pGame = &exGame;
#else
	pGame = &MainGame;
#endif

	CurrTime = SDL_GetTicks();
	LogicTime = 0.0f;

	pGame->Init();
}

void Update()
{
	SDL_Event e;

	while( SDL_PollEvent( &e ) != 0 )
	{
		//User requests quit
		if( e.type == SDL_QUIT )
		{
			bQuit = true;
		}
	}

	int time = SDL_GetTicks();
	int TimeDelta = time - CurrTime;
	LogicTime += TimeDelta;
	CurrTime = time;

	while(LogicTime > 16.66666f)
	{
		LogicTime -= 16.66666f;
		// DO UPDATE
		pGame->Update();
	}
}


void Render()
{
	pGame->Render();
}

int main(int argc, char *args[])
{
    // Your code here

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	gSDL_Window = SDL_CreateWindow("Speedy Boatz", 100, 100, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
	if (gSDL_Window == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	gSDL_Renderer = SDL_CreateRenderer(gSDL_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (gSDL_Renderer == nullptr)
	{
		SDL_DestroyWindow(gSDL_Window);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	Init();

	while(bQuit == false)
	{
		Update();
		Render();
	}

	SDL_DestroyRenderer(gSDL_Renderer);
	SDL_DestroyWindow(gSDL_Window);
	SDL_Quit();

	return 0;
}


