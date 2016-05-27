#include "GameManager.h"
extern bool sdlQuit;

int main(int argc, char* args[])
{
	GameManager gameManager;

	if (gameManager.Init()){

		/* Loop until an SDL_QUIT event is found */
		while (!sdlQuit){
			gameManager.Draw();
			gameManager.Update();
		}
	}

	return 0;
}