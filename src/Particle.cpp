#include "Particle.h"

Particle::Particle(ofVec2f _pos, ofVec2f _vel, float _radius, ofColor _color, int _lifetime)
{
	pos = _pos;
	vel = _vel;
	vel.x += ofRandom(-1.5, 1.5);
	vel.y += ofRandom(-1.5, 1.5);
	radius = _radius;
	color = _color;
	lifetime = _lifetime;

	AddModule("screenBounce");
	AddModule("gravity");
}

void Particle::update()
{
	friction = vel;
	friction *= -1;
	friction *= FRICTION_FORCE;
	accel += (friction*2);
	accel.limit(MAXIMUM_ACCELERATION);

	vel += accel;
	accel.set(0);

	ofVec2f newPos;
	newPos.x = ofLerp(pos.x, pos.x + vel.x, 0.75);
	newPos.y = ofLerp(pos.y, pos.y + vel.y, 0.75);

	pos = newPos;

	if (radius > 0) {
		radius -= 0.05;
	}
	else {
		needs_to_be_deleted = true;
	}
}

void Particle::draw()
{
	ofSetColor(color, lifetime);
	ofDrawEllipse(pos.x, pos.y, radius, radius);
}