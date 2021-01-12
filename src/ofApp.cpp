#include "ofApp.h"

void ofApp::setup()
{
	GameController = new Controller;
	gui_Controller = new guiController;

	GameObject* player = new Player;
	GameObjects->push_back(player);

	Events.showTutorial(false);	// <----- enable or disable tutorial
	Events.setup();
}

void ofApp::update()
{	
	// erase objects that need to be deleted and free memory
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
		(*GameObjects)[i]->root_update(GameObjects, GameController, gui_Controller);
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
	ofBackground(0);
	ofSetCircleResolution(176); // must be a high resolution as the radius is flexible

	ofPushMatrix();

	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	for (int i = 0; i < GameObjects->size(); i++) (*GameObjects)[i]->root_draw();
	Events.draw();

	ofPopMatrix();

	drawRequiredGUI();
}

void ofApp::drawRequiredGUI() {
	if (GameController->getGUIVisible() || Events.playerGUIVisible) {
		gui_Controller->player_gui.draw();
		if (GameController->getActive() != nullptr) {
			if (GameController->getActive()->isSpring) {	// if an object is a spring then it has multiple gui windows to draw
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
	if (GameController->getNewNodeType() == 0) {
		GameObject* object = new Object(ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2), ofRandom(MASS_LOWER_BOUND, MASS_UPPER_BOUND), ofRandom(RADIUS_LOWER_BOUND, RADIUS_UPPER_BOUND), GameController);
		GameObjects->push_back(object);
	}
	else if (GameController->getNewNodeType() == 1) {
		GameObject* spring = new Springs(ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2), ofRandom(25, 50), ofRandom(25, 75), ofRandom(25, 50), ofRandom(25, 75), 2, 2, 22, GameController);
		GameObjects->push_back(spring);
	}
}

void ofApp::keyPressed(int key)
{
	Events.keyPressed(key);

	if ((Events.fullInput) || (Events.canKeypress)) {
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
	if ((Events.fullInput) || (Events.canKeypress)) {
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
	if ((Events.fullInput) || (button == 0 && Events.canLMB) || (button == 2 && Events.canDrag)) {
		for (int i = 0; i < GameObjects->size(); i++) {
			(*GameObjects)[i]->mouseDragged(x - ofGetWidth() / 2, y - ofGetHeight() / 2, button);
		}
		//if (button == 1) {
			//createNode();
		//}
	}
}

void ofApp::mousePressed(int x, int y, int button)
{
	if ((Events.fullInput) || (button == 0 && Events.canLMB) || (button == 2 && Events.canSelect)) {
		for (int i = 0; i < GameObjects->size(); i++) {
			(*GameObjects)[i]->mousePressed(x - ofGetWidth() / 2, y - ofGetHeight() / 2, button);
		}
		//if (button == 1) {
			//createNode();
		//}
	}
}

void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY)
{
	if ((Events.fullInput) || (Events.canKeypress)) { // use the scroll wheel to set the type of object you create
		if (scrollY == 1) {
			if (GameController->getNewNodeType() < 1) {
				GameController->setNewNodeType(GameController->getNewNodeType() + 1);
			}
			else {
				GameController->setNewNodeType(0);
			}
		}
		else if (scrollY == -1) {
			if (GameController->getNewNodeType() > 0) {
				GameController->setNewNodeType(GameController->getNewNodeType() - 1);
			}
			else {
				GameController->setNewNodeType(1);
			}
		}
	}
}

void ofApp::mouseReleased(int x, int y, int button)
{
	if ((Events.fullInput) || (button == 0 && Events.canLMB) || (button == 2 && Events.canSelect)) {
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