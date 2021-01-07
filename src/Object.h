#pragma once

#ifndef OBJECT_H

#include "ofMain.h"
#include "GameObject.h"

#define OBJECT_H

class Object : public GameObject {
	
public:

	Object(ofVec2f _pos, float _mass, float _radius);
	void update() override;
	void draw() override;

	void applyForce(ofVec2f _force);
	ofVec2f applyFriction();
	ofVec2f getAcceleration();
	void updateMovementForces();
	void updateGUI();

	void mousePressed(int _x, int _y, int _button) override;
	void mouseReleased(int _x, int _y, int _button) override;

	ofVec2f friction;

	bool mouse_down_triggered;
	bool initiai_values_triggered;

	ofVec2f anchorPos;
	int node;

	//CalculateSprings springs;
};

#endif