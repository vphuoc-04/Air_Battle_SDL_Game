#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include "CommonFunction.h"
#include "BaseObject.h"
#include "Shoot.h"
#include "Enemy.h"
#include "Explosion.h"
#include <vector>

#define WIDTH_MAIN_OBJECT 100
#define HEIGHT_MAIN_OBJECT 50

class MainObject : public BaseObject{
	public:
		MainObject();
		~MainObject();
		void handleInputAction(SDL_Event events, Mix_Chunk* shoot_sound[2]);
		void handleMove();
		void setShootList(std::vector<Shoot*> shoot_list){
			p_shoot_list_ = shoot_list;
		}
		std::vector<Shoot*> getShootList() const{
			return p_shoot_list_;
		}
		void extermination(const int& extermination);
		void reset(){
			SetRect(POS_X_START_MAIN, POS_Y_START_MAIN);
			 x_val_ = 0;
			 y_val_ = 0;
		}
		void makeShootOfMain(SDL_Surface* des);
		void SetX(int x) {
			rect_.x = x;
		}

		void SetY(int y) {
			rect_.y = y;
		}
		void setReplaying(bool replaying);

	private:
		int x_val_;
		int y_val_;
		bool replaying_;
		std::vector<Shoot*> p_shoot_list_;
};

#endif