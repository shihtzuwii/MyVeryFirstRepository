#pragma once

#include <string>
#include <SDL_image.h>

class Entity{
	
	public:
		Entity(){};
		Entity(SDL_Rect rect) : mRect(rect){};

	public:
		float mXPos = 0;
		float mYPos = 0;
		int mWidth = 0;
		int mHeight = 0;
		SDL_Rect mRect;
		SDL_Texture* mTexture = NULL;
		char* mTextureName = "";
};