#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <Windows.h>
#include "SDL.h"
#include <string>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

// Screen
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BPP = 32;

// Main
const int POS_X_START_MAIN = 100;
const int POS_Y_START_MAIN = 200;
const int SPEED_MAIN = 10;
const int SPEED_SHOOT_MAIN = 20;

// Enemy
const int SPEED_ENEMY = 5;
const int NUM_ENEMIES = 5;
const int SPEED_SHOOT_ENEMIES = 10;

static SDL_Surface* g_screen = NULL;
static SDL_Surface* g_background = NULL;
static SDL_Surface* g_menu_background = NULL;
static SDL_Event g_even;

static Mix_Chunk* g_sound_shoot[1];
static Mix_Chunk* g_sound_explosion[1];
static Mix_Chunk* g_sound_background[1];
static Mix_Chunk* g_sound_intro[1];

static TTF_Font* g_font_text = NULL;
static TTF_Font* g_font_menu = NULL;
static TTF_Font* g_font_gameOver = NULL;
static TTF_Font* g_font_retry_exit = NULL;

static char g_name_backgroud[]       =		{"img/background.png"};
static char g_name_main_char[]       =		{"img/combatAircraft.png"};
static char g_name_enemy[]           =		{"img/enemyAircraft.png"};
static char g_name_explosion[]       =		{"img/explosion.png"};
static char g_name_bullet[]			 =		{"img/bullet.png"};
static char g_name_menu_background[] =		{"img/background.png"};
static char g_name_audio_shoot[]     =		{"sound/shoot.wav"};
static char g_name_audio_exp[]       =		{"sound/explosion.wav"};
static char g_name_score[]			 =		{"font/Pixel-UniCode.ttf"};
static char g_name_menu[]            =		{"font/Pixel-UniCode.ttf"};
static char g_name_over[]            =		{"font/Pixel-UniCode.ttf"};
static char g_name_retry[]           =		{"font/Pixel-UniCode.ttf"};

namespace SDLCommonFunction{
	SDL_Surface* LoadImage(std::string file_path);
	SDL_Rect applySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void applySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y);
	void cleanUp();
	bool checkCollision(const SDL_Rect& object1, const SDL_Rect& object2);
	bool addEventListener(const int& x, const int& y, const SDL_Rect& rect);
	int menu(SDL_Surface* des, TTF_Font* font);
	void showGameOverText(SDL_Surface* des, TTF_Font* g_font_gameOver, TTF_Font* g_font_retry_exit);
	void cleanUp();
}

#endif