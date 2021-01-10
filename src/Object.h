#pragma once

#include "ofMain.h"
#include "GameObject.h"

class Object : public GameObject {
	
public:

	Object(ofVec2f _pos, float _mass, float _radius);
	
	void update() override;	
	void updateForces();
	ofVec2f applyAllForces();
	ofVec2f getFriction();
	void updateGUI();
	void dragNodes();
	void resetForces();

	void mousePressed(int _x, int _y, int _button) override;
	void mouseReleased(int _x, int _y, int _button) override;

	void draw() override;

	ofVec2f anchorPos;
	int node;

	bool mouse_down_triggered;
	bool initiai_values_triggered;
	bool mouseDrag;

	bool startedDragging = false;
	//ofVec2f mousePosBeforeDrag;

	//CalculateSprings springs;
};