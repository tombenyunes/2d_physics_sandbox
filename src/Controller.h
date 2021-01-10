#pragma once

#include "ofMain.h"

#define MINIMUM_MASS 1
#define MAXIMUM_MASS 5000

#define MASS_LOWER_BOUND 250
#define MASS_UPPER_BOUND 2500

#define RADIUS_MINIMUM 1
#define RADIUS_MAXIMUM 500

#define RADIUS_LOWER_BOUND 25
#define RADIUS_UPPER_BOUND 250

#define MAXIMUM_ACCELERATION 0.15 // 0.15
#define MAXIMUM_VELOCITY 100 // 15

#define FRICTION_FORCE 0.015
#define GRAVITY_FORCE 0.0001

class GameObject;


class Controller {

public:
	
	Controller();

	void setGravity(bool _value);
	void clearAll();

	void makeActive(GameObject* _this);
	GameObject* getActive();

	GameObject* activeObject;

	bool GRAVITY;
	bool NEED_TO_DELETE_ALL;
	bool OBJECT_SELECTED;
	bool MOUSE_BEING_DRAGGED;
	int NEW_NODE_NAME;
	bool HARD_COLLISIONS;


};