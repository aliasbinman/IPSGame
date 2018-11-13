// Game definition
#include "ExampleGame.h"
#include "SpriteSheet.h"
#include "Core.h"
#include <stdio.h>
#include <SDL_image.h>

const float SPIN_SPEED   = 3.0f;
const float ACCELERATION = 0.1f;
const float DRAG         = 0.01f;


SDL_Texture *BoatTexture;

const float PI = 3.1415926535897932384626433f;
#define DEG2RAD(x) (x*PI/180.0f)

const float ArenaX_Min =    0.0f;
const float ArenaX_Max =  4000.0f;
const float ArenaY_Min =    0.0f;
const float ArenaY_Max =  4000.0f;


struct BoatEntity : public Entity
{
	float Angle;
	float Size;
};

// This class encapsulates a simple camera 
class CameraType
{
public:

	CameraType();
	Vec2	Pos;
	float	Zoom;

	Vec2	TransformToScreen(Vec2 P);
	float	ZoomPoint(float f) { return f*Zoom;}
	void 	SetPos(Vec2 P) { Pos = P;}
};

CameraType::CameraType()
{
	Pos  = { 0.0f, 0.f};	
	Zoom = 3.0f;
}


Vec2 CameraType::TransformToScreen(Vec2 P)
{
	Vec2 out;

	out.x = ((P.x - Pos.x) * Zoom) + (WINDOW_Wf/2.0f);
	out.y = ((P.y - Pos.y) * Zoom) + (WINDOW_Hf/2.0f);

	return out;
}


BoatEntity	   PlayerBoat;
CameraType     Camera;


void LoadResources()
{
	// Load in a texture
	SDL_Surface *img = IMG_Load( "boat.png");
	   
	if( img == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", "stones.png", IMG_GetError() );
    }
	else
	{
		BoatTexture = SDL_CreateTextureFromSurface( gSDL_Renderer, img );
        if( BoatTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", "stones.png", SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( img );
	}
}








int ExampleGame::Init()
{
	LoadResources();
	
	PlayerBoat.Pos.x = (ArenaX_Max+ArenaX_Min) / 2.0f;
	PlayerBoat.Pos.y = (ArenaY_Max+ArenaY_Min) / 2.0f;
	PlayerBoat.Angle =  0.0f;
	PlayerBoat.Size  = 10.0f;
	return 1;
}

int ExampleGame::Shutdown()
{
	return 1;
}





void RenderWorld()
{
	SDL_SetRenderDrawColor(gSDL_Renderer, 127,127,127,255);

	// Draw the Horizontal And verticl Grids that make up the arena
	const int NumGrids = 50;
	
	{
		float XStart = ArenaX_Min;
		float XEnd   = ArenaX_Max;
		float XDiff  = (XEnd- XStart) /  float(NumGrids);

		for(float x=XStart; x<=XEnd; x+= XDiff)
		{
			Vec2 p1 = Camera.TransformToScreen(Vec2(x,ArenaY_Min));
			Vec2 p2 = Camera.TransformToScreen(Vec2(x,ArenaY_Max));

			SDL_RenderDrawLine(gSDL_Renderer, int(p1.x), int(p1.y), int(p2.x), int(p2.y) );
		}
	}

	{
		float YStart = ArenaY_Min;
		float YEnd   = ArenaY_Max;
		float YDiff  = (YEnd- YStart) /  float(NumGrids);

		for(float y=YStart; y<=YEnd; y+= YDiff)
		{
			Vec2 p1 = Camera.TransformToScreen(Vec2(ArenaX_Min, y));
			Vec2 p2 = Camera.TransformToScreen(Vec2(ArenaX_Max, y));

			SDL_RenderDrawLine(gSDL_Renderer, int(p1.x), int(p1.y), int(p2.x), int(p2.y) );
		}
	}
}


void ExampleGame::Render()
{
	//Clear screen
	SDL_SetRenderDrawColor(gSDL_Renderer, 0,0,0,0);	// Set clear color to black
    SDL_RenderClear( gSDL_Renderer );

	// Render the grid 
	RenderWorld();

	// Render the player boat
	Vec2 Centre = Camera.TransformToScreen( PlayerBoat.Pos);
	float Scale = Camera.ZoomPoint( PlayerBoat.Size);
	SDL_Rect srcQuad =  { 0,0,256, 256 };
	SDL_Rect dstQuad =  { Centre.x - Scale, Centre.y - Scale, Scale*2.0f, Scale*2.0f};
	SDL_Point CentreP = { Scale, Scale};
	SDL_RenderCopyEx( gSDL_Renderer, BoatTexture, &srcQuad, &dstQuad, PlayerBoat.Angle, &CentreP, SDL_FLIP_NONE );

    //Update screen
    SDL_RenderPresent( gSDL_Renderer );
}

void ExampleGame::Update()
{
	// Update the boat
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

	float SinAng = sinf(DEG2RAD(PlayerBoat.Angle));
	float CosAng = cosf(DEG2RAD(PlayerBoat.Angle));
    
	if( currentKeyStates[ SDL_SCANCODE_UP ] )
    {
        PlayerBoat.Veloc += Vec2(CosAng,  SinAng )*ACCELERATION;
    }

	if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
    {
        PlayerBoat.Veloc -= Vec2(CosAng, SinAng)*ACCELERATION;
    }

	if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
    {
        PlayerBoat.Angle -= SPIN_SPEED;
    }

	if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
    {
        PlayerBoat.Angle += SPIN_SPEED;
    }

	// Update the position based on the Velocity
	PlayerBoat.Pos += PlayerBoat.Veloc;

	// Apply drag to the velocity
	PlayerBoat.Veloc *= 1.0f-DRAG;

	// Set the camera so its looking at the boat
	Camera.SetPos(PlayerBoat.Pos);
}


