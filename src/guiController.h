#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class guiController {

public:

	guiController();
	void update();
	void updateValues(ofVec2f _pos, ofVec2f _vel, ofVec2f _accel);

	ofxPanel gui;

	ofxLabel position;
	ofxLabel velocity;
	ofxLabel accel;

};