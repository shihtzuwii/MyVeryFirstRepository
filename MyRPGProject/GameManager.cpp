#include "GameManager.h"
#include "SDLInit.h"

extern SDL_Window* window;
extern SDL_Surface* gScreenSurface;

SDL_Surface* gPNGSurfaceGrass = NULL;
SDL_Surface* gPNGSurfacePlayer = NULL;

static SDLInit sdlInit;

bool GameManager::Init(){
	bool initSuccess = sdlInit.Setup() &&
		LoadMedia();

	return initSuccess;

}

bool GameManager::LoadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG surface
	gPNGSurfaceGrass = sdlInit.loadSurface("grass.png"); 
	if (gPNGSurfaceGrass == NULL)
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	gPNGSurfacePlayer = sdlInit.loadSurface("player_up.png"); //<------- TODO MOVE THE CHARACTER WITH ARROWKEYS
	if (gPNGSurfacePlayer == NULL)
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}

	return success;
}

bool GameManager::Cleanup(){
	bool success = true;

	if (!sdlInit.Cleanup(gPNGSurfaceGrass)){
		success = false;
	}

	if (!sdlInit.Cleanup(gPNGSurfacePlayer)){
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