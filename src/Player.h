#pragma once

#ifndef PLAYER_H

#include "ofMain.h"
#include "GameObject.h"
#include "Particle.h"
#include "Controller.h"
#include "guiController.h"

#define PLAYER_H

class Player : public GameObject {

public:
	Player(ofVec2f _pos = { 0, 0 }, ofColor _color = ofColor(255));

	void update() override;

	ofVec2f getFriction();
	ofVec2f getMovementVector();
	ofVec2f getInterpolatedPosition();

	bool playerCanMove();

	void addForces();
	ofVec2f applyAllForces();
	void updateForces();
	void updateGUI();
	void resetForces();

	void mousePressed(int _x, int _y, int _button) override;
	void mouseReleased(int _x, int _y, int _button) override;
	void keyPressed(int key) override;
	void keyReleased(int key) override;

	void boostPlayer();

	void draw() override;
	ofVec3f drawVelPath();
	void drawParticleTrail();

private:
	
	bool mouse_down;
	int mouse_button;
	ofVec2f mouse_pos;
	
	bool aimingBoost;

};

#endif