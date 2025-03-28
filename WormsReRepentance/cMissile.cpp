#include "cMissile.h"

cMissile::cMissile(float xPosition, float yPosition, float radius) : cPhysicsObject(xPosition, yPosition, radius) {
	missile.setSize(Vector2f(14.0f, 30.0f));
	missile.setOrigin(missile.getSize() / 2.0f);
	if (!texture.loadFromFile("materials\\polskieRevo.png")) {
	}
	missile.setTexture(&texture);
	nrgLoss = 0;
	nBounceBeforeDeath = 0;	
}

void cMissile::draw(RenderWindow& window) const {
	missile.setPosition(position);
	missile.setRotation((directionAngle * 180.0f / 3.14159f) - 90.0f);
	window.draw(missile);
}

int cMissile::bounceDeathAction() const {
	return 150;
}
