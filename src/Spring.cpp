#include "Spring.h"

Spring::Spring(ofVec2f _pos, float _mass, float springConst, float damping, float restPos)
{
	// Spring drawing constants for top bar
	pos = _pos;
	mass = 30;

	springHeight = 32;
	width = 100;
	left = pos.x - width;
	right = pos.x + width;
	maxHeight = 200;
	minHeight = 100;
	over = false;
	move = false;

	// Spring simulation constants
	M = _mass;  // Mass
	K = springConst;  // Spring constant
	D = damping; // Damping
	R = restPos;  // Rest position

	// Spring simulation variables
	springPos = R;   // Position
	velocity = 0.0; // Velocity
	accel = 0;   // Acceleration
	f = 0;    // Force

	AddModule("gravity");
}

void Spring::update()
{
	// Update the spring position
	if (!move) {
		f = -K * (springPos - R); // f=-ky
		accel = f / M;          // Set the acceleration, f=ma == a=f/m
		velocity = D * (velocity + accel);  // Set the velocity
		springPos = springPos + velocity;        // Updated position
	}

	if (abs(velocity) < 0.1) {
		velocity = 0.0;
	}

	// Test if mouse if over the top bar
	if (ofGetMouseX()-ofGetWidth()/2 > pos.x + left && ofGetMouseX()-ofGetWidth()/2 < pos.x + right && ofGetMouseY()-ofGetHeight()/2 > pos.y + springPos && ofGetMouseY()-ofGetHeight()/2 < pos.y + springPos + springHeight) {
		over = true;
	}
	else {
		over = false;
	}

	// Set and constrain the position of top bar
	if (move) {
		springPos = ofGetMouseY()-ofGetHeight()/2 - pos.y - springHeight / 2;
		springPos = ofClamp(springPos, minHeight, maxHeight);
	}
}

void Spring::draw()
{
	// Draw base
	ofSetColor(125);
	ofFill();
	
	float baseWidth = 0.5 * springPos;
	ofRect(pos.x - baseWidth, pos.y + springPos + springHeight, springPos, springHeight - springPos + 200);

	// Set color and draw top bar
	if (over || move) {
		ofSetColor(255);
	}
	else {
		ofSetColor(204);
	}
	ofRect(pos.x + left, pos.y + springPos, right * 2, springHeight);

	// Bottom bar
	ofRect(pos.x + left, pos.y + 264, right * 2, springHeight/4);
}

void Spring::mousePressed(int _x, int _y, int _button)
{
	if (over) move = true;
}

void Spring::mouseReleased()
{
	move = false;
}