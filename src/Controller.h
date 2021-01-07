#pragma once

#ifndef CONTROLLER_H
#define CONTROLLER_H

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
	
	ofVec2f anchorPos;
	ofVec2f nodePos1;
	ofVec2f nodeVel1;
	ofVec2f nodePos2;
	ofVec2f nodeVel2;


};

#endif