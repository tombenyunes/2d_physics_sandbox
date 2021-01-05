#pragma once

#include "ofMain.h"
#include "Controller.h"
#include "guiController.h"

#define MAXIMUM_ACCELERATION 0.15
#define MAXIMUM_VELOCITY 15
#define FRICTION 0.015
#define GRAVITY_FORCE 0.05

class GameObject {
	
public:

	GameObject(ofVec2f _pos = { 0, 0 }, ofColor _color = ofColor(255));

	void AddModule(string _id);

	void root_update(vector<GameObject*>* _gameobjects, Controller* _controller, guiController* _guiController);
	virtual void update();

	// Event functions
	virtual void mousePressed(int _x, int _y, int _button);
	virtual void mouseReleased();
	virtual void keyPressed(int key);
	virtual void keyReleased(int key);

	// Render loop
	void root_draw();
	virtual void draw();

	vector<GameObject*>* GameObjects;
	Controller* GameController;
	guiController* gui_Controller;

	bool needs_to_be_deleted;

protected:
	
	// Base
	ofVec2f pos;
	ofVec2f vel;
	ofVec2f accel;
	ofColor color;		
	float radius;

	// Modules
	bool screenWrap_enabled;
	bool screenBounce_enabled;
	bool gravity_enabled;

private:

	// Modules
	void screenWrap();
	void screenBounce();
	void gravity();

};