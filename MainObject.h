#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include "CommonFunction.h"
#include "BaseObject.h"
#include "Shoot.h"
#include <vector>

#define WIDTH_MAIN_OBJECT 100
#define HEIGHT_MAIN_OBJECT 50

class MainObject : public BaseObject{
	public:
		MainObject();
		~MainObject();
		void handleInputAction(SDL_Event events);
		void handleMove();
		void setShootList(std::vector<Shoot*> shoot_list){
			p_shoot_list_ = shoot_list;
		}
		std::vector<Shoot*> getShootList() const{
			return p_shoot_list_;
		}
		void extermination(const int& extermination);

		void reset(){
			SetRect(100, 200);
		}

	private:
		int x_val_;
		int y_val_;
		std::vector<Shoot*> p_shoot_list_;
};

#endif