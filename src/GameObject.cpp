#include "GameObject.h"

GameObject::GameObject(ofVec2f _pos, ofColor _color)
{
	pos.set(_pos);
	color.set(_color);

	vel.set(0);
	accel.set(0);
	radius = 35;
	mass = 10;
	infiniteMass = false;

	needs_to_be_deleted = false;
	mouseOver = false;
	mouseOffsetFromCenter.set(0);
	active = false;

	isSpring = false;

	screenWrap_enabled = false;
	screenBounce_enabled = false;
	gravity_enabled = false;
	ellipseCollider_enabled = false;
	mouseHover_enabled = false;
}

void GameObject::root_update(vector<GameObject*>* _gameobjects, Controller* _controller, guiController* _guiController, Collisions* _collisionDetector)
{
	if (!needs_to_be_deleted) {

		GameObjects = _gameobjects;
		GameController = _controller;
		gui_Controller = _guiController;
		CollisionDetector = _collisionDetector;

		if (screenWrap_enabled) {
			screenWrap();
		}
		if (screenBounce_enabled) {
			screenBounce();
		}
		if (gravity_enabled) {
			gravity();
		}
		if (ellipseCollider_enabled) {
			ellipseCollider();
		}
		if (mouseHover_enabled) {
			mouseHover();
		}

		update();
	}
	else {
		//cout << "Error: 'Dead' GameObject is still being updated" << endl;
	}
}

void GameObject::update()
{
	static bool initialized = false;
	if (!initialized)
	{
		cout << "Error: User hasn't defined unique 'update' function for a GameObject" << endl;
		initialized = true;
	}
}

// ----- MODULES ----- //

void GameObject::screenWrap()
{
	if (pos.x > 0 + (ofGetWidth() / 2)) {
		pos.x = 0 - (ofGetWidth() / 2);
	}
	if (pos.x < 0 - (ofGetWidth() / 2)) {
		pos.x = 0 + (ofGetWidth() / 2);
	}
	if (pos.y < 0 - (ofGetHeight() / 2)) {
		pos.y = 0 + (ofGetHeight() / 2);
	}
	if (pos.y > 0 + (ofGetHeight() / 2)) {
		pos.y = 0 - (ofGetHeight() / 2);
	}
}

void GameObject::screenBounce()
{
	if (pos.x > 0 + (ofGetWidth() / 2) - (radius) / 2) {
		vel.x *= -1;
		pos.x = 0 + (ofGetWidth() / 2) - (radius) / 2;
	}
	if (pos.x < 0 - (ofGetWidth() / 2) + (radius) / 2) {
		vel.x *= -1;
		pos.x = 0 - (ofGetWidth() / 2) + (radius) / 2;
	}
	if (pos.y < 0 - (ofGetHeight() / 2) + (radius) / 2) {
		vel.y *= -1;
		pos.y = 0 - (ofGetHeight() / 2) + (radius) / 2;
	}
	if (pos.y > 0 + (ofGetHeight() / 2) - (radius) / 2) {
		vel.y *= -1;
		pos.y = 0 + (ofGetHeight() / 2) - (radius) / 2;
	}
}

void GameObject::gravity()
{
	if (GameController->GRAVITY == 1) {
		ofVec2f gravity = { 0, (float)GRAVITY_FORCE * mass };
		//applyForce(gravity, false);
		vel += gravity;
	}
}

void GameObject::ellipseCollider()
{
	for (int i = 0; i < GameObjects->size(); i++) {
		if ((*GameObjects)[i]->ellipseCollider_enabled) {
			if ((*GameObjects)[i] != this) {
				if ((*GameObjects)[i]->isSpring == false) {
					if (CollisionDetector->EllipseCompare(pos, radius, (*GameObjects)[i]->pos, (*GameObjects)[i]->radius)) {
						isColliding((*GameObjects)[i]);
					}
				}
			}
		}
	}
}

void GameObject::isColliding(GameObject* _other, ofVec2f _nodePos)
{
	if (!_other->isSpring) {
		ofVec2f forceVec = pos - _other->pos;
		applyForce(forceVec / mass);
	}
}

void GameObject::mouseHover()
{
	if (CollisionDetector->EllipseCompare(pos, radius, ofVec2f(ofGetMouseX()-ofGetWidth()/2, ofGetMouseY()-ofGetHeight()/2), 0)) {
		if (GameController->MOUSE_BEING_DRAGGED == false) {
			color = ofColor(255, 165, 0);
			mouseOver = true;
			mouseOffsetFromCenter = pos - ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2);
		}
	}
	else {
		color = ofColor(255);
		mouseOver = false;
		mouseOffsetFromCenter.set(0);
	}
}

void GameObject::AddModule(string _id)
{
	if (_id == "screenWrap") {
		//cout << "screenWrap module added" << endl;
		screenWrap_enabled = true;
	}
	else if (_id == "screenBounce") {
		//cout << "screenBounce module added" << endl;
		screenBounce_enabled = true;
	}
	else if (_id == "gravity") {
		//cout << "gravity module added" << endl;
		gravity_enabled = true;
	}
	else if (_id == "ellipseCollider") {
		//cout << "gravity module added" << endl;
		ellipseCollider_enabled = true;
	}
	else if (_id == "mouseHover") {
		//cout << "gravity module added" << endl;
		mouseHover_enabled = true;
	}
	else {
		cout << "Error: Module ID is invalid" << endl;
	}
}

void GameObject::applyForce(ofVec2f _force, bool _limitForce)
{
	accel += _force;
	if (_limitForce) {
		accel.limit(MAXIMUM_ACCELERATION);
	}
}


// ----- EVENT FUNCTIONS ----- //

void GameObject::mousePressed(int _x, int _y, int _button)
{
}

void GameObject::mouseReleased(int _x, int _y, int _button)
{
}

void GameObject::keyPressed(int key)
{
}

void GameObject::keyReleased(int key)
{
}


// ----- RENDER LOOP ----- //


void GameObject::root_draw()
{
	if (!needs_to_be_deleted) {
		draw();
	}
	else {
		//cout << "Error: 'Dead' GameObject is still being rendered" << endl;
	}
}

void GameObject::draw()
{
	static bool initialized = false;
	if (!initialized)
	{
		cout << "Error: User hasn't defined unique 'draw' function for a GameObject" << endl;
		initialized = true;
	}
}