#pragma once

#include "ofMain.h"
#include "GameObject.h"
#include "Controller.h"
#include "Player.h"
#include "Spring.h"
#include "Object.h"
#include "Springs.h"

#include "ofxGui.h"
#include "guiController.h"
#include "Collisions.h"
#include "EventManager.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void createNode();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseScrolled(int x, int y, float scrollX, float scrollY);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		vector <GameObject*> vec;
		vector <GameObject*>* GameObjects = &vec;

		Controller* GameController;
		guiController* gui_Controller;
		EventManager Events;

		Collisions* CollisionDetector;

};