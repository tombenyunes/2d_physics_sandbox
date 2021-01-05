#pragma once

#include "ofMain.h"
#include "GameObject.h"
#include "Controller.h"
#include "Player.h"

#include "ofxGui.h"
#include "guiController.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
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

};
