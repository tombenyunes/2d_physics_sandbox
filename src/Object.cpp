#include "Object.h"

Object::Object(ofVec2f _pos, float _mass, float _radius, Controller* _controller)
{
	// game controller must be initialized before waiting for root_update, as very occasionally it is required before the first update cycle
	GameController = _controller;

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

void Object::update()
{
	prevMousePos.set(ofGetMouseX() / 2 - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2);
	updateForces();
	updateGUI();
	dragNodes();
	resetForces();
}

void Object::updateForces()
{
	applyAllForces();
	addForces(false);
}

void Object::applyAllForces()
{
	applyForce(accel, getFriction());
}

ofVec2f Object::getFriction()
{
	ofVec2f friction = vel * -1;
	friction *= FRICTION_FORCE;
	return friction;
}

void Object::updateGUI()
{
	if (GameController->getActive() == this) {
		if (!initiai_values_triggered) {
			initiai_values_triggered = true;
			gui_Controller->updateValues(pos, vel, accel, mass, infiniteMass, radius, affectedByGravity, 2);
		}
		else {
			gui_Controller->updateValues(pos, vel, accel, gui_Controller->selected_mass, gui_Controller->selected_infiniteMass, gui_Controller->selected_radius, gui_Controller->selected_affectedByGravity, 2);
			if (infiniteMass) {
				mass = 999999999999;
			}
			else {
				mass = gui_Controller->selected_mass;
			}
			radius = gui_Controller->selected_radius;
			infiniteMass = gui_Controller->selected_infiniteMass;
			affectedByGravity = gui_Controller->selected_affectedByGravity;
		}
	}
}

void Object::dragNodes()
{
	static ofVec2f mousePosBeforeDrag;
	if (mouseDrag) {
		ofVec2f prevPos2 = ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2) + mouseOffsetFromCenter;

		ofVec2f newPos;
		newPos.x = ofLerp(pos.x, prevPos2.x, 0.1);
		newPos.y = ofLerp(pos.y, prevPos2.y, 0.1);

		pos.set(newPos);

		vel.set(0);

		startedDragging = true;
		mousePosBeforeDrag = ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2);
	}
	else {
		if (startedDragging == true) {
			startedDragging = false;
			ofVec2f mousespeed = (ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2) - mousePosBeforeDrag) / 3;
			applyForce(accel, mousespeed, false);
		}
	}
}

void Object::resetForces()
{
	accel.set(0);
}


// ----- EVENT FUNCTIONS ----- //


void Object::mousePressed(int _x, int _y, int _button)
{
	if (!mouse_down_triggered) {
		mouse_down_triggered = true;
		if (_button == 2 && mouseOver) {
			if (GameController->getActive() != this) {
				initiai_values_triggered = false;
				GameController->makeActive(this);
			}
		}
	}
}

void Object::mouseDragged(int _x, int _y, int _button)
{
	if (_button == 2) {
		if (mouseOver && GameController->getMouseDragged() == false) {			
			if (prevMousePos.distance(ofVec2f(ofGetMouseX() / 2 - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2)) > 2) {
				// the node will only be moved by the mouse if it has been moved by more than 1 pixel - this prevents accidentally stopping something by selecting it
				mouseDrag = true;
				GameController->setMouseDragged(true);				
			}
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
			GameController->setMouseDragged(false);
		}
	}
}


// ----- RENDER LOOP ----- //


void Object::draw()
{
	ofPushStyle();

	if (infiniteMass) {
	ofSetColor(255, 0, 0);
	}
	else if (GameController->getActive() == this) {
		ofSetColor(255, 165, 0);
	}
	else {
		ofSetColor(color);
	}
	ofNoFill();
	ofSetLineWidth(ofMap(mass, MINIMUM_MASS, MAXIMUM_MASS, 0.1, 10));

	ofEllipse(pos.x, pos.y, radius, radius);

	ofVec2f velLine = vel;
	velLine.normalize();

	ofSetLineWidth(0.01);
	//ofLine(ofVec3f(pos.x, pos.y, 0), ofVec3f(velLine.x * ofGetWidth(), velLine.y * ofGetHeight(), 0));

	ofPopStyle();
}