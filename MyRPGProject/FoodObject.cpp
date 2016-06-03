#include "FoodObject.h"

bool FoodObject::Pickup(Entity other){
	bool pickedUp = HasCollided(other);
	if (pickedUp){	//is true
		Respawn();
	}

	return pickedUp;
}

bool FoodObject::HasCollided(Entity other){
	bool hasCollided = true;

	                         //is the left or right side touching the object's left or right side
	bool collidesHorizontal = ((other.mRect.x < mRect.x + mRect.w) && (other.mRect.x + other.mRect.w > mRect.x));
							 //is the top or bottom side touching the object's top or bottom
	bool collidesVertical = ((other.mRect.y < mRect.y + mRect.h) && (other.mRect.y + other.mRect.h > mRect.y));

	hasCollided = collidesHorizontal && collidesVertical;

	return hasCollided;
}

void FoodObject::Respawn()
{
	mRect.x = rand() % 640 + 1;	//randomize position...
	mRect.y = rand() % 480 + 1;	//randomize position...
	mRect.w = 20;
	mRect.h = 20;
};
//bool SDLInit::Setup()