#pragma once

#include "ofMain.h"
#include "GameObject.h"
#include "Particle.h"

#define MAXIMUM_ACCELERATION 0.15
#define MAXIMUM_VELOCITY 15
#define FRICTION 0.015

class Player : public GameObject {

public:
	Player(ofVec2f _pos = { 0, 0 }, ofColor _color = ofColor(255));

	void update();

	ofVec2f getTeleportVector();
	void teleportPlayer();
	void applyFriction();
	ofVec2f getMovementVector();
	ofVec2f getAcceleration();
	ofVec2f getInterpolatedPosition();
	void updateMovementForces();

	void drawParticleTrail();

	void keyPressed(int key);
	void keyReleased(int key);

	void draw();

	ofVec2f friction;

private:

	bool readyToTeleport;
	ofVec2f teleportTarget;
	bool isTeleporting;
	ofVec2f previousMousePos;

};