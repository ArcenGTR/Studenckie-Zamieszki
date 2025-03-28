#pragma once

#include "cPhysicsObject.h"

class cDummy : public cPhysicsObject {
public:

	cDummy(float xPosition = 0.0f, float yPosition = 0.0f, float radius = 25.0);

	void draw(RenderWindow& window) const override;

	int bounceDeathAction() const override;

private:

	mutable CircleShape dummyCircle;
};