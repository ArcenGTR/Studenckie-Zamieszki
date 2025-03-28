#include "cDebris.h"

cDebris::cDebris(float xPosition, float yPosition, float radius) : cPhysicsObject(xPosition, yPosition, radius) {
	debris.setSize(Vector2f(8.0f, 8.0f));	
	debris.setOrigin(debris.getSize() / 2.0f);
	debris.setFillColor(Color::Green);
	nrgLoss = 0.5;
	nBounceBeforeDeath = 7;

	velocity = { (float)pow(-1, rand() - RAND_MAX / 2) * 15.0f * cos((float)rand() / (float)RAND_MAX) * 2.0f * 3.1415f, 
		(float)pow(-1, rand() - RAND_MAX / 2) * 15.0f * sin((float)rand() / (float)RAND_MAX) * 2.0f * 3.1415f };
}

cDebris::cDebris(float xPosition, float yPosition, Color color, float radius) : cPhysicsObject(xPosition, yPosition, radius) {
	debris.setSize(Vector2f(8.0f, 8.0f));
	debris.setOrigin(debris.getSize() / 2.0f);
	debris.setFillColor(color);
	nrgLoss = 0.5;
	nBounceBeforeDeath = 5;

	velocity = { (float)pow(-1, rand() - RAND_MAX / 2) * 15.0f * cos((float)rand() / (float)RAND_MAX) * 2.0f * 3.1415f,
		(float)pow(-1, rand() - RAND_MAX / 2) * 15.0f * sin((float)rand() / (float)RAND_MAX) * 2.0f * 3.1415f };
}

void cDebris::draw(RenderWindow& window) const {
	debris.setPosition(position);
	window.draw(debris);
}

int cDebris::bounceDeathAction() const {
	return 0;
}
