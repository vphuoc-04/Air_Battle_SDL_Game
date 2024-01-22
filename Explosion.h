#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "BaseObject.h"
#include "CommonFunction.h"

const int EXP_WIDTH = 250;
const int EXP_HEIGHT = 250;

class Explosion : public BaseObject{
	public:
		Explosion();
		~Explosion();
		void set_clip();
		void set_frame(const int& fr){
			frame = fr;
		}
		void ShowEX(SDL_Surface* des);

	private:
		int frame;
		SDL_Rect clip_[4];
};

#endif