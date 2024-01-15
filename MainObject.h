#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include "CommonFunction.h"
#include "BaseObject.h"

#define WIDTH_MAIN_OBJECT 100
#define HEIGHT_MAIN_OBJECT 50

class MainObject : public BaseObject{
	public:
		MainObject();
		~MainObject();
		void handleInputAction(SDL_Event events);
		void handleMove();

	private:
		int x_val_;
		int y_val_;
};

#endif