#pragma once

//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Entity.h"

extern float horizAxis;
extern float vertAxis;

class SDLInit{

public:
	bool Setup();
	bool FinalCleanup();
	bool Cleanup(Entity &entity);

	SDL_Surface* loadSurface(std::string path);
	void LoadTexture(Entity &entity);

	void Draw(Entity &entity);

	void Update();

};