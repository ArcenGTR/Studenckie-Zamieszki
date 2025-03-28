#include "cPhysicsObject.h"
#include "Game.h"
#include <iostream>

cPhysicsObject::cPhysicsObject(float xPosition, float yPosition, float radius) {
	position.x = xPosition;
	position.y = yPosition;
	this->radius = radius;
}



