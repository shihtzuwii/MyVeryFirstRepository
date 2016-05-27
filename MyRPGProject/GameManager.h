#pragma once
#include "SDLInit.h"

void MovePlayer(SDL_Rect& PlayerRect);
extern char* direction;

class GameManager{
public:
	bool Init();
	bool Cleanup();
	bool LoadMedia();

	void Draw();
	void Update();
	
};