#include "GameManager.h"
#include "SDLInit.h"

#include <time.h>

extern SDL_Window* window;
extern SDL_Surface* gScreenSurface;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
static SDL_Event event;

SDL_Rect rectPlayer;
SDL_Rect rectFood;

<<<<<<< HEAD
//player stuff
SDL_Surface* gPNGSurfaceGrass = NULL;
SDL_Surface* gPNGSurfacePlayer = NULL;
SDL_Surface* gPNGSurfacePlayerLeft = NULL;
SDL_Surface* gPNGSurfacePlayerDown = NULL;
SDL_Surface* gPNGSurfacePlayerRight = NULL;
//food
SDL_Surface* gPNGSurfaceFood = NULL;
=======
SDL_Surface* gPNGSurfaceGrass = NULL;
SDL_Surface* gPNGSurfacePlayer = NULL;
>>>>>>> 24f2b58292516d8721c8c215377848f2341b970f

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
	
	//Entity grass;
	//SDL_Rect rectGrass(0, 0, 64, 64);
	//grass.load("grass.png", rectGrass);

	//TODO: move surfaces to individual entities

	//Load PNG surface
<<<<<<< HEAD
	gPNGSurfaceGrass = sdlInit.loadSurface("grass.png");
=======
	gPNGSurfaceGrass = sdlInit.loadSurface("grass.png"); 
>>>>>>> 24f2b58292516d8721c8c215377848f2341b970f
	if (gPNGSurfaceGrass == NULL)
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
<<<<<<< HEAD
	gPNGSurfaceFood = sdlInit.loadSurface("food.png");
	if (gPNGSurfaceFood == NULL)
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	gPNGSurfacePlayer = sdlInit.loadSurface("player_up.png"); //<------- TODO HAVE PLAYER FACE THE DIRECTION THEY ARE MOVING
	if (gPNGSurfacePlayer == NULL)
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	gPNGSurfacePlayerLeft = sdlInit.loadSurface("player_left.png"); //<------- TODO HAVE PLAYER FACE THE DIRECTION THEY ARE MOVING
	if (gPNGSurfacePlayerLeft == NULL)
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	gPNGSurfacePlayerDown = sdlInit.loadSurface("player_down.png"); //<------- TODO HAVE PLAYER FACE THE DIRECTION THEY ARE MOVING
	if (gPNGSurfacePlayerDown == NULL)
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	gPNGSurfacePlayerRight = sdlInit.loadSurface("player_right.png"); //<------- TODO HAVE PLAYER FACE THE DIRECTION THEY ARE MOVING
	if (gPNGSurfacePlayerRight == NULL)
=======
	gPNGSurfacePlayer = sdlInit.loadSurface("player_up.png"); //<------- TODO MOVE THE CHARACTER WITH ARROWKEYS
	if (gPNGSurfacePlayer == NULL)
>>>>>>> 24f2b58292516d8721c8c215377848f2341b970f
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}

	//Seeding our rand...
	srand(time(0));

	//TODO: Move this to entity class (when we create entity)
	rectFood.x = rand() % SCREEN_WIDTH + 1;	//randomize position...
	rectFood.y = rand() % SCREEN_HEIGHT + 1;	//randomize position...
	rectFood.w = 20;
	rectFood.h = 20;

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

	if (!sdlInit.Cleanup(gPNGSurfaceGrass)){
		success = false;
	}

	if (!sdlInit.Cleanup(gPNGSurfacePlayer)){
<<<<<<< HEAD
		success = false;
	}

	if (!sdlInit.Cleanup(gPNGSurfaceFood)){
=======
>>>>>>> 24f2b58292516d8721c8c215377848f2341b970f
		success = false;
	}

	if (!sdlInit.FinalCleanup()){
		success = false;
	}

	return success;
}

//TODO add delta time here
void GameManager::Draw(){
	SDL_BlitSurface(gPNGSurfaceGrass, NULL, gScreenSurface, NULL); // code that displays grass

	SDL_BlitSurface(gPNGSurfaceFood, NULL, gScreenSurface, &rectFood); // code that displays food

	if (direction == "up"){
		SDL_BlitSurface(gPNGSurfacePlayer, NULL, gScreenSurface, &rectPlayer); // code that displays player
	}
	else if (direction == "left"){
		SDL_BlitSurface(gPNGSurfacePlayerLeft, NULL, gScreenSurface, &rectPlayer); // code that displays player
	}
	else if (direction == "right"){
		SDL_BlitSurface(gPNGSurfacePlayerRight, NULL, gScreenSurface, &rectPlayer); // code that displays player
	}
	else if (direction == "down"){
		SDL_BlitSurface(gPNGSurfacePlayerDown, NULL, gScreenSurface, &rectPlayer); // code that displays player
	}
}

void GameManager::Update(){
	sdlInit.Update();
	MovePlayer(rectPlayer);
}