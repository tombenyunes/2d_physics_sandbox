#include "guiController.h"

guiController::guiController()
{
	gui.setup("Player");	
	gui.add(position.setup("pos", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	gui.add(velocity.setup("vel", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	gui.add(accel.setup("accel", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));

	gui2.setup("Selected Object", "", ofGetWidth()-215, 10);
	gui2.add(position2.setup("pos", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	gui2.add(velocity2.setup("vel", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));
	gui2.add(accel2.setup("accel", ofToString("Error: Updating failed") + ", " + ofToString("Error: Updating failed")));

}

void guiController::update()
{
	
}

void guiController::updateValues(ofVec2f _pos, ofVec2f _vel, ofVec2f _accel, bool active)
{
	if (!active) {
		position = ofToString(roundf(_pos.x)) + ", " + ofToString(roundf(_pos.y));
		velocity = ofToString(roundf(_vel.x * 100) / 100) + ", " + ofToString(roundf(_vel.y * 100) / 100);
		accel = ofToString(roundf(_accel.x * 10000) / 10000) + ", " + ofToString(roundf(_accel.y * 10000) / 10000);
	}
	else {
		position2 = ofToString(roundf(_pos.x)) + ", " + ofToString(roundf(_pos.y));
		velocity2 = ofToString(roundf(_vel.x * 100) / 100) + ", " + ofToString(roundf(_vel.y * 100) / 100);
		accel2 = ofToString(roundf(_accel.x * 10000) / 10000) + ", " + ofToString(roundf(_accel.y * 10000) / 10000);
	}
}