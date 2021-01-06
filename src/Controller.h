#pragma once

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ofMain.h"

class GameObject;


class Controller {

public:
	
	Controller();

	void setGravity(bool _value);
	void invertGravity();
	void makeActive(GameObject* _this);
	GameObject* getActive();

	GameObject* activeObject;

	bool GRAVITY;
	bool OBJECT_SELECTED;


};

#endif