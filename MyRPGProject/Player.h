#pragma once
#include "Actor.h"

class Player : public Actor
{
public:
	Player(){};
	Player(std::string name, int health, SDL_Rect rect) :
		Actor(name, health, rect){};

	~Player();
};

