#pragma once

#include "cPhysicsObject.h"

class cDebris : public cPhysicsObject {
public:

	cDebris(float xPosition = 0.0f, float yPosition = 0.0f, float radius = 4.0f);

	cDebris(float xPosition = 0.0f, float yPosition = 0.0f, Color color = Color::Green, float radius = 4.0f);

	void draw(RenderWindow& window) const override;

	int bounceDeathAction() const override;

private:

	mutable RectangleShape debris;
};