#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H
#include "CommonFunction.h"

class BaseObject
{
	public:
		BaseObject();
		~BaseObject();
		void Show(SDL_Surface* des);
		bool LoadImg(const char* file_name);

		void SetRect(const int& x, const int& y){
			rect_.x = x, rect_.y = y;
		}

		SDL_Rect GetRect() const{
			return rect_;
		}

		SDL_Surface* GetObject() const{
			return p_object_;
		}

	protected:
		SDL_Rect rect_;
		SDL_Surface* p_object_;
};

#endif 