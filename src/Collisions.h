#pragma once

#ifndef COLLISIONS_H

#include "ofMain.h"

#define COLLISIONS_H

class Collisions
{

public:
	Collisions();
	bool EllipseCompare(ofVec2f _pos1, float _r1, ofVec2f _pos2, float _r2);

};

#endif