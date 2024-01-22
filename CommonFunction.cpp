#include "CommonFunction.h"

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