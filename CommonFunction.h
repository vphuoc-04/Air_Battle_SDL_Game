#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <Windows.h>
#include "SDL.h"
#include <string>
#include <SDL_image.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BPP = 32;
const int NUM_ENEMIES = 5;

static SDL_Surface* g_screen = NULL;
static SDL_Surface* g_background = NULL;
static SDL_Event g_even;

namespace SDLCommonFunction{
	SDL_Surface* LoadImage(std::string file_path);
	void applySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void cleanUp();
}

#endif