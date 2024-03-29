#include "MainObject.h"

MainObject::MainObject(){
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;
	x_val_ = 0;
	y_val_ = 0;
}

MainObject::~MainObject(){}

void MainObject::handleInputAction(SDL_Event events, Mix_Chunk* shoot_sound[2]){
	if(events.type == SDL_KEYDOWN){
		switch (events.key.keysym.sym){
			case SDLK_a:
				x_val_ -= WIDTH_MAIN_OBJECT / 15;
				break;

			case SDLK_w:
				y_val_ -= HEIGHT_MAIN_OBJECT / 15;
				break;

			case SDLK_s:
				y_val_ += HEIGHT_MAIN_OBJECT / 15;
				break;

			case SDLK_d:
				x_val_ += WIDTH_MAIN_OBJECT / 15;
				break;

			default:
				break;
		}
	}
	
	else if(events.type == SDL_KEYUP){
		switch (events.key.keysym.sym){
			case SDLK_a:
				x_val_ += WIDTH_MAIN_OBJECT / 15;
				break;

			case SDLK_w:
				y_val_ += HEIGHT_MAIN_OBJECT / 15;
				break;

			case SDLK_s:
				y_val_ -= HEIGHT_MAIN_OBJECT / 15;
				break;

			case SDLK_d:
				x_val_ -= WIDTH_MAIN_OBJECT / 15;
				break;

			default:
				break;
		}
	}
	else if(events.type == SDL_MOUSEBUTTONDOWN){
		Shoot* p_shoot = new Shoot();
		if(events.button.button == SDL_BUTTON_LEFT){
			p_shoot->setWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_shoot->LoadImg(g_name_bullet);
			p_shoot->set_type(Shoot::SPHERE);
			Mix_PlayChannel(-1, shoot_sound[0], 0);
		}
		p_shoot->SetRect(this->rect_.x + 100, this->rect_.y + 30);
		p_shoot->set_is_move(true);
		p_shoot_list_.push_back(p_shoot);
		p_shoot->set_x_val(SPEED_SHOOT_MAIN);
	}
	else if(events.type == SDL_MOUSEBUTTONUP){

	}
	if(replaying_){
		return;
	}
}

void MainObject::makeShootOfMain(SDL_Surface* des){
	for (int i = 0; i < p_shoot_list_.size(); i++){
		Shoot* p_shoot = p_shoot_list_.at(i);
		if(p_shoot != NULL){
			if(p_shoot->get_is_move()){
				p_shoot->Show(des);
				p_shoot->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
			}
			else{
				if(p_shoot != NULL){
					p_shoot_list_.erase(p_shoot_list_.begin() + i);
					delete p_shoot;
					p_shoot = NULL;
				}
			}
		}
	}
}

void MainObject::extermination(const int& mainCharDie){
	for(int i = 0; i < p_shoot_list_.size(); i++){
		if(mainCharDie < p_shoot_list_.size()){
			Shoot* p_shoot = p_shoot_list_.at(mainCharDie);
			p_shoot_list_.erase(p_shoot_list_.begin() + mainCharDie);
			if (p_shoot != NULL){
				delete p_shoot;
				p_shoot = NULL;
			}
		}
	}
}

void MainObject::handleMove(){
	rect_.x += x_val_;
	if(rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH){
		rect_.x -= x_val_;
	}

	rect_.y += y_val_;
	if(rect_.y < 0 || rect_.y + (HEIGHT_MAIN_OBJECT + 110) > SCREEN_HEIGHT){
		rect_.y -= y_val_;
	}
}

void MainObject::setReplaying(bool replaying) {
    replaying_ = replaying;
    if (replaying) {
        x_val_ = 0;
        y_val_ = 0;
    }
}


