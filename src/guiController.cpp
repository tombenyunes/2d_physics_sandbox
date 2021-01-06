#include "guiController.h"

guiController::guiController()
{
	world_gui.setup("World");
	world_gui.add(gravity.setup("gravity", false));

	player_gui.setup("Player", "", 215, 10);	
	player_gui.add(position.setup("pos", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	player_gui.add(velocity.setup("vel", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	player_gui.add(accel.setup("accel", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	player_gui.add(mass.setup("mass", 404, 1, 100000));
	player_gui.add(radius.setup("radius", 404, 5, 300));

	selected_gui.setup("Selected Object", "", ofGetWidth()-215, 10);
	selected_gui.add(position2.setup("pos", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	selected_gui.add(velocity2.setup("vel", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	selected_gui.add(accel2.setup("accel", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	selected_gui.add(mass2.setup("mass", 404, 1, 100000));
	selected_gui.add(radius2.setup("radius", 404, 5, 300));

}

void guiController::update(Controller* _controller)
{
	_controller->setGravity(gravity);
}

void guiController::updateValues(ofVec2f _pos, ofVec2f _vel, ofVec2f _accel, float _mass, float _radius, int panel)
{
	if (panel == 1) {
		position = ofToString(roundf(_pos.x)) + ", " + ofToString(roundf(_pos.y));
		velocity = ofToString(roundf(_vel.x * 100) / 100) + ", " + ofToString(roundf(_vel.y * 100) / 100);
		accel = ofToString(roundf(_accel.x * 10000) / 10000) + ", " + ofToString(roundf(_accel.y * 10000) / 10000);
		mass = _mass;
		radius = _radius;
	}
	else if (panel == 2) {
		position2 = ofToString(roundf(_pos.x)) + ", " + ofToString(roundf(_pos.y));
		velocity2 = ofToString(roundf(_vel.x * 100) / 100) + ", " + ofToString(roundf(_vel.y * 100) / 100);
		accel2 = ofToString(roundf(_accel.x * 10000) / 10000) + ", " + ofToString(roundf(_accel.y * 10000) / 10000);
		mass2 = _mass;
		radius2 = _radius;
	}
	
	
}

void guiController::windowResized(int w, int h) {
	selected_gui.setPosition(ofGetWidth() - 215, 10);
}