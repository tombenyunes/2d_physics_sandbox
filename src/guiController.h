#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Controller.h"

class guiController {

public:

	guiController();
	void update(Controller* _controller);
	void updateWorld();
	void updateValues(ofVec2f _pos, ofVec2f _vel, ofVec2f _accel, float _mass, bool _infmass, float _radius, int panel);
	void updateMultipleValues(ofVec2f _anchorpos, ofVec2f _nodePos1, ofVec2f _nodeVel1, ofVec2f _nodeAccel1, float _nodeMass1, float _nodeRadius1, ofVec2f _nodePos2, ofVec2f _nodeVel2, ofVec2f _nodeAccel2, float _nodeMass2, float _nodeRadius2);
	void updateCreateNodeValues();
	
	void windowResized(int w, int h);

	Controller* GameController;

	// ----- Panels ----- //

	ofxPanel world_gui;
	ofxPanel player_gui;
	ofxPanel selected_gui;
	ofxPanel multi_selection_gui;
	ofxPanel create_node_gui;

	// ----- Parameters ----- //
	
	// World
	ofxToggle gravity;
	
	// Player
	ofxLabel position;
	ofxLabel velocity;
	ofxLabel accel;
	ofxFloatSlider mass;
	ofxToggle infiniteMass;
	ofxFloatSlider radius;

	// Selected Node
	ofxLabel position2;
	ofxLabel velocity2;
	ofxLabel accel2;
	ofxFloatSlider mass2;
	ofxToggle infiniteMass2;
	ofxFloatSlider radius2;

	// Multiple Selected Nodes
	ofxLabel anchorLabel;
	ofxLabel anchorPos;
	ofxLabel nodeLabel1;
	ofxLabel nodePos1;
	ofxLabel nodeVel1;
	ofxLabel nodeAccel1;
	ofxFloatSlider nodeRadius1;
	ofxFloatSlider nodeMass1;
	ofxLabel nodeLabel2;
	ofxLabel nodePos2;
	ofxLabel nodeVel2;
	ofxLabel nodeAccel2;
	ofxFloatSlider nodeRadius2;
	ofxFloatSlider nodeMass2;

	// Create New Node
	ofxLabel name;
	ofxLabel middleMouseToCreate;

};