#include "ofApp.h"

void ofApp::setup()
{
	GameController = new Controller;
	gui_Controller = new guiController;
	CollisionDetector = new Collisions;

	GameObject* player = new Player;
	GameObjects->push_back(player);

	//GameObject* spring = new Spring(ofVec2f(0, 0), 0.8, 0.2, 0.92, 150);
	//GameObjects->push_back(spring);
	//for (int i = 0; i < 2; i++) {
		//GameObject* object = new Object(ofVec2f(ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2), ofRandom(-ofGetHeight() / 2, ofGetHeight() / 2)), ofRandom(1, 250), ofRandom(10, 300));
		//GameObjects->push_back(object);
	//}
	
	//GameObject* spring1 = new Springs(ofVec2f(-100, 0), 35, 22, 35, 22, 2, 2, 22);
	//GameObject* spring2 = new Springs(ofVec2f(100, 0), 35, 22, 35, 22, 2, 2, 22);
	//GameObjects->push_back(spring1);
	//GameObjects->push_back(spring2);
}

void ofApp::update()
{
	// erase objects that need to be deleted
	for (int i = 0; i < GameObjects->size(); i++) {
		if ((*GameObjects)[i]->needs_to_be_deleted == true) {
			if ((*GameObjects)[i] == GameController->getActive()) {
				GameController->makeActive(nullptr);
			}
			delete (*GameObjects)[i];
			GameObjects->erase(GameObjects->begin() + i);
		}
	}
	// update all gameobjects
	for (int i = 0; i < GameObjects->size(); i++) {
		(*GameObjects)[i]->root_update(GameObjects, GameController, gui_Controller, CollisionDetector);
	}

	gui_Controller->update(GameController);
	Events.update(GameController, GameObjects);

	if (GameController->getDeleteAll()) {
		GameController->setDeleteAll(false);
		for (int i = 0; i < GameObjects->size(); i++) {
			if ((*GameObjects)[i]->isPlayer != true) {
				(*GameObjects)[i]->needs_to_be_deleted = true;
			}
		}
	}
}

void ofApp::draw()
{
	ofBackground(/*30*/0);
	ofSetCircleResolution(176);

	ofPushMatrix();

	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	for (int i = 0; i < GameObjects->size(); i++) {
		(*GameObjects)[i]->root_draw();
	}

	Events.draw();

	ofPopMatrix();

	if (GameController->getGUIVisible() || Events.playerGUIVisible) {
		gui_Controller->player_gui.draw();
		if (GameController->getActive() != nullptr) {
			if (GameController->getActive()->isSpring) {
				gui_Controller->multi_selection_gui_anchor.draw();
				gui_Controller->multi_selection_gui_node1.draw();
				gui_Controller->multi_selection_gui_node2.draw();
				gui_Controller->multi_selection_gui_spring.draw();
			}
			else {
				gui_Controller->selected_gui.draw();
			}
		}
	}
	if (GameController->getGUIVisible()) {
		gui_Controller->world_gui.draw();
		gui_Controller->create_node_gui.draw();
	}
}

void ofApp::createNode()
{
	if (GameController->getNewNodeName() == 0) {
		GameObject* object = new Object(ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2), ofRandom(MASS_LOWER_BOUND, MASS_UPPER_BOUND), ofRandom(RADIUS_LOWER_BOUND, RADIUS_UPPER_BOUND), GameController);
		GameObjects->push_back(object);
	}
	else if (GameController->getNewNodeName() == 1) {
		GameObject* spring = new Springs(ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2), ofRandom(25, 50), ofRandom(25, 75), ofRandom(25, 50), ofRandom(25, 75), 2, 2, 22, GameController);
		GameObjects->push_back(spring);
	}
}

void ofApp::keyPressed(int key)
{
	Events.keyPressed(key);

	if (GameController->getCanUserInput()) {
		for (int i = 0; i < GameObjects->size(); i++) {
			(*GameObjects)[i]->root_keyPressed(key);
		}
		if (key == 99) {
			createNode();
		}
	}
}

void ofApp::keyReleased(int key)
{
	if (GameController->getCanUserInput()) {
		for (int i = 0; i < GameObjects->size(); i++) {
			(*GameObjects)[i]->root_keyReleased(key);
		}
	}
}

void ofApp::mouseMoved(int x, int y )
{

}
 
void ofApp::mouseDragged(int x, int y, int button)
{
	if (GameController->getCanUserInput()) {
		for (int i = 0; i < GameObjects->size(); i++) {
			//(*GameObjects)[i]->mousePressed(x - ofGetWidth() / 2, y - ofGetHeight() / 2, button);
			(*GameObjects)[i]->mouseDragged(x - ofGetWidth() / 2, y - ofGetHeight() / 2, button);
		}
		if (button == 1) {
			createNode();
		}
	}
}

void ofApp::mousePressed(int x, int y, int button)
{
	if (GameController->getCanUserInput()) {
		for (int i = 0; i < GameObjects->size(); i++) {
			(*GameObjects)[i]->mousePressed(x - ofGetWidth() / 2, y - ofGetHeight() / 2, button);
		}
		if (button == 1) {
			createNode();
		}
	}
}

void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY)
{
	if (GameController->getCanUserInput()) {
		if (scrollY == 1) {
			if (GameController->getNewNodeName() < 1) {
				GameController->setNewNodeName(GameController->getNewNodeName() + 1);
			}
			else {
				GameController->setNewNodeName(0);
			}
		}
		else if (scrollY == -1) {
			if (GameController->getNewNodeName() > 0) {
				GameController->setNewNodeName(GameController->getNewNodeName() - 1);
			}
			else {
				GameController->setNewNodeName(1);
			}
		}
	}
}

void ofApp::mouseReleased(int x, int y, int button)
{
	if (GameController->getCanUserInput()) {
		for (int i = 0; i < GameObjects->size(); i++) {
			(*GameObjects)[i]->mouseReleased(x - ofGetWidth() / 2, y - ofGetHeight() / 2, button);
		}
	}
}

void ofApp::mouseEntered(int x, int y)
{

}

void ofApp::mouseExited(int x, int y)
{

}

void ofApp::windowResized(int w, int h)
{
	gui_Controller->windowResized(w, h);
}

void ofApp::gotMessage(ofMessage msg)
{

}

void ofApp::dragEvent(ofDragInfo dragInfo)
{

}