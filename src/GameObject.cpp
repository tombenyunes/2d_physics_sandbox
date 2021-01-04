#include "GameObject.h"

GameObject::GameObject(ofVec2f _pos, ofColor _color)
{
	pos.set(_pos);
	color.set(_color);

	vel.set(0);
	accel.set(0);
	radius = 35;
	
	needs_to_be_deleted = false;

	mouse_down = false;
	mouse_button = -1;

	screenWrap_enabled = false;
	screenBounce_enabled = false;
}

void GameObject::screenWrap() {
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

void GameObject::screenBounce() {
	if (pos.x > 0 + (ofGetWidth() / 2)) {
		vel.x *= -1;
	}
	if (pos.x < 0 - (ofGetWidth() / 2)) {
		vel.x *= -1;
	}
	if (pos.y < 0 - (ofGetHeight() / 2)) {
		vel.y *= -1;
	}
	if (pos.y > 0 + (ofGetHeight() / 2)) {
		vel.y *= -1;
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
	else {
		cout << "Error: Module ID is invalid" << endl;
	}
}

void GameObject::root_update(vector<GameObject*>* _gameobjects)
{
	if (!needs_to_be_deleted) {
		GameObjects = _gameobjects;

		if (screenWrap_enabled) {
			screenWrap();
		}
		if (screenBounce_enabled) {
			screenBounce();
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

// ----- EVENT FUNCTIONS ----- //

void GameObject::mousePressed(int _x, int _y, int _button)
{
	mouse_down = true;
	mouse_button = _button;
	mouse_pos = { (float)_x, (float)_y };
}

void GameObject::mouseReleased()
{
	mouse_down = false;
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