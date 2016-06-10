#include "GameManager.h"
#include "SDLInit.h"
#include "Player.h"
#include "NonPlayer.h"
#include "FoodObject.h"
#include <time.h>

extern SDL_Window* window;
extern SDL_Surface* gScreenSurface;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
static SDL_Event event;

Player player;
FoodObject food;

//player stuff
SDL_Surface* gPNGSurfaceGrass = NULL;
//SDL_Surface* gPNGSurfacePlayer = NULL;
//SDL_Surface* gPNGSurfacePlayerLeft = NULL;
//SDL_Surface* gPNGSurfacePlayerDown = NULL;
//SDL_Surface* gPNGSurfacePlayerRight = NULL;
//food
SDL_Surface* gPNGSurfaceFood = NULL;

static SDLInit sdlInit;
char* direction = "up";

bool GameManager::Init(){
	bool initSuccess = sdlInit.Setup() &&
		LoadMedia();

	return initSuccess;

}

bool GameManager::LoadMedia()
{
	//Loading success flag
	bool success = true;

	//TODO: move surfaces to individual entities

	////Load PNG surface
	//gPNGSurfaceGrass = sdlInit.loadSurface("grass.png");
	//if (gPNGSurfaceGrass == NULL)
	//{
	//	printf("Failed to load PNG image!\n");
	//	success = false;
	//}
	//gPNGSurfaceFood = sdlInit.loadSurface("food.png");
	//if (gPNGSurfaceFood == NULL)
	//{
	//	printf("Failed to load PNG image!\n");
	//	success = false;
	//}

	player.mTextureName = "player_right.png";
	sdlInit.LoadTexture(player);

	//gPNGSurfacePlayer = sdlInit.loadSurface("player_up.png"); //<------- TODO HAVE PLAYER FACE THE DIRECTION THEY ARE MOVING
	//if (gPNGSurfacePlayer == NULL)
	//{
	//	printf("Failed to load PNG image!\n");
	//	success = false;
	//}
	//gPNGSurfacePlayerLeft = sdlInit.loadSurface("player_left.png"); //<------- TODO HAVE PLAYER FACE THE DIRECTION THEY ARE MOVING
	//if (gPNGSurfacePlayerLeft == NULL)
	//{
	//	printf("Failed to load PNG image!\n");
	//	success = false;
	//}
	//gPNGSurfacePlayerDown = sdlInit.loadSurface("player_down.png"); //<------- TODO HAVE PLAYER FACE THE DIRECTION THEY ARE MOVING
	//if (gPNGSurfacePlayerDown == NULL)
	//{
	//	printf("Failed to load PNG image!\n");
	//	success = false;
	//}
	//gPNGSurfacePlayerRight = sdlInit.loadSurface("player_right.png"); //<------- TODO HAVE PLAYER FACE THE DIRECTION THEY ARE MOVING
	//if (gPNGSurfacePlayerRight == NULL)
	//{
	//	printf("Failed to load PNG image!\n");
	//	success = false;
	//}

	//Seeding our rand...
	srand(time(0));

	

	//TODO: Move this to entity class (when we create entity)
	//rectFood.x = rand() % SCREEN_WIDTH + 1;	//randomize position...
	//rectFood.y = rand() % SCREEN_HEIGHT + 1;	//randomize position...
	//rectFood.w = 20;
	//rectFood.h = 20;

	return success;
}

void MovePlayer(SDL_Rect& PlayerRect){

	PlayerRect.x += horizAxis;
	PlayerRect.y += vertAxis;

	// moves player with arrow keys
	if (horizAxis < 0.0f) {
		direction = "left";
	}
	else if (horizAxis > 0.0f) {
		direction = "right";
	}
	else if (vertAxis > 0.0f) {
		direction = "down";
	}
	else if (vertAxis < 0.0f) {
		direction = "up";
	}
	
}


bool GameManager::Cleanup(){
	bool success = true;

	//if (!sdlInit.Cleanup(gPNGSurfaceGrass)){
	//	success = false;
	//}

	if (!sdlInit.Cleanup(player)){
		success = false;
	}

	/*if (!sdlInit.Cleanup(gPNGSurfaceFood)){
		success = false;
	}
*/
	if (!sdlInit.FinalCleanup()){
		success = false;
	}

	return success;
}

//TODO add delta time here
void GameManager::Draw(){
	sdlInit.Draw(player);

	//SDL_BlitSurface(gPNGSurfaceGrass, NULL, gScreenSurface, NULL); // code that displays grass

	//SDL_BlitSurface(gPNGSurfaceFood, NULL, gScreenSurface, &food.mRect); // code that displays food

	//if (direction == "up"){
	//	SDL_BlitSurface(gPNGSurfacePlayer, NULL, gScreenSurface, &player.mRect); // code that displays player
	//}
	//else if (direction == "left"){
	//	SDL_BlitSurface(gPNGSurfacePlayerLeft, NULL, gScreenSurface, &player.mRect); // code that displays player
	//}
	//else if (direction == "right"){
	//	SDL_BlitSurface(gPNGSurfacePlayerRight, NULL, gScreenSurface, &player.mRect); // code that displays player
	//}
	//else if (direction == "down"){
	//	SDL_BlitSurface(gPNGSurfacePlayerDown, NULL, gScreenSurface, &player.mRect); // code that displays player
	//}
}

void GameManager::Update(){
	sdlInit.Update();
	MovePlayer(player.mRect);
	food.Pickup(player);
}