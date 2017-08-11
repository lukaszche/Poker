#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_functions.h"
#include <string>
class SDL_app
{
private:
	SDL_Surface *screen;
	SDL_Surface *loadTest;
public:
	SDL_app(void);
	~SDL_app(void);
	bool init();
	void flip();
};

