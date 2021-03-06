#include "Player.h"

Player::Player(ofVec2f _pos, ofColor _color)
{
	pos.set(_pos);
	color.set(_color);

	vel.set(0);
	accel.set(0);
	radius = 35;
	mass = 500;

	isPlayer = true;
	mouse_down = false;
	mouse_button = -1;	
	aimingBoost = false;

	// modules are updated automatically
	AddModule("screenBounce");
	AddModule("ellipseCollider");
	AddModule("gravity");
	AddModule("friction");
}

void Player::update()
{
	updateForces();
	updateGUI();
	resetForces();
}

void Player::updateForces()
{
	applyAllForces();
	addForces(true);
}

void Player::applyAllForces()
{
	if (playerCanMove()) applyForce(accel, getMovementVector(), true, 0.15);
}

bool Player::playerCanMove()
{
	if (mouse_down && mouse_button == 0) {
		return true;
	}
	else {
		return false;
	}
}

ofVec2f Player::getMovementVector()
{
	ofVec2f movementVec = pos - mouse_pos;
	movementVec.scale(5);
	return movementVec;
}

void Player::updateGUI()
{
	static bool initiai_values_triggered = false; // initial values are sent to the gui_manager initially, after which it will update the results internally, and the object can receive the values back
	if (!initiai_values_triggered) {
		initiai_values_triggered = true;
		gui_Controller->updateValues(pos, vel, accel, mass, infiniteMass, radius, affectedByGravity, 1);
	}
	else {
		gui_Controller->updateValues(pos, vel, accel, gui_Controller->mass, gui_Controller->infiniteMass, gui_Controller->radius, gui_Controller->affectedByGravity, 1); // receiving and updating the results from the gui_controller
		if (infiniteMass) mass = 9999999999999999999; else mass = gui_Controller->mass;
		radius = gui_Controller->radius;
		infiniteMass = gui_Controller->infiniteMass;
		affectedByGravity = gui_Controller->affectedByGravity;
	}
}

void Player::resetForces()
{
	accel.set(0);
}


// ----- EVENT FUNCTIONS ----- //


void Player::mousePressed(int _x, int _y, int _button)
{
	mouse_down = true;
	mouse_button = _button;
	mouse_pos = { (float)_x, (float)_y };
}

void Player::mouseDragged(int _x, int _y, int _button)
{
	mouse_down = true;
	mouse_button = _button;
	mouse_pos = { (float)_x, (float)_y };
}

void Player::mouseReleased(int _x, int _y, int _button)
{
	mouse_down = false;
}

void Player::keyPressed(int key)
{
	if (key == 114) // r
	{
		accel = { 0, 0 };
		vel = { 0, 0 };
		pos = { 0, 0 };
	}
	if (key == 32)
	{
		aimingBoost = true;
	}
}

void Player::keyReleased(int key)
{
	if (key == 32)
	{
		boostPlayer();
	}
}

void Player::boostPlayer()
{
	aimingBoost = false;
	if (vel.length() < 5) {
		applyForce(accel, (pos - ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2)), true, 10);
	}
}


// ----- RENDER LOOP ----- //


void Player::draw()
{
	ofSetColor(255);

	if (aimingBoost) drawBoostDirection();
	drawParticleTrail();

	ofSetColor(color);
	ofFill();
	ofEllipse(pos.x, pos.y, radius, radius);
}

void Player::drawBoostDirection() // draws dotted line in the direction the player is aiming
{
	ofPushMatrix();

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(8, 0xAAAA);
	glBegin(GL_LINES);
	glVertex3f(pos.x, pos.y, 0);
	glVertex3f(drawVelPath().x, drawVelPath().y, drawVelPath().z);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glFlush();

	ofPopMatrix();
}

ofVec3f Player::drawVelPath()
{
	ofVec2f vec = pos - ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2);
	return ofVec3f(vec.x * ofGetWidth(), vec.y * ofGetHeight(), 0);
}

void Player::drawParticleTrail() // draws particle trail following the player when moving
{
	if (mouse_down && mouse_button == 0) {
		GameObject* particle = new Particle{ pos /*+ ofRandom(-radius/3, radius/3)*/, getMovementVector() * -1, 4, ofColor(255), 255 };
		GameObjects->push_back(particle);
	}
}