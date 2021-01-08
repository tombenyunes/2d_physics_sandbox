#pragma once

#ifndef OBJECT_H

#include "ofMain.h"
#include "GameObject.h"

#define OBJECT_H

class Object : public GameObject {
	
public:

	Object(ofVec2f _pos, float _mass, float _radius);
	
	void dragNodes();
	void update() override;
	void draw() override;
	
	ofVec2f getFriction();
	ofVec2f applyAllForces();
	void addForces();
	void updateForces();
	void updateGUI();
	void resetForces();

	void mousePressed(int _x, int _y, int _button) override;
	void mouseReleased(int _x, int _y, int _button) override;

	ofVec2f friction;

	ofVec2f anchorPos;
	int node;

	bool mouse_down_triggered;
	bool initiai_values_triggered;
	bool mouseDrag;

	//CalculateSprings springs;
};

#endif