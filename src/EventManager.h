#pragma once

#include "Controller.h"
#include "GameObject.h"
#include "Object.h"
#include "Springs.h"

class EventManager
{

public:

	EventManager();
	void update(Controller* _controller, vector<GameObject*>* _gameobjects);
	void draw();
	void keyPressed(int _key);

	bool playerGUIVisible;

private:

	Controller* GameController;
	vector<string> dialogues;
	vector<ofVec2f> positions;
	int currentIndex;
	ofTrueTypeFont PottaOne;

};

