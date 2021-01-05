#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	GameObject* player = new Player;
	GameObjects->push_back(player);

	GameObject* spring = new Spring(ofVec2f(0, 0), 0.8, 0.2, 0.92, 150);
	//GameObjects->push_back(spring);
	for (int i = 0; i < 10; i++) {
		GameObject* object = new Object(5, 17.5);
		GameObjects->push_back(object);
	}
	GameObject* object2 = new Object(100, 125);
	GameObjects->push_back(object2);
	
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

	if (draw_gui) {
		gui_Controller->gui.draw();
		if (GameController->OBJECT_SELECTED) {
			gui_Controller->gui2.draw();
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	for (int i = 0; i < GameObjects->size(); i++) {
		(*GameObjects)[i]->keyPressed(key);
	}
	if (key == 102) {
		(draw_gui) ? draw_gui = false : draw_gui = true;
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
