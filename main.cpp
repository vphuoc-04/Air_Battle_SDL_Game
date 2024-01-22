#include "CommonFunction.h"
#include "MainObject.h"
#include "Enemy.h"
#include "Explosion.h"
#include "TextObject.h"

TTF_Font* g_font_text = NULL;

bool Init(){
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
		return false;
	}

	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(g_screen == NULL){
		return false;
	}

	if(TTF_Init() == -1){
		return false;
	}

	g_font_text = TTF_OpenFont("font/Pixel-UniCode.ttf", 20);
	if(g_font_text == NULL){
		return false;
	}
	return true;
}

int main(int arc, char*argv[]){
	int background_x = 0;
	int score_value = 0;
	bool isQuit = false;
	bool setImg = true;
	if(Init() == false){
		return 0;
	}
	g_background = SDLCommonFunction::LoadImage("img/background.png");
	if(g_background == NULL){
		return 0;
	}

	// Make main character
	MainObject mainChar;
	mainChar.SetRect(100, 200);
	setImg = mainChar.LoadImg("img/combatAircraft.png");
		if(!setImg){
		return 0;
	}

	// Make explosion
	Explosion exp;
	setImg = exp.LoadImg("img/explosion.png");
	exp.set_clip();
	if(setImg == false){
		return 0;
	}

	// Text score
	TextObject score;
	score.SetColor(TextObject::WHITE_TEXT);

	// Text higgerScore
	/*TextObject higgerScore;
	higgerScore.setColor(TextObject::WHITE_TEXT);*/

	// Make enemy 
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

				//Check collision main and enemies
				bool is_collision = SDLCommonFunction::checkCollision(mainChar.GetRect(), p_enemy->GetRect());
				if(is_collision){
					for(int explosion = 0; explosion < 4; explosion++){
						int x_boom = (mainChar.GetRect().x + mainChar.GetRect().w * 0.5) - EXP_WIDTH * 0.3;
						int y_boom = (mainChar.GetRect().y + mainChar.GetRect().h * 0.5) - EXP_HEIGHT * 0.5;
						exp.set_frame(explosion);
						exp.SetRect(x_boom, y_boom);
						exp.ShowEX(g_screen);
						SDL_Delay(50);
						if(SDL_Flip(g_screen) == -1){
							return 0;
						}
					}
					if(MessageBox(NULL, L"GAME OVER!", L"THÔNG BÁO", MB_RETRYCANCEL) == IDRETRY){
						mainChar.reset();
						score_value = 0;
						for (int i = 0; i < NUM_ENEMIES; i++) {
							p_enemies[i].Reset(SCREEN_WIDTH + i * 1000); 
						}
						break;
					}
					else{
						delete [] p_enemies;
						SDLCommonFunction::cleanUp();
						SDL_Quit();
						return 0;
					}
				}

				//Check collision shoot of main to enemies
				std::vector<Shoot*> shoot_list = mainChar.getShootList();
				for(int mainCharShootToEnemies = 0; mainCharShootToEnemies < shoot_list.size(); mainCharShootToEnemies++){
					Shoot* p_shoot = shoot_list.at(mainCharShootToEnemies);
					if (p_shoot != NULL){
						bool ret_collision = SDLCommonFunction::checkCollision(p_shoot->GetRect(), p_enemy->GetRect());
							if(ret_collision){
								score_value++;
								for(int explosion = 0; explosion < 4; explosion++){
								int x_boom = (p_enemy->GetRect().x + p_enemy->GetRect().w * 0.5) - EXP_WIDTH * 0.5;
								int y_boom = (p_enemy->GetRect().y + p_enemy->GetRect().h * 0.5) - EXP_HEIGHT * 0.5;
								exp.set_frame(explosion);
								exp.SetRect(x_boom, y_boom);
								exp.ShowEX(g_screen);
								//SDL_Delay(20);
								if(SDL_Flip(g_screen) == -1){
									delete [] p_enemies;
									SDLCommonFunction::cleanUp();
									SDL_Quit();
									return 0;
								}
							}

							p_enemy->Reset(SCREEN_WIDTH + manyEnemies*1000);
							mainChar.extermination(mainCharShootToEnemies);
						}
					}
				}

				//Check collision shoot of enemies to main
				std::vector<Shoot*> enemy_Shoot_List = p_enemy->GetShootList();
				for (int enemiesShootToMainchar = 0; enemiesShootToMainchar < enemy_Shoot_List.size(); enemiesShootToMainchar++) {
					Shoot* p_shoot = enemy_Shoot_List.at(enemiesShootToMainchar);
					if (p_shoot != NULL) {
						bool ret_collision = SDLCommonFunction::checkCollision(p_shoot->GetRect(), mainChar.GetRect());
						if (ret_collision){
							for(int explosion = 0; explosion < 4; explosion++){
								int x_boom = (mainChar.GetRect().x + mainChar.GetRect().w * 0.5) - EXP_WIDTH * 0.5;
								int y_boom = (mainChar.GetRect().y + mainChar.GetRect().h * 0.5) - EXP_HEIGHT * 0.5;
								exp.set_frame(explosion);
								exp.SetRect(x_boom, y_boom);
								exp.ShowEX(g_screen);
								SDL_Delay(50);
								if(SDL_Flip(g_screen) == -1){
									return 0;
								}
							}
							if (MessageBox(NULL, L"GAME OVER!", L"THÔNG BÁO", MB_RETRYCANCEL) == IDRETRY) {
								mainChar.reset();
								score_value = 0;
								for (int i = 0; i < NUM_ENEMIES; i++) {
									p_enemies[i].Reset(SCREEN_WIDTH + i * 1000); 
								}
								break;
							}
							else{
								delete [] p_enemies;
								SDLCommonFunction::cleanUp();
								SDL_Quit();
								return 0;
							}
						}
					}
				}
			}
		}
		// Show score value of mainChar 
		std::string val_str_score = std::to_string(score_value);
		std::string strScore("Score:  ");
		strScore += val_str_score;

		score.SetText(strScore);
		score.SetRect(1100, 30);
		score.CreateText(g_font_text, g_screen);

		// Show higger score value of mainChar
		/*std::string strHiggerScore("Higger Score:  ");
		higgerScore.setText(strHiggerScore);
		higgerScore.setRect(1100, 10);
		higgerScore.createText(g_font_text, g_screen);*/

		// Update screen
		if(SDL_Flip(g_screen) == -1){
			delete [] p_enemies;
			SDLCommonFunction::cleanUp();
			SDL_Quit();
			return 0;
		}
	}
	return 0;
}