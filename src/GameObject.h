#pragma once

#include "ofMain.h"

#define MAXIMUM_ACCELERATION 0.15
#define FRICTION 0.015

class GameObject {
	
public:

	GameObject(ofVec2f _pos = { 0, 0 }, ofColor _color = ofColor(255));

	void AddModule(string _id);

	void root_update(vector<GameObject*>* _gameobjects);
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

	bool needs_to_be_deleted;

protected:
	
	// Base
	ofVec2f pos;
	ofVec2f vel;
	ofVec2f accel;
	ofColor color;		
	float radius;

	// Events
	bool mouse_down;
	int mouse_button;
	ofVec2f mouse_pos;

	// Modules
	bool screenWrap_enabled;
	bool screenBounce_enabled;

private:

	// Modules
	void screenWrap();
	void screenBounce();

};