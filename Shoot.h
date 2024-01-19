#ifndef SHOOT_H
#define SHOOT_H

#include "BaseObject.h"

#define WIDTH_SPHERE 10
#define HEIGHT_SPHERE 10

class Shoot: public BaseObject{
	public:
		enum ShootType{
			NONE = 0,
			SPHERE = 1
		};
		Shoot();
		~Shoot();
		void handleInputAction(SDL_Event events);
		void handleMove(const int& x_border, const int& y_border);
		void handleMoveRightToLeft();
		int get_type() const {
			return shoot_type_;
		}
		void set_type(const int& type) {
			shoot_type_ = type;
		}
		bool get_is_move() const {
			return is_move_;
		}
		void set_is_move(bool is_move){
			is_move_ = is_move;
		}
		void setWidthHeight(const int& widht, const int& height){
			rect_.w = widht; 
			rect_.h = height;
		};

	private:
		int x_val_;
		int y_val_;
		bool is_move_;
		int shoot_type_;
};

#endif