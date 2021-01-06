#pragma once

#ifndef GUICONTROLLER_H

#include "ofMain.h"
#include "ofxGui.h"
#include "Controller.h"

#define GUICONTROLLER_H

class guiController {

public:

	guiController();
	void update(Controller* _controller);
	void updateValues(ofVec2f _pos, ofVec2f _vel, ofVec2f _accel, float _mass,float _radius, int panel);
	void windowResized(int w, int h);

	ofxPanel world_gui;
	ofxPanel player_gui;
	ofxPanel selected_gui;

	ofxToggle gravity;

	ofxLabel position;
	ofxLabel velocity;
	ofxLabel accel;
	ofxFloatSlider mass;
	ofxFloatSlider radius;

	ofxLabel position2;
	ofxLabel velocity2;
	ofxLabel accel2;
	ofxFloatSlider mass2;
	ofxFloatSlider radius2;

};

#endif