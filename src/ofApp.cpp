#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	GameObject* player = new Player;
	GameObjects->push_back(player);

	GameObject* spring = new Spring(ofVec2f(-150, 0), 0.4, 0.5, 0.5, 100);
	GameObject* spring2 = new Spring(ofVec2f(0, 0), 0.8, 0.2, 0.92, 0);
	GameObject* spring3 = new Spring(ofVec2f(150, 0), 2, 0.3, 0.8, 175);
	//GameObjects->push_back(spring);
	GameObjects->push_back(spring2);
	//GameObjects->push_back(spring3);
	
	GameController = new Controller;
	gui_Controller = new guiController;
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
		(*GameObjects)[i]->root_update(GameObjects, GameController, gui_Controller);
	}

	//gui_Controller->update();
	//gui_Controller->acceleration++;
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(/*30*/0);

	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	for (int i = 0; i < GameObjects->size(); i++) {
		(*GameObjects)[i]->root_draw();
	}
	ofPopMatrix();

	gui_Controller->gui.draw();
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
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	for (int i = 0; i < GameObjects->size(); i++) {
		(*GameObjects)[i]->mousePressed(x - ofGetWidth()/2, y - ofGetHeight()/2, button);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	for (int i = 0; i < GameObjects->size(); i++) {
		(*GameObjects)[i]->mouseReleased();
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
