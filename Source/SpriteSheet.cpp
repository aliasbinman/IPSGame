#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include"SpriteSheet.h"

Image::Image()
{
	W = H	 = 0;
	pPixData = 0;
}

Image::~Image()
{
}


