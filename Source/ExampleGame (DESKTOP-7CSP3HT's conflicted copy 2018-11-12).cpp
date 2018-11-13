// Game definition
#include "ExampleGame.h"
#include "SpriteSheet.h"
#include "Renderer.h"
#include <stdio.h>
#include <SDL_image.h>


SDL_Texture *mainTexture;


void LoadResources()
{


}








int ExampleGame::Init()
{
	// Load in a texture
	SDL_Surface *img = IMG_Load( "stones.png");
	   
	if( img == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", "stones.png", IMG_GetError() );
    }
	else
	{
		mainTexture = SDL_CreateTextureFromSurface( gSDL_Renderer, img );
        if( mainTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", "stones.png", SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( img );
	}

	return 1;
}

int ExampleGame::Shutdown()
{
	return 1;
}


void ExampleGame::Render()
{
	//Clear screen
    SDL_RenderClear( gSDL_Renderer );

    //Render texture to screen
 //   SDL_RenderCopy( gSDL_Renderer, mainTexture, NULL, NULL );

	        
//	SDL_Rect fillRect = { WINDOW_W / 4, WINDOW_H / 4, WINDOW_W / 2, WINDOW_H / 2 };
 //   SDL_SetRenderDrawColor( gSDL_Renderer, 0xFF, 0x00, 0x00, 0xFF );        
 //   SDL_RenderFillRect( gSDL_Renderer, &fillRect );

	SDL_Rect srcQuad = { 0,0,10,10 };
	SDL_Rect dstQuad = { 100,100,120,120 };
	SDL_Point CentreP = { 100,100 };
	SDL_RenderCopyEx( gSDL_Renderer, mainTexture, &srcQuad, &dstQuad, 30.0f, &CentreP, SDL_FLIP_NONE );


    //Update screen
    SDL_RenderPresent( gSDL_Renderer );



//	SDL_RenderCopyEx( gSDL_Renderer, mainTexture, clip, &renderQuad, angle, center, flip );


# if 0
	SDL_SetRenderDrawColor(gSDL_Renderer, 0, 0, 0, 0);
	SDL_RenderClear(gSDL_Renderer);

	// Draw Some pixels
	SDL_SetRenderDrawColor(gSDL_Renderer, 255, 0, 0, 255);

	SDL_RenderDrawPoint(gSDL_Renderer, 10,20);
	SDL_Rect rect;
	rect.x = 50+xx;
	rect.y = 60;
	rect.w = 360;
	rect.h = 260;
//	SDL_RenderDrawFilledRect(ren, &rect);

	xx++;
	if(xx > 400)
		xx = 0;

	for(int i=0; i<3000; i++)
	{
	//	SDL_RenderFillRect(ren, &rect);
	}



	SDL_Rect dstRect;
	dstRect.x = xx;
	dstRect.y = 0;
	dstRect.w = 100+xx;
	dstRect.h = 100;


//SDL_BlitScaled( mainImage, NULL, gSDL_ScreenSurface, &dstRect );

	SDL_Delay( 50 );

	//Update the surface
 //   SDL_UpdateWindowSurface( gSDL_Window );
	SDL_RenderPresent(gSDL_Renderer);

#endif


}

void ExampleGame::Update()
{


}