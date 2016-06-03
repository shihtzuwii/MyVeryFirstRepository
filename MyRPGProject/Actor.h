#pragma once

#include "Entity.h"

class Actor : public Entity{

public:
	Actor(){};
	Actor(std::string name, int health, SDL_Rect rect) :
		mName(name), mHealth(health), Entity(rect){};

protected:
	std::string mName;
	int mHealth;
};