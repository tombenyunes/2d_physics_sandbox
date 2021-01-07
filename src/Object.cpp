#include "Object.h"

Object::Object(ofVec2f _pos, float _mass, float _radius)
{
	//pos.set(ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2), ofRandom(-ofGetHeight() / 2, ofGetHeight() / 2));
	pos.set(_pos);
	color = ofColor(255);
	mass = _mass;
	radius = _radius;

	mouse_down_triggered = false;
	initiai_values_triggered = false;

	AddModule("screenBounce");
	AddModule("gravity");
	AddModule("ellipseCollider");
	AddModule("mouseHover");
}

void Object::update()
{
	updateMovementForces();
}

void Object::applyForce(ofVec2f _force)
{
	accel += _force;
}

ofVec2f Object::applyFriction()
{
	friction = vel * -1;
	friction *= FRICTION;
	return friction;
}

ofVec2f Object::getAcceleration()
{
	// Adds friction to acceleration
	applyForce(applyFriction());

	return accel.limit(MAXIMUM_ACCELERATION);
}

void Object::updateMovementForces()
{
	vel += getAcceleration();
	vel.limit(MAXIMUM_VELOCITY);
	pos += vel;
	
	if (GameController->activeObject == this) {
		updateGUI();
	}

	accel.set(0);
}

void Object::updateGUI()
{
	if (!initiai_values_triggered) {
		initiai_values_triggered = true;
		gui_Controller->updateValues(pos, vel, accel, mass, radius, 2);
	}
	else {
		gui_Controller->updateValues(pos, vel, accel, gui_Controller->mass2, gui_Controller->radius2, 2);
		mass = gui_Controller->mass2;
		radius = gui_Controller->radius2;
	}
	//mass = gui_Controller->mass;
}

void Object::mousePressed(int _x, int _y, int _button)
{
	if (!mouse_down_triggered) {
		mouse_down_triggered = true;
		if (_button == 2 && mouseOver) {
			if (GameController->activeObject != this) {
				initiai_values_triggered = false;
				GameController->makeActive(this);
			}
		}
	}
}

void Object::mouseReleased(int _x, int _y, int _button)
{
	if (_button == 2 && mouse_down_triggered) {
		mouse_down_triggered = false;
	}
}

void Object::draw()
{
	ofPushStyle();

	if (GameController->activeObject == this) {
		ofSetColor(255, 0, 0);
	}
	else {
		ofSetColor(color);
	}
	ofNoFill();
	ofSetLineWidth(ofMap(mass, 1, 100000, 0.1, 10));

	ofEllipse(pos.x, pos.y, radius, radius);

	ofPopStyle();
}