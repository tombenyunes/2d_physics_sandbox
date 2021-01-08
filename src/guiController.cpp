#include "guiController.h"

guiController::guiController()
{
	world_gui.setup("World");
	world_gui.add(gravity.setup("gravity", false));

	player_gui.setup("Player", "", 215, 10);	
	player_gui.add(position.setup("pos", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	player_gui.add(velocity.setup("vel", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	player_gui.add(accel.setup("accel", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	player_gui.add(mass.setup("mass", 404, 1, 500));
	player_gui.add(infiniteMass.setup("infinite mass", false));
	player_gui.add(radius.setup("radius", 404, 5, 300));

	selected_gui.setup("Selected Object", "", ofGetWidth() - 215, 10);
	selected_gui.add(position2.setup("pos", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	selected_gui.add(velocity2.setup("vel", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	selected_gui.add(accel2.setup("accel", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	selected_gui.add(mass2.setup("mass", 404, 1, 500));
	selected_gui.add(infiniteMass2.setup("infinite mass", false));
	selected_gui.add(radius2.setup("radius", 404, 5, 300));

	multi_selection_gui.setup("Spring", "", ofGetWidth() - 215, 10);
	multi_selection_gui.add(anchorLabel.setup("ANCHOR", "------------------------------"));
	multi_selection_gui.add(anchorPos.setup("pos", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	multi_selection_gui.add(nodeLabel1.setup("NODE 1", "------------------------------"));
	multi_selection_gui.add(nodePos1.setup("pos", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	multi_selection_gui.add(nodeVel1.setup("vel", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	multi_selection_gui.add(nodeAccel1.setup("accel", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	multi_selection_gui.add(nodeMass1.setup("mass", 404, 1, 500));
	multi_selection_gui.add(nodeRadius1.setup("radius", 404, 5, 300));
	multi_selection_gui.add(nodeLabel2.setup("NODE 2", "------------------------------"));
	multi_selection_gui.add(nodePos2.setup("pos", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	multi_selection_gui.add(nodeVel2.setup("vel", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	multi_selection_gui.add(nodeAccel2.setup("accel", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	multi_selection_gui.add(nodeMass2.setup("mass", 404, 1, 500));
	multi_selection_gui.add(nodeRadius2.setup("radius", 404, 5, 300));

}

void guiController::updateWorld(Controller* _controller)
{
	_controller->setGravity(gravity);
}

void guiController::updateValues(ofVec2f _pos, ofVec2f _vel, ofVec2f _accel, float _mass, bool _infmass, float _radius, int panel)
{
	if (panel == 1) {
		position = ofToString(roundf(_pos.x)) + ", " + ofToString(roundf(_pos.y));
		velocity = ofToString(roundf(_vel.x * 100) / 100) + ", " + ofToString(roundf(_vel.y * 100) / 100);
		accel = ofToString(roundf(_accel.x * 10000) / 10000) + ", " + ofToString(roundf(_accel.y * 10000) / 10000);
		if (_infmass) {
			mass.setTextColor(0);
			infiniteMass = true;
		}
		else {
			mass.setTextColor(255);
			mass = _mass;
			infiniteMass = false;
		}
		radius = _radius;
	}
	else if (panel == 2) {
		position2 = ofToString(roundf(_pos.x)) + ", " + ofToString(roundf(_pos.y));
		velocity2 = ofToString(roundf(_vel.x * 100) / 100) + ", " + ofToString(roundf(_vel.y * 100) / 100);
		accel2 = ofToString(roundf(_accel.x * 10000) / 10000) + ", " + ofToString(roundf(_accel.y * 10000) / 10000);
		if (_infmass) {
			mass2.setTextColor(0);
			infiniteMass2 = true;
		}
		else {
			mass2.setTextColor(255);
			mass2 = _mass;
			infiniteMass2 = false;
		}
		radius2 = _radius;
	}	
}

void guiController::updateMultipleValues(ofVec2f _anchorpos, ofVec2f _nodePos1, ofVec2f _nodeVel1, ofVec2f _nodeAccel1, float _nodeMass1, float _nodeRadius1, ofVec2f _nodePos2, ofVec2f _nodeVel2, ofVec2f _nodeAccel2, float _nodeMass2, float _nodeRadius2)
{
	anchorPos = ofToString(roundf(_anchorpos.x)) + ", " + ofToString(roundf(_anchorpos.y));
	nodePos1 = ofToString(roundf(_nodePos1.x)) + ", " + ofToString(roundf(_nodePos1.y));
	nodeVel1 = ofToString(roundf(_nodeVel1.x * 100) / 100) + ", " + ofToString(roundf(_nodeVel1.y * 100) / 100);
	nodeAccel1 = ofToString(roundf(_nodeAccel1.x * 10000) / 10000) + ", " + ofToString(roundf(_nodeAccel1.y * 10000) / 10000);
	nodeMass1 = _nodeMass1;
	nodeRadius1 = _nodeRadius1;
	nodePos2 = ofToString(roundf(_nodePos2.x)) + ", " + ofToString(roundf(_nodePos2.y));
	nodeVel2 = ofToString(roundf(_nodeVel2.x * 100) / 100) + ", " + ofToString(roundf(_nodeVel2.y * 100) / 100);
	nodeAccel2 = ofToString(roundf(_nodeAccel2.x * 10000) / 10000) + ", " + ofToString(roundf(_nodeAccel2.y * 10000) / 10000);
	nodeMass2 = _nodeMass2;
	nodeRadius2 = _nodeRadius2;
}

void guiController::windowResized(int w, int h) {
	selected_gui.setPosition(ofGetWidth() - 215, 10);
	multi_selection_gui.setPosition(ofGetWidth() - 215, 10);
}