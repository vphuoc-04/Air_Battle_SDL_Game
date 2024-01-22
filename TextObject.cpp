#include "TextObject.h"

TextObject::TextObject(){}

TextObject::~TextObject(){}

void TextObject::SetColor(const int& type){
	if(type == WHITE_TEXT){
		SDL_Color color = {255, 255, 255};
		text_color_ = color;
	}
	if(type == RED_TEXT){
		SDL_Color color = {255, 0, 0};
		text_color_ = color;
	}
}

void TextObject::CreateText(TTF_Font* font, SDL_Surface* des){
	p_object_ = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_);
	Show(des);
}