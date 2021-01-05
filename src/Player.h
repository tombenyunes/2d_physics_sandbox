#pragma once

#include "ofMain.h"
#include "GameObject.h"
#include "Particle.h"
#include "Controller.h"
#include "guiController.h"

class Player : public GameObject {

public:
	Player(ofVec2f _pos = { 0, 0 }, ofColor _color = ofColor(255));

	void update() override;

	ofVec2f getTeleportVector();
	void teleportPlayer();
	ofVec2f applyFriction();
	ofVec2f getMovementVector();
	ofVec2f getAcceleration();
	ofVec2f getInterpolatedPosition();
	void updateMovementForces();
	void updateGUI();

	void drawParticleTrail();
	ofVec3f drawVelPath();

	void mousePressed(int _x, int _y, int _button) override;
	void mouseReleased(int _x, int _y, int _button) override;
	void keyPressed(int key) override;
	void keyReleased(int key) override;

	void draw() override;

	ofVec2f friction;

private:

	// Events
	bool mouse_down;
	int mouse_button;
	ofVec2f mouse_pos;

	// Teleporting
	bool readyToTeleport;
	ofVec2f teleportTarget;
	bool isTeleporting;
	ofVec2f previousMousePos;
	bool aiming = false;

};