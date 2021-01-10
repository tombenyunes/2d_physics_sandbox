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
	void updateForces();
	void applyAllForces();
	ofVec2f getFriction();
	bool playerCanMove();
	ofVec2f getMovementVector();
	void updateGUI();
	void resetForces();

	void mousePressed(int _x, int _y, int _button) override;
	void mouseDragged(int _x, int _y, int _button) override;
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