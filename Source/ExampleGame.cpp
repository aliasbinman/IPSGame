// Game definition
#include "ExampleGame.h"
#include "SpriteSheet.h"
#include "Core.h"
#include <stdio.h>
#include <SDL_image.h>

// These are some constants we use to control the boat movement - Modify them to change how the boat behaves
const float SPIN_SPEED   = 3.0f;	// How fast the boat turn in degrees per tick (a tick is 1/60th sec)
const float ACCELERATION = 0.1f;	// How much the boat accelerates
const float DRAG         = 0.01f;   // How much drag is applied to the boat per tick


SDL_Texture *BoatTexture;			// This hold an image of the boat


const float ArenaX_Min =    0.0f;	// How big the Arena is in the X,Y plane. This is used to draw the grid of wires.
const float ArenaX_Max =  4000.0f;
const float ArenaY_Min =    0.0f;
const float ArenaY_Max =  4000.0f;

// This stores the details on the boat
struct BoatEntity 
{
	Vec2 Pos;			// It's position in the X,Y plane
	Vec2 Veloc;			// It's Velocity in the X,Y plane (how much the Pos changes per tick)
	float Angle;		// The angle in degrees the boat is facing
	float Size;			// Its size in the world
};

// This class encapsulates a simple camera 
// The Camera has a position and a scale
// using this class a world position can be transformed into a screen position
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

// When constructor the camera is poiting at the origin with a typical Zoom
CameraType::CameraType()
{
	Pos  = { 0.0f, 0.0f};	
	Zoom = 3.0f;
}

// Given a position in the world transform to the screen
Vec2 CameraType::TransformToScreen(Vec2 P)
{
	Vec2 out;

	out.x = ((P.x - Pos.x) * Zoom) + (WINDOW_Wf/2.0f);
	out.y = ((P.y - Pos.y) * Zoom) + (WINDOW_Hf/2.0f);

	return out;
}

// Define a boat and a camera
BoatEntity	   PlayerBoat;
CameraType     Camera;

// Called once at the start 
// Loads an image of a boat from the GameData folder
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
	
	// Position the boat to be in the middle of the arena
	PlayerBoat.Pos.x = (ArenaX_Max+ArenaX_Min) / 2.0f;
	PlayerBoat.Pos.y = (ArenaY_Max+ArenaY_Min) / 2.0f;
	PlayerBoat.Angle =  0.0f;
	PlayerBoat.Size  = 10.0f;
	return 1;
}

int ExampleGame::Shutdown()
{
	SDL_DestroyTexture( BoatTexture );
	return 1;
}




// This function will draw the grid of horizontal and vertical lines to make up the world.
void RenderWorld()
{
	// Set Drawing Color to mid grey. The four numbers are Red,Green,Blue and Opacity. Numbers go from 0 to 255
	SDL_SetRenderDrawColor(gSDL_Renderer, 127,127,127,255);

	const int NumGrids = 50;// How many lines to draw per axis
	
	// Horizontal Lines
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

	// Vertical Lines
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

// This function draws the world and all enitites (boat)
void ExampleGame::Render()
{
	//Clear screen
	SDL_SetRenderDrawColor(gSDL_Renderer, 0,0,0,0);	// Set clear color to black
    SDL_RenderClear( gSDL_Renderer );				// Clear the screen

	// Render the grid 
	RenderWorld();

	// Render the player boat
	// https://wiki.libsdl.org/SDL_RenderCopyEx for info on the SDL call
	Vec2 Centre = Camera.TransformToScreen( PlayerBoat.Pos);
	float Scale = Camera.ZoomPoint( PlayerBoat.Size);
	SDL_Rect srcQuad =  { 0,0,256, 256 };
	SDL_Rect dstQuad =  { int(Centre.x - Scale),  int(Centre.y - Scale),  int(Scale*2.0f),  int(Scale*2.0f)};
	SDL_Point CentreP = { int(Scale), int(Scale)};
	SDL_RenderCopyEx( gSDL_Renderer, BoatTexture, &srcQuad, &dstQuad, PlayerBoat.Angle, &CentreP, SDL_FLIP_NONE );

    //Update screen
    SDL_RenderPresent( gSDL_Renderer );
}

// This function is called once every tick (1/60th sec)
// In it we will process input and update all objects in the world.
// We currently have a boat and a camera that follows the boat around
void ExampleGame::Update()
{
	// Get the keystates
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

	// Given the angle in degrees we need to get a 2D vector of where it is pointing in the 2D plane
	// Using Trigonometry of a right hand triangle we can work this out from the angle.
	// The Sin and Cos functons require angles in Radians so we need to convert from degrees to radians first
	Vec2  VecBoat = Vec2( cosf(DEG2RAD(PlayerBoat.Angle)), sinf(DEG2RAD(PlayerBoat.Angle)) );
    
	// If the UP key is pressed adjust the velocity of the boat in the direction the boat is currently facing
	if( currentKeyStates[ SDL_SCANCODE_UP ] )
    {
        PlayerBoat.Veloc += VecBoat * ACCELERATION;
    }

	// If the DOWN key is pressed adjust the velocity of the boat in the OPPOSITE direction the boat is currently facing
	if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
    {
        PlayerBoat.Veloc -= VecBoat * ACCELERATION;
    }

	// If the LEFT key is pressed decrease the angle of the boat 
	if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
    {
        PlayerBoat.Angle -= SPIN_SPEED;
    }

	// If the RIGHT key is pressed increase the angle of the boat 
	if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
    {
        PlayerBoat.Angle += SPIN_SPEED;
    }

	// Update the position based on the Velocity
	PlayerBoat.Pos += PlayerBoat.Veloc;

	// Apply drag to the velocity so it reduces every tick
	// At some point the drag will balance and equal the change velocity so the boat will move at a constant speed
	PlayerBoat.Veloc *= 1.0f-DRAG;

	// Set the camera so its looking at the boat
	Camera.SetPos(PlayerBoat.Pos);
}

