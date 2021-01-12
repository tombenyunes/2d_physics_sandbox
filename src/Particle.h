#pragma once

#include "ofMain.h"
#include "GameObject.h"

class Particle : public GameObject {

public:

	Particle(ofVec2f _pos, ofVec2f _vel, float _radius, ofColor _color, int _lifetime);

	void update() override;
	void draw() override;


private:

	int lifetime;
	ofVec2f friction;

};