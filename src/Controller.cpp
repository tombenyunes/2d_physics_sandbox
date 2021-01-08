#include "Controller.h"

Controller::Controller()
{
	GRAVITY = 0;
	OBJECT_SELECTED = false;
	MOUSE_BEING_DRAGGED = false;
	NEW_NODE_NAME = 0;

	activeObject = nullptr;
}

void Controller::setGravity(bool _value)
{
	(_value == 1) ? GRAVITY = 1 : GRAVITY = 0;
}

void Controller::makeActive(GameObject* _this)
{
	activeObject = _this;
}

GameObject* Controller::getActive()
{
	return activeObject;
}