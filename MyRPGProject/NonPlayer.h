#pragma once
#include "Actor.h"

class NonPlayer : public Actor
{
public:
	NonPlayer(std::string name, int health, SDL_Rect rect) :
		Actor(name, health, rect){};

	~NonPlayer();
};

