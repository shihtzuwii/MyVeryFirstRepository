#include "GameManager.h"
#include "SDLInit.h"

extern SDL_Window* window;
extern SDL_Surface* gScreenSurface;

SDL_Surface* gPNGSurface = NULL;

static SDLInit sdlInit;

bool GameManager::Init(){
	bool initSuccess = sdlInit.Setup();

	return initSuccess;

}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG surface
	gPNGSurface = sdlInit.loadSurface("loaded.png"); //<-- current program isn't showing image, where should it go in the files?
	if (gPNGSurface == NULL)
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}

	return success;
}

bool GameManager::Cleanup(){
	bool success = true;

	if (!sdlInit.Cleanup(gPNGSurface)){
		success = false;
	}

	if (!sdlInit.FinalCleanup()){
		success = false;
	}

	return success;
}

//TODO add delta time here
void GameManager::Update(){
	sdlInit.Update();
}