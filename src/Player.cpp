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


	AddModule("screenBounce");
	AddModule("gravity");
	AddModule("ellipseCollider");
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
	applyForce(accel, getFriction());
	if (playerCanMove()) applyForce(accel, getMovementVector(), true, 0.15);
}

ofVec2f Player::getFriction()
{
	ofVec2f friction = vel * -1;
	friction *= FRICTION_FORCE;
	return friction;
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
	static bool initiai_values_triggered = false;
	if (!initiai_values_triggered) {
		initiai_values_triggered = true;
		gui_Controller->updateValues(pos, vel, accel, mass, infiniteMass, radius, affectedByGravity, 1);
	}
	else {
		gui_Controller->updateValues(pos, vel, accel, gui_Controller->mass, gui_Controller->infiniteMass, gui_Controller->radius, gui_Controller->affectedByGravity, 1);
		if (infiniteMass) {
			mass = 9999999999999999999;
		}
		else {
			mass = gui_Controller->mass;
		}
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

	if (aimingBoost) {
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

	drawParticleTrail();

	ofSetColor(color);
	ofFill();
	//float mult = (ofMap(vel.length(), 0, 15, 1, 0.25));
	ofEllipse(pos.x, pos.y, radius /** mult*/, radius /** mult*/);

	ofVec2f velLine = vel;
	velLine.normalize();

	ofSetLineWidth(0.01);
	//ofLine(ofVec3f(pos.x, pos.y, 0), ofVec3f(velLine.x * ofGetWidth(), velLine.y * ofGetHeight(), 0));
}

ofVec3f Player::drawVelPath()
{
	ofVec2f vec = pos - ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2);
	return ofVec3f(vec.x * ofGetWidth(), vec.y * ofGetHeight(), 0);
}

void Player::drawParticleTrail()
{
	if (mouse_down && mouse_button == 0) {
		GameObject* particle = new Particle{ pos /*+ ofRandom(-radius/3, radius/3)*/, getMovementVector() * -1, 4, ofColor(255), 255 };
		GameObjects->push_back(particle);
	}
}