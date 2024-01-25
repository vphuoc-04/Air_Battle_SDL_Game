#include "CommonFunction.h"
#include "TextObject.h"
#include "MainObject.h"
#include "Enemy.h"

bool SDLCommonFunction::addEventListener(const int& x, const int& y, const SDL_Rect& rect){
	if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h){
		return true;
	}
	return false;
}

int SDLCommonFunction::menu(SDL_Surface* des, TTF_Font* font){
	g_menu_background = LoadImage(g_name_menu_background);
	if(g_menu_background == NULL){
		return 1;
	}
	const int menuChoose = 2;
	SDL_Rect pos_arr[menuChoose];
	pos_arr[0].x = 385;
	pos_arr[0].y = 450;

	pos_arr[1].x = 800;
	pos_arr[1].y = 450;

	TextObject textMenu[menuChoose];
	textMenu[0].SetText("PLAY");
	textMenu[0].SetColor(TextObject::WHITE_TEXT);
	textMenu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

	textMenu[1].SetText("EXIT");
	textMenu[1].SetColor(TextObject::WHITE_TEXT);
	textMenu[1].SetRect(pos_arr[1].x, pos_arr[1].y);

	bool selected[menuChoose] = {0, 0};

	int x_mouse = 0;
	int y_mouse = 0;

	SDL_Event m_event;
	while(true){
		SDLCommonFunction::applySurface(g_menu_background, des, 0, 0);
		for(int i = 0; i < menuChoose; i++){
			textMenu[i].CreateText(font, des);
		}
		while(SDL_PollEvent(&m_event)){
			switch (m_event.type){
				case SDL_QUIT:
					return 1;
				case SDL_MOUSEMOTION:{
					x_mouse = m_event.motion.x;
					y_mouse = m_event.motion.y;

					for(int i = 0; i < menuChoose; i++){
						if(addEventListener(x_mouse, y_mouse, textMenu[i].GetRect())){
							if(selected[i] == false){
								selected[i] = 1;
								textMenu[i].SetColor(TextObject::BLACK_TEXT);
							}
						}
						else{
							if(selected[i] == true){
								selected[i] = 0;
								textMenu[i].SetColor(TextObject::WHITE_TEXT);
							}
						}
					}
				}
				break;
				case SDL_MOUSEBUTTONDOWN:{
					x_mouse = m_event.button.x;
					y_mouse = m_event.button.y;
					for(int i = 0; i < menuChoose; i++){
						if(addEventListener(x_mouse, y_mouse, textMenu[i].GetRect())){
							return i;
						}
					}
				}
				break;
				case SDL_KEYDOWN:
					if(m_event.key.keysym.sym == SDLK_ESCAPE){
						return 1;
					}
			default:
				break;
			}
		}
		SDL_Flip(des);
	}
	return 1;
}
void SDLCommonFunction::showGameOverText(SDL_Surface* des, TTF_Font* g_font_gameOver, TTF_Font* g_font_retry_exit){
	int score_value = 0;
	bool setImg = true;
	bool is_retry_pressed = false;
	bool is_exit_pressed = false;

    TextObject gameOverText;
    TextObject retryText;

    gameOverText.SetText("GAME OVER!");
    gameOverText.SetColor(TextObject::BLACK_TEXT);
    gameOverText.SetRect(500, 300);
    gameOverText.CreateText(g_font_gameOver, des);

    retryText.SetText("Press R to retry or press E to exit!");
    retryText.SetColor(TextObject::WHITE_TEXT);
    retryText.SetRect(455, 650);
    retryText.CreateText(g_font_retry_exit, des);

    SDL_Flip(des);
}

SDL_Surface* SDLCommonFunction::LoadImage(std::string file_path){
	SDL_Surface* load_image = NULL;
	SDL_Surface* optimize_image = NULL;

	load_image = IMG_Load(file_path.c_str());
	if(load_image != NULL){
		optimize_image = SDL_DisplayFormat(load_image);
		SDL_FreeSurface(load_image);
	}

	if (optimize_image != NULL) {
	    UINT32 color_key = SDL_MapRGB(optimize_image->format, 0, 0xFF, 0xFF);
	    SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
	}
	return optimize_image;
}

SDL_Rect SDLCommonFunction::applySurface(SDL_Surface* src, SDL_Surface* des, int x, int y){
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, des, &offset);

	return offset;
}

void SDLCommonFunction::applySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y){
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, clip, des, &offset);
}

bool SDLCommonFunction::checkCollision(const SDL_Rect& object1, const SDL_Rect& object2){
	int left_a = object1.x;
	int right_a = object1.x + object1.w;
	int top_a = object1.y;
	int bottom_a = object1.y + object1.h;

	int left_b = object2.x;
	int right_b = object2.x + object2.w;
	int top_b = object2.y;
	int bottom_b = object2.y + object2.h;

	bool horizontal_overlap = (left_a < right_b) && (right_a > left_b);
    bool vertical_overlap = (top_a < bottom_b) && (bottom_a > top_b);

    return horizontal_overlap && vertical_overlap;
}

void SDLCommonFunction::cleanUp(){
	SDL_Surface* g_screen;
	SDL_Surface* g_background;
}