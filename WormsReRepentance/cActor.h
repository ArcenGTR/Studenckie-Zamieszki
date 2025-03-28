#pragma once

#include "cPhysicsObject.h"

class cActor : public cPhysicsObject {
public:

	cActor(float xPosition = 0.0f, float yPosition = 0.0f, float radius = 32.0f);

	void draw(RenderWindow& window) const override;

	int bounceDeathAction() const override;

	void setGrave();

	void setTexture();

	float shootAngle = 0.0f;
	float fHealth = 100;
	bool bIsPlayable = true;
	int nTeam;

private:
	Texture graveTexture;
	Texture textureAGH;
	Texture textureTiger;
	mutable RectangleShape actor;
};