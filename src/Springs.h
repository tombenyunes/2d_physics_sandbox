#pragma once

#ifndef SPRINGS_H

#include "ofMain.h"
#include "GameObject.h"

#define SPRINGS_H

class Springs : public GameObject {
	
public:

	Springs(ofVec2f _anchorPos, int _anchorRadius, float _k, float _damping, float _springmass);

	ofVec2f updateSprings(int _node);
	void ellipseCollider() override;
	void mouseHover() override;
	void isColliding(GameObject* _other, int _node);

	void update() override;
	void draw() override;

	void applyForce(ofVec2f _force, int _node);
	ofVec2f applyFriction(int _node);
	ofVec2f getAcceleration(int _node);
	void updateMovementForces();
	void updateGUI();

	void mousePressed(int _x, int _y, int _button) override;
	void mouseReleased(int _x, int _y, int _button) override;

	ofVec2f friction;

	bool mouse_down_triggered;
	bool initiai_values_triggered;

	float gravity;
	float timeStep;
	float g_k;
	float g_damping;

	float k;
	float damping;
	float springmass;
	ofVec2f nodePos1;
	ofVec2f nodeVel1;
	ofVec2f nodeAccel1;
	ofVec2f nodePos2;
	ofVec2f nodeVel2;
	ofVec2f nodeAccel2;

	int mouseOver1;
	int mouseOver2;

};

#endif