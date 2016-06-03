#pragma once

#include "SDLInit.h"
#include "GameManager.h"
#include "Entity.h"

class FoodObject : public Entity{

public:
	bool Pickup(Entity other);

	bool HasCollided(Entity other);

	void Respawn();
	//rectFood.x = rand() % SCREEN_WIDTH + 1;	//randomize position...
	//rectFood.y = rand() % SCREEN_HEIGHT + 1;	//randomize position...
	//rectFood.w = 20;
	//rectFood.h = 20;
};