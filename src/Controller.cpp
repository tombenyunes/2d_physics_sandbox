#include "Controller.h"

Controller::Controller()
{
	GRAVITY = 0;
}

void Controller::invertGravity()
{
	(GRAVITY == 0) ? GRAVITY = 1 : GRAVITY = 0;
}
