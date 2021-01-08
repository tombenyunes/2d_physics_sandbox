#pragma once

#include "ofMain.h"

class GameObject;


class Controller {

public:
	
	Controller();

	void setGravity(bool _value);
	void makeActive(GameObject* _this);
	GameObject* getActive();

	GameObject* activeObject;

	bool GRAVITY;
	bool OBJECT_SELECTED;
	bool MOUSE_BEING_DRAGGED;
	int NEW_NODE_NAME;


};