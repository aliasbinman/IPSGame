// Game definition
#include "CallumGame.h"
#include "SpriteSheet.h"
#include "Core.h"
#include <stdio.h>
#include <SDL_image.h>


int CallumGame::Init()
{
	// Create all Data once here
	return 1;
}

int CallumGame::Shutdown()
{
	return 1;
}

void CallumGame::Render()
{
	//Clear screen
	SDL_SetRenderDrawColor(gSDL_Renderer, 0,0,0,0);	// Set clear color to black
    SDL_RenderClear( gSDL_Renderer );

	// Do adll drawing Here
    //Update screen
    SDL_RenderPresent( gSDL_Renderer );
}

void CallumGame::Update()
{
	// Key KeyStates
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

}


