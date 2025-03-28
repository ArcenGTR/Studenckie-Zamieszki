#pragma once

#include <SFML/Graphics.hpp>


using namespace sf;

class cPhysicsObject {
public:

	cPhysicsObject(float xPosition = 0.0f, float yPosition = 0.0f, float radius = 5.0f);

    virtual void draw(RenderWindow& window) const = 0; //virtual function for drawing object

	virtual int bounceDeathAction() const = 0;

	virtual ~cPhysicsObject() = default;

	Vector2f position;
	Vector2f velocity;
	Vector2f acceleration;
	float directionAngle;

	float nrgLoss = 0.8f;
	int nBounceBeforeDeath = -1; //means inf many times
	bool bDead = false;

	float radius;
	bool bStable = false; // var for saying is object stable(not moving)

};