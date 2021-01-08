#pragma once

#include "ofMain.h"
#include "Controller.h"
#include "guiController.h"
#include "Collisions.h"


#define MAXIMUM_ACCELERATION 0.15 // 0.15
#define MAXIMUM_VELOCITY 100 // 15
#define FRICTION_FORCE 0.015
#define GRAVITY_FORCE 0.01

class GameObject {
	
public:

	GameObject(ofVec2f _pos = { 0, 0 }, ofColor _color = ofColor(255));

	void AddModule(string _id);

	void root_update(vector<GameObject*>* _gameobjects, Controller* _controller, guiController* _guiController, Collisions* _collisionDetector);
	virtual void update();

	virtual void isColliding(GameObject* _other, ofVec2f _nodePos = { 0, 0 });
	bool ellipseCollider_enabled;

	virtual void mousePressed(int _x, int _y, int _button);
	virtual void mouseReleased(int _x, int _y, int _button);
	virtual void keyPressed(int key);
	virtual void keyReleased(int key);

	void root_draw();
	virtual void draw();

	vector<GameObject*>* GameObjects;
	Controller* GameController;
	guiController* gui_Controller;
	Collisions* CollisionDetector;

	bool needs_to_be_deleted;
	bool mouseOver;
	ofVec2f mouseOffsetFromCenter;
	bool active;

	ofVec2f pos;
	float radius;
	bool isSpring;

protected:

	// Base
	//ofVec2f pos;
	ofVec2f vel;
	ofVec2f accel;
	ofColor color;		
	//float radius;
	float mass;
	bool infiniteMass;

	// Modules
	bool screenWrap_enabled;
	bool screenBounce_enabled;
	bool gravity_enabled;
	
	bool mouseHover_enabled;

	virtual void applyForce(ofVec2f _force, bool _limitForce = true);
	virtual void screenWrap();
	virtual void screenBounce();
	virtual void gravity();
	virtual void ellipseCollider();
	virtual void mouseHover();

};