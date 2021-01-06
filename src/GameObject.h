#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "ofMain.h"
#include "Controller.h"
#include "guiController.h"
#include "Collisions.h"


#define MAXIMUM_ACCELERATION 0.15
#define MAXIMUM_VELOCITY 15
#define FRICTION 0.015
#define GRAVITY_FORCE 0.01

class GameObject {
	
public:

	GameObject(ofVec2f _pos = { 0, 0 }, ofColor _color = ofColor(255));

	void AddModule(string _id);

	void root_update(vector<GameObject*>* _gameobjects, Controller* _controller, guiController* _guiController, Collisions* _collisionDetector);
	virtual void update();
	virtual void ellipseCollider();

	virtual void isColliding(GameObject* _other);
	bool ellipseCollider_enabled;

	// Event functions
	virtual void mousePressed(int _x, int _y, int _button);
	virtual void mouseReleased(int _x, int _y, int _button);
	virtual void keyPressed(int key);
	virtual void keyReleased(int key);

	// Render loop
	void root_draw();
	virtual void draw();

	vector<GameObject*>* GameObjects;
	Controller* GameController;
	guiController* gui_Controller;
	Collisions* CollisionDetector;

	bool needs_to_be_deleted;
	bool mouseOver;
	bool active;

	ofVec2f pos;
	float radius;
	int node;

protected:

	// Base
	//ofVec2f pos;
	ofVec2f vel;
	ofVec2f accel;
	ofColor color;		
	//float radius;
	float mass;

	// Modules
	bool screenWrap_enabled;
	bool screenBounce_enabled;
	bool gravity_enabled;
	
	bool mouseHover_enabled;

private:

	// Modules
	void screenWrap();
	void screenBounce();
	void gravity();
	/*void ellipseCollider();*/
	void mouseHover();

};

#endif