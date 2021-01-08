#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	GameObject* player = new Player;
	GameObjects->push_back(player);

	GameObject* spring = new Spring(ofVec2f(0, 0), 0.8, 0.2, 0.92, 150);
	//GameObjects->push_back(spring);
	for (int i = 0; i < 2; i++) {
		GameObject* object = new Object(ofVec2f(ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2), ofRandom(-ofGetHeight() / 2, ofGetHeight() / 2)), ofRandom(1, 250), ofRandom(10, 300));
		GameObjects->push_back(object);
	}
	
	GameObject* spring1 = new Springs(ofVec2f(-100, 0), 35, 22, 35, 22, 2, 2, 22);
	GameObject* spring2 = new Springs(ofVec2f(100, 0), 35, 22, 35, 22, 2, 2, 22);
	//GameObjects->push_back(spring1);
	//GameObjects->push_back(spring2);
	
	GameController = new Controller;
	gui_Controller = new guiController;

	CollisionDetector = new Collisions;
}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < GameObjects->size(); i++) {
		if ((*GameObjects)[i]->needs_to_be_deleted == true) {
			GameObjects->erase(GameObjects->begin() + i);
			//delete (*GameObjects)[i];
		}
	}

	for (int i = 0; i < GameObjects->size(); i++) {
		(*GameObjects)[i]->root_update(GameObjects, GameController, gui_Controller, CollisionDetector);
	}

	gui_Controller->update(GameController);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(/*30*/0);
	ofSetCircleResolution(176);

	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	for (int i = 0; i < GameObjects->size(); i++) {
		(*GameObjects)[i]->root_draw();
	}
	ofPopMatrix();

	if (draw_gui) {
		gui_Controller->world_gui.draw();
		gui_Controller->create_node_gui.draw();
		gui_Controller->player_gui.draw();
		if (GameController->activeObject != nullptr) {
			if (GameController->activeObject->isSpring) {
				gui_Controller->multi_selection_gui.draw();
			}
			else {
				gui_Controller->selected_gui.draw();
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	for (int i = 0; i < GameObjects->size(); i++) {
		(*GameObjects)[i]->keyPressed(key);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	for (int i = 0; i < GameObjects->size(); i++) {
		(*GameObjects)[i]->keyReleased(key);
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}
 
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	for (int i = 0; i < GameObjects->size(); i++) {
		(*GameObjects)[i]->mousePressed(x - ofGetWidth() / 2, y - ofGetHeight() / 2, button);
	}
	if (button == 1) {
		if (GameController->NEW_NODE_NAME == 0) {
			GameObject* object = new Object(ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2), ofRandom(1, 50), ofRandom(10, 300));
			GameObjects->push_back(object);
		}
		else if (GameController->NEW_NODE_NAME == 1) {
			GameObject* spring = new Springs(ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2), 35, 22, 35, 22, 2, 2, 22);
			GameObjects->push_back(spring);
		}
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	for (int i = 0; i < GameObjects->size(); i++) {
		(*GameObjects)[i]->mousePressed(x - ofGetWidth() / 2, y - ofGetHeight() / 2, button);
	}
	if (button == 1) {
		if (GameController->NEW_NODE_NAME == 0) {
			GameObject* object = new Object(ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2), ofRandom(1, 50), ofRandom(10, 300));
			GameObjects->push_back(object);
		}
		else if (GameController->NEW_NODE_NAME == 1) {
			GameObject* spring = new Springs(ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2), 35, 22, 35, 22, 2, 2, 22);
			GameObjects->push_back(spring);
		}
	}
}

void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){
	if (scrollY == 1) {
		if (GameController->NEW_NODE_NAME < 1) {
			GameController->NEW_NODE_NAME++;
		}
		else {
			GameController->NEW_NODE_NAME = 0;
		}
	}
	else if (scrollY == -1) {
		if (GameController->NEW_NODE_NAME > 0) {
			GameController->NEW_NODE_NAME--;
		}
		else {
			GameController->NEW_NODE_NAME = 1;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	for (int i = 0; i < GameObjects->size(); i++) {
		(*GameObjects)[i]->mouseReleased(x - ofGetWidth()/2, y - ofGetHeight()/2, button);
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	gui_Controller->windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
