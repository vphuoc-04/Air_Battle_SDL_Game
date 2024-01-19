#include "CommonFunction.h"
#include "MainObject.h"
#include "Enemy.h"

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
	bool setImg = true;
	if(Init() == false){
		return 0;
	}
	g_background = SDLCommonFunction::LoadImage("img/Background.png");
	if(g_background == NULL){
		return 0;
	}

	MainObject mainChar;
	mainChar.SetRect(100, 200);
	setImg = mainChar.LoadImg("img/combatAircraft.png");
		if(!setImg){
		return 0;
	}
	Enemy* p_enemies = new Enemy[NUM_ENEMIES];
	for (int enemy = 0; enemy < NUM_ENEMIES; enemy++){
		Enemy* p_enemy = (p_enemies + enemy);
		if(p_enemy){
			setImg = p_enemy->LoadImg("img/enemyAircraft.png");
			if (setImg == false){
				return 0;
			}

			int random_y = rand() % 800;
			if(random_y > SCREEN_HEIGHT - 150){
				random_y = SCREEN_HEIGHT * 0.5;
			}

			p_enemy->SetRect(SCREEN_WIDTH + enemy*1000, random_y);
			p_enemy->set_x_val(5);

			Shoot* p_shoot = new Shoot();
			p_enemy->ActionEnemy(p_shoot);
		}
	}
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
		for (int manyEnemies = 0; manyEnemies < NUM_ENEMIES; manyEnemies++){
			Enemy* p_enemy = (p_enemies + manyEnemies);
			if(p_enemy){
				p_enemy->Show(g_screen);
				p_enemy->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_enemy->ShootEnemy(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
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