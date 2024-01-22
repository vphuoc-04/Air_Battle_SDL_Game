#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "BaseObject.h"
#include <string>
#include <SDL_ttf.h>

class TextObject : public BaseObject{
	public:
		enum textColor{
			WHITE_TEXT = 0,
			RED_TEXT = 1,
		};

		TextObject();
		~TextObject();

		void SetText(const std::string& text){
			str_val_ = text;
		}
		void SetColor(const int& t);
		void CreateText(TTF_Font* font, SDL_Surface* des);

	private:
		std::string str_val_;
		SDL_Color text_color_;
};

#endif