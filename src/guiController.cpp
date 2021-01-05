#include "guiController.h"

guiController::guiController()
{
	gui.setup();
	
	gui.add(position.setup("pos", ofToString("Error: Values not updating") + ", " + ofToString("Error: Values not updating")));
	gui.add(velocity.setup("vel", ofToString("Error: Values not updating") + ", " + ofToString("Error: Values not updating")));
	gui.add(accel.setup("accel", ofToString("Error: Values not updating") + ", " + ofToString("Error: Values not updating")));

}

void guiController::update()
{
	
}

void guiController::updateValues(ofVec2f _pos, ofVec2f _vel, ofVec2f _accel)
{
	position = ofToString(roundf(_pos.x)) + ", " + ofToString(roundf(_pos.y));
	velocity = ofToString(roundf(_vel.x*100)/100) + ", " + ofToString(roundf(_vel.y*100)/100);
	accel = ofToString(roundf(_accel.x*10000)/10000) + ", " + ofToString(roundf(_accel.y*10000)/10000);
}