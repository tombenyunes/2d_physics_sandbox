#include "EventManager.h"

EventManager::EventManager()
{
	currentIndex = 0;
	PottaOne.load("PottaOne-Regular.ttf", 12, true, true);
	dialogues = {
		"hi",
		"you're new here aren't you?",
		"well, let me show you around",
		"this is you --->",
		"you can propell yourself by holding left click",
		"<--- here are some details about you",
		"watch your position, velocity, and acceleration update as your move around",
		"try changing your radius, and enabling gravity",
		"this is an orb --->",
		"try right clicking on it",
		"it, too, has properties you can see --->",
		"oh no, another orb has joined and isn't doing a good job of social distancing",
		"why don't you give it a caring nudge...",
		"notice how the small orb moved less than the larger orb, despite its size?",
		"that's because of it's mass",
		"the larger the mass, the harder it is to move, and the smaller the mass, the easier",
		"if you're not satisfied with how far you pushed it, you can try holding right click and giving it a throw",
		"now you might be thinking \"if only there was some way to support the masses so the don't just collapse under the pressure of gravity\"",
		"and no, i'm not talking about the furlough scheme",
		"i'm talking about springs",
		"by selecting a spring, you get to see the properties of all the nodes attached to it, along with settings affecting the spring --->",
		"anyway, that's all for now, have fun in sandbox mode",		
		"",
	};
	positions = {
		{ (float)(3.95 * (float)(dialogues[0].length()) * -1), -125 },
		{ (float)(3.95 * (float)(dialogues[1].length()) * -1), -125 },
		{ (float)(3.95 * (float)(dialogues[2].length()) * -1), -125 },
		{ -175, 6 },
		{ (float)(3.95 * (float)(dialogues[4].length()) * -1), 100 },
		{ -527, -424 },
		{ -527, -424 },
		{ -527, -424 },
		{ 34, 6 },
		{ 33, 200 },
		{ 371, -424 },
		{ -488, 121 },
		{ -85, 321 },
		{ -300, 6 },
		{ -125, 6 },
		{ -310, 6 },
		{ -450, 6 },
		{ -580, 6 },
		{ -220, 6 },
		{ -110, 6 },
		{ -398, -163 },
		{ (float)(3.95 * (float)(dialogues[4].length()) * -1), 6 },
		{ 0, 0 },
	};
	playerGUIVisible = false;
}

void EventManager::update(Controller* _controller, vector<GameObject*>* _gameobjects)
{
	GameController = _controller;

	static bool i0 = false;
	if (!i0) {
		i0 = true;
		GameController->setGUIVisible(false);
		GameController->setCanUserInput(false);
	}
	static bool i4 = false;
	if (currentIndex >= 4 && !i4) {
		i4 = true;
		GameController->setCanUserInput(true);
	}
	static bool i5 = false;
	if (currentIndex >=  5 && !i5) {
		i5 = true;
		playerGUIVisible = true;
	}
	static bool i8 = false;
	if (currentIndex >= 8 && !i8) {
		i8 = true;
		GameObject* object = new Object(ofVec2f(340, 0), 1000, 220, GameController);
		_gameobjects->push_back(object);
	}
	static bool i11 = false;
	if (currentIndex >= 11 && !i11) {
		i11 = true;
		GameObject* object = new Object(ofVec2f(294, 174), 4000, 115, GameController);
		_gameobjects->push_back(object);
	}
	static bool i19 = false;
	if (currentIndex >= 19 && !i19) {
		i19 = true;
		for (int i = 0; i < 30; i++) {
			GameObject* spring = new Springs(ofVec2f(ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2), ofRandom(-ofGetHeight() / 2, ofGetHeight() / 2)), ofRandom(25, 50), ofRandom(25, 75), ofRandom(25, 50), ofRandom(25, 75), 2, 2, 22, GameController);
			_gameobjects->push_back(spring);
		}
	}
	static bool i21 = false;
	if (currentIndex >= 21 && !i21) {
		i21 = true;
		GameController->setDeleteAll(true);
	}
	static bool i22 = false;
	if (currentIndex >= 22 && !i22) {
		i22 = true;
		GameController->setGUIVisible(true);
	}
}

void EventManager::draw()
{
	PottaOne.drawString(dialogues[currentIndex], positions[currentIndex].x, positions[currentIndex].y);
}

void EventManager::keyPressed(int _key)
{
	//if (GameController->getGUIVisible()) GameController->setGUIVisible(false);
	//else GameController->setGUIVisible(true);
	cout << ofGetMouseX() - ofGetWidth() / 2 << ", " << ofGetMouseY() - ofGetHeight() / 2 << endl;

	if (_key == 57356 && currentIndex != 0) {
		currentIndex--;
	}
	else if (_key == 57358 && currentIndex != dialogues.size()-1) {
		currentIndex++;
	}
}