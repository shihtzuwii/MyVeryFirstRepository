#pragma once

#include <string>
#include <SDL_image.h>

class Entity{
	
	public:
		Entity(){};
		Entity(SDL_Rect rect) : mRect(rect){};

	public:
		SDL_Rect mRect;
};