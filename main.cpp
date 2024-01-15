#include "CommonFunction.h"
#include "MainObject.h"

bool Init(){
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
		return false;
	}

	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	if(g_screen == NULL){
		return false;
	}
	return true;
}

int main(int arc, char*argv[]){
	bool isQuit = false;

	if(Init() == false){
		return 0;
	}
	g_background = SDLCommonFunction::LoadImage("img/background.png");
	if(g_background == NULL){
		return 0;
	}

	SDLCommonFunction::applySurface(g_background, g_screen, 0, 0);
	MainObject mainChar;
	mainChar.SetRect(100, 200);
	bool setImgMainChar = mainChar.LoadImg("img/combatAircraft.png");

	if(!setImgMainChar){
		return 0;
	}

	mainChar.Show(g_screen);

	while (!isQuit){
		while (SDL_PollEvent(&g_even)){
			if(g_even.type == SDL_QUIT){
				isQuit = true;
				break;
			}
		}
		if(SDL_Flip(g_screen) == -1){
			return 0;
		}
	}
	SDLCommonFunction::cleanUp();
	SDL_Quit();

	return 0;
}