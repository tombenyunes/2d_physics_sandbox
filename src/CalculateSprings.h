#pragma once

#include "ofMain.h"
#include "Controller.h"
#include "GameObject.h"

class CalculateSprings
{

public:

	CalculateSprings();
	ofVec2f update(Controller* _GameController, int _node);

	float gravity;
	float timeStep;
	float g_k;
	float g_damping;

	float springmass;

};

