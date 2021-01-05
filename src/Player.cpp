#include "Player.h"

Player::Player(ofVec2f _pos, ofColor _color)
{
	pos.set(_pos);
	color.set(_color);

	vel.set(0);
	accel.set(0);
	radius = 35;

	// Events
	mouse_down = false;
	mouse_button = -1;

	// Teleporting
	readyToTeleport = true;
	isTeleporting = false;

	AddModule("screenBounce");
	AddModule("gravity");
}

void Player::update()
{
	//updateGUI();
	if (isTeleporting) teleportPlayer();
	updateMovementForces();
}

ofVec2f Player::getTeleportVector()
{
	int movementDirection;
	if (vel.x > 0 && vel.y < 0) {
		//cout << "right up" << endl;
		movementDirection = 0;
	}
	else if (vel.x > 0 && vel.y > 0) {
		//cout << "right down" << endl;
		movementDirection = 1;
	}
	else if (vel.x < 0 && vel.y > 0) {
		//cout << "left down" << endl;
		movementDirection = 2;
	}
	else if (vel.x < 0 && vel.y < 0) {
		//cout << "left up" << endl;
		movementDirection = 3;
	}
	cout << vel << endl;
	//return ((vel-pos) * 2 * -1);
	return vel.scale(2);
	//return { (float)ofGetMouseX() - ofGetWidth() / 2, (float)ofGetMouseY() - ofGetHeight() / 2 };
}

void Player::teleportPlayer()
{
	if (abs(pos.x - teleportTarget.x) < 1 || abs(pos.y - teleportTarget.y) < 1) {
		isTeleporting = false;
		//ofVec2f movementVec = pos - previousMousePos;
		//movementVec.scale(5);
		//accel += getMovementVector();
	}
	else {
		//float progress = (float)(ofGetFrameNum() % 100) / 100;
		float progress = (float)(((int)(ofGetElapsedTimef() * 60)) % 100) / 100;

		ofVec2f powInterpIn;
		powInterpIn.x = ofNextPow2(progress);
		powInterpIn.y = ofNextPow2(progress);

		float sinInterp = sin(progress * (PI / 2));

		ofVec2f newPos;
		//newPos.x = ofLerp(pos.x, teleportTarget.x, powInterpIn.x/5);
		//newPos.y = ofLerp(pos.y, teleportTarget.y, powInterpIn.y/5);
		//newPos.x = ofLerp(pos.x, teleportTarget.x, sinInterp*2);
		//newPos.y = ofLerp(pos.y, teleportTarget.y, sinInterp*2);
		newPos.x = ofLerp(pos.x, teleportTarget.x, 0.1);
		newPos.y = ofLerp(pos.y, teleportTarget.y, 0.1);
		pos = newPos;
	}
}

ofVec2f Player::applyFriction()
{
	//if (!mouse_down) {
		friction = vel * -1;
		//friction.normalize(); // normalizing breaks ui
		friction *= FRICTION;
	//}
	
	return accel += friction;
}

ofVec2f Player::getMovementVector()
{
	ofVec2f movementVec = pos - mouse_pos;
	movementVec.scale(5);
	return movementVec;
}

ofVec2f Player::getAcceleration()
{
	accel = applyFriction();
	if (mouse_down && mouse_button == 0) {
		accel += getMovementVector();
	}
	return accel.limit(MAXIMUM_ACCELERATION);
}

ofVec2f Player::getInterpolatedPosition()
{
	//ofVec2f newPos;
	//newPos.x = ofLerp(pos.x, pos.x + vel.x, 0.75);
	//newPos.y = ofLerp(pos.y, pos.y + vel.y, 0.75);
	//return newPos;

	int progress = (ofGetFrameNum() % 100) / 100;
	ofVec2f powInterpIn;
	powInterpIn.x = ofNextPow2(progress);
	powInterpIn.y = ofNextPow2(progress);

	float sinInterp = sin(progress * (PI / 2));

	ofVec2f newPos;
	newPos.x = ofLerp(pos.x, pos.x + vel.x, powInterpIn.x);
	newPos.y = ofLerp(pos.y, pos.y + vel.y, powInterpIn.y);
	return newPos;
}

void Player::updateMovementForces()
{
	vel += getAcceleration();
	vel.limit(MAXIMUM_VELOCITY);
	pos = getInterpolatedPosition();
	
	updateGUI();

	accel.set(0);
}

void Player::updateGUI()
{
	gui_Controller->updateValues(pos, vel, accel);
}

void Player::drawParticleTrail()
{
	if (mouse_down && mouse_button == 0) {
		GameObject* particle = new Particle{ pos + ofRandom(-radius/3, radius/3), getMovementVector() * -1, 4, ofColor(255), 255 };
		GameObjects->push_back(particle);
	}
}

ofVec3f Player::drawVelPath()
{
	ofVec2f vec = pos - ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2);
	return ofVec3f(vec.x * ofGetWidth(), vec.y * ofGetHeight(), 0);
}

// ----- EVENT FUNCTIONS ----- //

void Player::mousePressed(int _x, int _y, int _button)
{
	mouse_down = true;
	mouse_button = _button;
	mouse_pos = { (float)_x, (float)_y };
}

void Player::mouseReleased()
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
		if (readyToTeleport == true) {
			/*readyToTeleport = false;
			isTeleporting = true;
			teleportTarget = getTeleportVector();
			vel.set(0);
			accel.set(0);
			ofResetElapsedTimeCounter();
			previousMousePos = mouse_pos;*/
			aiming = true;
		}
	}
	if (key == 103)
	{
		GameController->invertGravity();
	}
}

void Player::keyReleased(int key)
{
	if (key == 32)
	{
		readyToTeleport = true;
		aiming = false;

		accel += pos - ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2);
		vel += (accel * 10).limit(10);
		pos = getInterpolatedPosition();
	}
}

// ----- RENDER LOOP ----- //

void Player::draw()
{
	if (aiming) {
		ofPushMatrix();

		glEnable(GL_LINE_STIPPLE);
		glLineStipple(8, 0xAAAA);
		glBegin(GL_LINES);
		glVertex3f(pos.x, pos.y, 0);		
		glVertex3f(drawVelPath().x, drawVelPath().y, drawVelPath().z);
		glEnd();
		glDisable(GL_LINE_STIPPLE);
		glFlush();

		//ofSetLineWidth(0.5);
		//ofSetColor(125);
		//ofLine(ofVec3f(pos.x, pos.y, 0), drawVelPath());
		
		ofPopMatrix();
	}

	drawParticleTrail();

	ofSetColor(color);
	float mult = (ofMap(vel.length(), 0, 15, 1, 0.25));
	ofEllipse(pos.x, pos.y, radius * mult, radius * mult);
	//ofLine(ofVec3f(pos.x, pos.y, 0), ofVec3f(vel.x*ofGetWidth(), vel.y*ofGetHeight(), 0));
}
