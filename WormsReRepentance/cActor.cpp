#include "cActor.h"

cActor::cActor(float xPosition, float yPosition, float radius) : cPhysicsObject(xPosition, yPosition, radius) {
	if (!textureAGH.loadFromFile("materials\\aghowiec.png") || !textureTiger.loadFromFile("materials\\tiger.png")) {
		actor.setSize(Vector2f(28.0f, 64.0f));
		actor.setOrigin(actor.getSize() / 2.0f);
		actor.setFillColor(Color::Magenta);
	}
	else {
		actor.setSize(Vector2f(28.0f, 64.0f));
		actor.setOrigin(actor.getSize() / 2.0f);

	}
	nrgLoss = 0.2;
	nBounceBeforeDeath = -1;
}

void cActor::draw(RenderWindow& window) const {
	actor.setPosition(position);
	window.draw(actor);
}

int cActor::bounceDeathAction() const {
	return 0;
}

void cActor::setGrave() {
	if (!graveTexture.loadFromFile("materials\\graveTexture.png")) {
	}
	actor.setTexture(&graveTexture);
}

void cActor::setTexture()
{
	if (this->nTeam == 0) {
		actor.setTexture(&textureAGH);
	}
	else {
		actor.setTexture(&textureTiger);
	}
}