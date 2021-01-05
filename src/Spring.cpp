#include "Spring.h"

Spring::Spring(ofVec2f _pos, float mass, float springConst, float damping, float restPos)
{
	// Spring drawing constants for top bar
	pos = _pos;

	springHeight = 32;
	width = 100;
	left = pos.x - width;
	right = pos.x + width;
	maxHeight = 800;
	minHeight = 50;
	over = false;
	move = false;

	// Spring simulation constants
	M = mass;  // Mass
	K = springConst;  // Spring constant
	D = damping; // Damping
	R = restPos;  // Rest position

	// Spring simulation variables
	springPos = R;   // Position
	vel = 0.0; // Velocity
	accel = 0;   // Acceleration
	f = 0;    // Force
}

void Spring::update()
{
	// Update the spring position
	if (!move) {
		f = -K * (springPos - R); // f=-ky
		accel = f / M;          // Set the acceleration, f=ma == a=f/m
		vel = D * (vel + accel);  // Set the velocity
		springPos = springPos + vel;        // Updated position
	}

	if (abs(vel) < 0.1) {
		vel = 0.0;
	}

	// Test if mouse if over the top bar
	if (ofGetMouseX()-ofGetWidth()/2 > left && ofGetMouseX()-ofGetWidth()/2 < right && ofGetMouseY()-ofGetHeight()/2 > springPos && ofGetMouseY()-ofGetHeight()/2 < springPos + springHeight) {
		over = true;
	}
	else {
		over = false;
	}

	// Set and constrain the position of top bar
	if (move) {
		springPos = ofGetMouseY()-ofGetHeight()/2 - springHeight / 2;
		springPos = ofClamp(springPos, minHeight, maxHeight);
	}
}

void Spring::draw()
{
	// Draw base
	ofSetColor(125);
	ofFill();
	float baseWidth = 0.5 * springPos;

	//cout << pos.x << "   " << baseWidth << "   " << springPos << "   " << springHeight << endl;
	ofRect(pos.x - baseWidth, springPos + springHeight, 100, ofGetHeight());

	// Set color and draw top bar
	if (over || move) {
		ofSetColor(255);
	}
	else {
		ofSetColor(204, 0, 0);
	}

	ofRect(left, springPos, right, springPos + springHeight);
}

void Spring::mousePressed(int _x, int _y, int _button)
{
	move = true;
}

void Spring::mouseReleased()
{
	move = false;
}