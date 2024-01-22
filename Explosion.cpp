#include "Explosion.h"

Explosion::Explosion(){}

Explosion::~Explosion(){}

void Explosion::set_clip(){
	clip_[0].x = 0;
	clip_[0].y = 0;
	clip_[0].w = EXP_WIDTH;
	clip_[0].h = EXP_HEIGHT;

	clip_[1].x = EXP_WIDTH;
	clip_[1].y = 0;
	clip_[1].w = EXP_WIDTH;
	clip_[1].h = EXP_HEIGHT;

	clip_[2].x = 2*EXP_WIDTH;
	clip_[2].y = 0;
	clip_[2].w = EXP_WIDTH;
	clip_[2].h = EXP_HEIGHT;

	clip_[3].x = 3*EXP_WIDTH;
	clip_[3].y = 0;
	clip_[3].w = EXP_WIDTH;
	clip_[3].h = EXP_HEIGHT;
}

void Explosion::ShowEX(SDL_Surface* des){
	if (frame >= 4){
		frame = 0;
	}
	SDLCommonFunction::applySurfaceClip(this->p_object_, des, &clip_[frame], rect_.x, rect_.y);
}