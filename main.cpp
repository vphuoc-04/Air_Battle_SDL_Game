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
	int background_x = 0;
	bool isQuit = false;
	if(Init() == false){
		return 0;
	}
	g_background = SDLCommonFunction::LoadImage("img/Background.png");
	if(g_background == NULL){
		return 0;
	}

	MainObject mainChar;
	mainChar.SetRect(100, 200);
	bool setImgMainChar = mainChar.LoadImg("img/combatAircraft.png");
	while(!isQuit){
		while (SDL_PollEvent(&g_even)){
			if(g_even.type == SDL_QUIT){
				isQuit = true;
				break;
			}
			mainChar.handleInputAction(g_even);
		}
		background_x -= 2;
		SDLCommonFunction::applySurface(g_background, g_screen, background_x, 0);
		SDLCommonFunction::applySurface(g_background, g_screen, background_x + SCREEN_WIDTH, 0);
		if (background_x <= -SCREEN_WIDTH){
			background_x = 0;
		}

		mainChar.Show(g_screen);
		mainChar.handleMove();

		for (int i = 0; i < mainChar.getShootList().size(); i++){
			std::vector<Shoot*> shoot_list = mainChar.getShootList();
			Shoot* p_shoot = shoot_list.at(i);
			if(p_shoot != NULL){
				if(p_shoot->get_is_move()){
					p_shoot->Show(g_screen);
					p_shoot->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				}
				else{
					if(p_shoot != NULL){
						shoot_list.erase(shoot_list.begin() + i);
						mainChar.setShootList(shoot_list);

						delete p_shoot;
						p_shoot = NULL;
					}
				}
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