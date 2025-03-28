#include "cDummy.h"
                                                 //here i just calling constructor of parrent class
cDummy::cDummy(float xPosition, float yPosition, float radius) : cPhysicsObject(xPosition, yPosition, radius) {
    dummyCircle.setRadius(radius);
    dummyCircle.setOrigin({ radius, radius });
    dummyCircle.setFillColor(Color::White);
    dummyCircle.setOutlineColor(Color::Yellow);
    dummyCircle.setOutlineThickness(1.0f);
}

void cDummy::draw(RenderWindow& window) const {
    dummyCircle.setPosition(position);
    window.draw(dummyCircle);

}

int cDummy::bounceDeathAction() const {
    return 0;
}

