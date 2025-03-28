#pragma once

#include "cPhysicsObject.h"

class cMissile : public cPhysicsObject {
public:

	cMissile(float xPosition = 0.0f, float yPosition = 0.0f, float radius = 15.0);

	void draw(RenderWindow& window) const override;

	int bounceDeathAction() const override;

private:
	Texture texture;
	mutable RectangleShape missile;	
};