#pragma once

#include "ofMain.h"
#include "Controller.h"
#include "guiController.h"
#include "Collisions.h"

class GameObject {
	
public:

	GameObject(ofVec2f _pos = { 0, 0 }, ofColor _color = ofColor(255));

	void AddModule(string _id);

	void root_update(vector<GameObject*>* _gameobjects, Controller* _controller, guiController* _guiController, Collisions* _collisionDetector);
	virtual void update();

	virtual void isColliding(GameObject* _other, ofVec2f _nodePos = { 0, 0 });
	bool ellipseCollider_enabled;

	virtual void mousePressed(int _x, int _y, int _button);
	virtual void mouseDragged(int _x, int _y, int _button);
	virtual void mouseReleased(int _x, int _y, int _button);
	
	void root_keyPressed(int key);
	virtual void keyPressed(int key);
	void root_keyReleased(int key);
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
	ofVec2f prevPos;
	float radius;
	bool isSpring;
	bool isPlayer;

protected:

	// Base
	//ofVec2f pos;
	ofVec2f vel;
	ofVec2f accel;
	ofColor color;		
	//float radius;
	float mass;
	bool infiniteMass;
	bool affectedByGravity;

	// Modules
	bool screenWrap_enabled;
	bool screenBounce_enabled;
	bool gravity_enabled;
	
	bool mouseHover_enabled;

	bool deleteKeyDown;

	virtual void screenWrap();
	virtual void screenBounce();
	virtual void gravity();
	virtual void ellipseCollider();
	virtual void mouseHover();
	virtual void applyForce(ofVec2f& _accel, ofVec2f _force, bool _limit = true, float _limitAmount = MAXIMUM_ACCELERATION);
	virtual void addForces(bool _interpPos);
	virtual ofVec2f getInterpolatedPosition();

};