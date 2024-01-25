#include "CommonFunction.h"
#include "MainObject.h"
#include "Enemy.h"
#include "Explosion.h"
#include "TextObject.h"
#include <SDL_mixer.h>

bool Init(){
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {return false;}
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(g_screen == NULL){return false;}

	// Read WAV audio
	if(Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {return false;}
	g_sound_shoot[0] = Mix_LoadWAV(g_name_audio_shoot);
	g_sound_explosion[0] = Mix_LoadWAV(g_name_audio_exp);
	if(g_sound_explosion[0] == NULL || g_sound_shoot[0] == NULL) {return false;}

	// Get Font
	if(TTF_Init() == -1) {return false;}
	g_font_text = TTF_OpenFont(g_name_score, 20);
	g_font_menu = TTF_OpenFont(g_name_menu, 70);
	g_font_gameOver = TTF_OpenFont(g_name_over, 70);
	g_font_retry_exit = TTF_OpenFont(g_name_retry, 30);
	if(g_font_text == NULL) {return false;}

	return true;
}

int main(int arc, char*argv[]){
	int background_x = 0, score_value = 0;
	bool isQuit = false;
	bool setImg = true;
	bool gameOver = false;

	if(Init() == false) {return 0;}

	// Make background
	g_background = SDLCommonFunction::LoadImage(g_name_backgroud); if(g_background == NULL) {return 0;}

	// Make main character
	MainObject mainChar;
	mainChar.SetRect(POS_X_START_MAIN, POS_Y_START_MAIN);
	setImg = mainChar.LoadImg(g_name_main_char);
	if(!setImg) {return 0;}

	// Make explosion
	Explosion exp;
	setImg = exp.LoadImg(g_name_explosion);
	exp.set_clip();
	if(!setImg) {return 0;}

	// Text score
	TextObject score;
	score.SetColor(TextObject::WHITE_TEXT);

	// Make enemy
	Enemy* p_enemies = Enemy::InitEnemies();
    if (p_enemies == nullptr) {return 0;}

	int ret_menu = SDLCommonFunction::menu(g_screen, g_font_menu); if(ret_menu == 1) {isQuit = true;} 

	while(!isQuit){
		while (SDL_PollEvent(&g_even)){
			if(g_even.type == SDL_QUIT){
				isQuit = true;
				break;
			}
			mainChar.handleInputAction(g_even, g_sound_shoot);
		}

		// Moving background
		background_x -= 2;
		SDLCommonFunction::applySurface(g_background, g_screen, background_x, 0);
		SDLCommonFunction::applySurface(g_background, g_screen, background_x + SCREEN_WIDTH, 0);
		if (background_x <= -SCREEN_WIDTH) {background_x = 0;}

		mainChar.Show(g_screen);
		mainChar.handleMove();
		mainChar.makeShootOfMain(g_screen);

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
						if(SDL_Flip(g_screen) == -1) {return 0;}
						Mix_PlayChannel(-1, g_sound_explosion[0], 0);
					}
					while(!gameOver){
						SDLCommonFunction::showGameOverText(g_screen, g_font_gameOver, g_font_retry_exit);
						while(SDL_PollEvent(&g_even)){
							if(g_even.type == SDL_QUIT){
								isQuit = true;
							}
							else if(g_even.type == SDL_KEYDOWN ){
								switch(g_even.key.keysym.sym){
									case SDLK_r:
										mainChar.reset();
										score_value = 0;
										for(int i = 0; i < NUM_ENEMIES; i++){
											p_enemies[i].Reset(SCREEN_WIDTH + i * 1000); 
										}
										gameOver = true;
										mainChar.setReplaying(true);
										break;

									case SDLK_e:
										delete [] p_enemies;
										SDLCommonFunction::cleanUp();
										SDLCommonFunction::menu(g_screen, g_font_menu);
										SDL_Quit();
										return 0;
								}
							}
						}
						SDL_Flip(g_screen);
					}
					gameOver = false;
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
								if(SDL_Flip(g_screen) == -1){
									delete [] p_enemies;
									SDLCommonFunction::cleanUp();
									SDL_Quit();
									return 0;
								}
								Mix_PlayChannel(-1, g_sound_explosion[0], 0);
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
								if(SDL_Flip(g_screen) == -1) {return 0;}
								Mix_PlayChannel(-1, g_sound_explosion[0], 0);
							}
							while (!gameOver) {
								SDLCommonFunction::showGameOverText(g_screen, g_font_gameOver, g_font_retry_exit);
								while(SDL_PollEvent(&g_even)){
									if(g_even.type == SDL_QUIT){
										isQuit = true;
									}
									else if (g_even.type == SDL_KEYDOWN){
										switch (g_even.key.keysym.sym) {
											case SDLK_r:
												mainChar.reset();
												score_value = 0;
												for (int i = 0; i < NUM_ENEMIES; i++) {
													p_enemies[i].Reset(SCREEN_WIDTH + i * 1000); 
												}
												gameOver = true;
												mainChar.setReplaying(true);
												break;

											case SDLK_e:
												delete [] p_enemies;
												SDLCommonFunction::cleanUp();
												SDLCommonFunction::menu(g_screen, g_font_menu);
												SDL_Quit();
												return 0;
										}
									}
								}
								SDL_Flip(g_screen);
							}
							gameOver = false;
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
