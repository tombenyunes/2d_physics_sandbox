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
	mouseDrag = false;

	AddModule("screenBounce");
	AddModule("gravity");
	AddModule("ellipseCollider");
	AddModule("mouseHover");
}

void Object::dragNodes()
{
	if (mouseDrag) {		
		pos.set(ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2) + mouseOffsetFromCenter);
		vel.set(0);
	}
}

void Object::update()
{
	updateForces();
	updateGUI();
	dragNodes();
	resetForces();
}

ofVec2f Object::getFriction()
{
	friction = vel * -1;
	friction *= FRICTION_FORCE;
	return friction;
}

ofVec2f Object::applyAllForces()
{
	applyForce(getFriction());
	return accel;
}

void Object::addForces()
{
	vel += accel.limit(MAXIMUM_ACCELERATION);
	pos += vel.limit(MAXIMUM_VELOCITY);
}

void Object::updateForces()
{
	applyAllForces();
	addForces();
}

void Object::updateGUI()
{
	if (GameController->activeObject == this) {
		if (!initiai_values_triggered) {
			initiai_values_triggered = true;
			gui_Controller->updateValues(pos, vel, accel, mass, infiniteMass, radius, 2);
		}
		else {
			gui_Controller->updateValues(pos, vel, accel, gui_Controller->mass2, gui_Controller->infiniteMass2, gui_Controller->radius2, 2);
			if (infiniteMass) {
				mass = 999999999999;
			}
			else {
				mass = gui_Controller->mass2;
			}
			radius = gui_Controller->radius2;
			infiniteMass = gui_Controller->infiniteMass2;
		}
	}
}

void Object::resetForces()
{
	accel.set(0);
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
	if (_button == 2) {
		if (mouseOver && GameController->MOUSE_BEING_DRAGGED == false) {
			mouseDrag = true;
			GameController->MOUSE_BEING_DRAGGED = true;
		}
	}
}

void Object::mouseReleased(int _x, int _y, int _button)
{
	if (_button == 2) {
		if (mouse_down_triggered) {
			mouse_down_triggered = false;
		}
		if (mouseDrag) {
			mouseDrag = false;
			GameController->MOUSE_BEING_DRAGGED = false;
		}
	}
}

void Object::draw()
{
	ofPushStyle();

	if (GameController->activeObject == this) {
		ofSetColor(255, 165, 0);
	}
	else {
		ofSetColor(color);
	}
	ofNoFill();
	ofSetLineWidth(ofMap(mass, 1, 10000, 0.1, 10));

	ofEllipse(pos.x, pos.y, radius, radius);

	ofPopStyle();
}