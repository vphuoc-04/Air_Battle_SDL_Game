#include "Shoot.h"

Shoot::Shoot(){
	rect_.x = 0;
	rect_.y = 0;
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;
	shoot_type_ = NONE;
}

Shoot::~Shoot(){}

void Shoot::handleMove(const int& x_border, const int& y_border){
	if (is_move_ == true){
		rect_.x += 20;
	}

    if (rect_.x > x_border){
      is_move_ = false;
    }
}

void Shoot::handleInputAction(SDL_Event events){}