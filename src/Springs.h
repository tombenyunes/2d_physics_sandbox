#pragma once

#include "ofMain.h"
#include "GameObject.h"

class Springs : public GameObject {
	
public:

	Springs(ofVec2f _anchorPos, float _nodeRadius1, float _nodeMass1, float _nodeRadius2, float _nodeMass2, float _k, float _damping, float _springmass);

	ofVec2f updateSprings(int _node);
	void ellipseCollider() override;
	void mouseHover() override;
	void isColliding(GameObject* _other, int _node);

	void gravity() override;
	void dragNodes();
	void getNodeColor(int _node);

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

	float gravityForce;
	float timeStep;
	float g_k;
	float g_damping;

	float k;
	float damping;
	float springmass;
	ofVec2f nodePos1;
	ofVec2f nodeVel1;
	ofVec2f nodeAccel1;
	float nodeRadius1;
	float nodeMass1;
	float nodeGravityForce1;

	ofVec2f nodePos2;
	ofVec2f nodeVel2;
	ofVec2f nodeAccel2;
	float nodeRadius2;
	float nodeMass2;
	float nodeGravityForce2;

	bool mouse_down_triggered;
	bool initiai_values_triggered;
	bool mouseOverNode1;
	bool mouseOverNode2;
	bool mouseOverAnchor;
	bool mouseDragNode1;
	bool mouseDragNode2;
	bool mouseDragAnchor;

};