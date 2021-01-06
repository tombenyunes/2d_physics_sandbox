#pragma once

#ifndef SPRING_H

#include "ofMain.h"
#include "GameObject.h"

#define SPRING_H

class Spring : public GameObject {

public:
	Spring(ofVec2f _pos, float mass, float springConst, float damping, float restPos);
	void update() override;
	void draw() override;

	void mousePressed(int _x, int _y, int _button) override;
	void mouseReleased(int _x, int _y, int _button) override;

private:

	int width;
	float springHeight;
	float left;
	float right;
	float maxHeight;
	float minHeight;
	bool over;
	bool move;

	float M;
	float K;
	float D;
	float R;

	float springPos;
	float velocity;
	float accel;
	float f;

};

#endif