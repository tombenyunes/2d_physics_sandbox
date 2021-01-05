#pragma once

#include "ofMain.h"
#include "guiController.h"


class Controller {

public:
	
	Controller();

	void invertGravity();
	void makeActive();

	bool GRAVITY;
	bool OBJECT_SELECTED;

};