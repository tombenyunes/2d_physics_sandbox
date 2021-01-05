#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class guiController {

public:

	guiController();
	void update();
	void updateValues(ofVec2f _pos, ofVec2f _vel, ofVec2f _accel, bool active = false);

	ofxPanel gui;
	ofxPanel gui2;

	ofxLabel position;
	ofxLabel velocity;
	ofxLabel accel;

	ofxLabel position2;
	ofxLabel velocity2;
	ofxLabel accel2;

};