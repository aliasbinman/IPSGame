#pragma once

struct Image
{
	int W,H, Pitch;
	unsigned char *pPixData;

	Image();
	~Image();
};


// A sprite is a rectangular sub image  

extern Image LoadImage(const char *filename);




