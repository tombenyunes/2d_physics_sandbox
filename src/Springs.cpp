#include "Springs.h"

Springs::Springs(ofVec2f _anchorPos, float _nodeRadius1, float _nodeMass1, float _nodeRadius2, float _nodeMass2, float _k, float _damping, float _springmass)
{
	pos.set(ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2), ofRandom(-ofGetHeight() / 2, ofGetHeight() / 2));
	color = ofColor(255);

	mouse_down_triggered = false;
	initiai_values_triggered = false;
	mouseOverNode1 = false;
	mouseOverNode2 = false;
	mouseOverAnchor = false;
	mouseDragNode1 = false;
	mouseDragNode2 = false;
	mouseDragAnchor = false;

	isSpring = true;

	gravity = 7;
	timeStep = 0.28;

	k = _k;
	damping = _damping;
	springmass = _springmass;

	pos = _anchorPos;
	radius = 8;
	
	nodePos1.set(pos);
	nodeVel1.set(0);
	nodeAccel1.set(0);
	nodeRadius1 = _nodeRadius1;
	nodeMass1 = _nodeMass1;

	nodePos2.set(pos);
	nodeVel2.set(0);
	nodeAccel2.set(0);
	nodeRadius2 = _nodeRadius2;
	nodeMass2 = _nodeMass2;

	AddModule("screenBounce");
	AddModule("ellipseCollider");
	AddModule("mouseHover");
}

ofVec2f Springs::updateSprings(int _node) {
	// Mass 1 Spring Force
	ofVec2f mass1SpringForce;
	mass1SpringForce.x = -k * (nodePos1.x - pos.x);
	mass1SpringForce.y = -k * (nodePos1.y - pos.y);

	// Mass 2 Spring Force
	ofVec2f mass2SpringForce;
	mass2SpringForce.x = -k * (nodePos2.x -
		nodePos1.x);
	mass2SpringForce.y = -k * (nodePos2.y -
		nodePos1.y);

	// Mass 1 Damping
	ofVec2f mass1DampingForce;
	mass1DampingForce.x = damping * nodeVel1.x;
	mass1DampingForce.y = damping * nodeVel1.y;

	// Mass 2 Damping
	ofVec2f mass2DampingForce;
	mass2DampingForce.x = damping * nodeVel2.x;
	mass2DampingForce.y = damping * nodeVel2.y;

	// Mass 1 Net Force
	ofVec2f mass1Force;
	mass1Force.x = mass1SpringForce.x -
		mass1DampingForce.x - mass2SpringForce.x + mass2DampingForce.x;
	mass1Force.y = mass1SpringForce.y +
		springmass * gravity - mass1DampingForce.y - mass2SpringForce.y +
		mass2DampingForce.y;

	// Mass 2 Net Force
	ofVec2f mass2Force;
	mass2Force.x = mass2SpringForce.x - mass2DampingForce.x;
	mass2Force.y = mass2SpringForce.y + springmass *
		gravity - mass2DampingForce.y;

	if (_node == 1) {
		return mass1Force / springmass;
	}
	else if (_node == 2) {
		return mass2Force / springmass;
	}
};

void Springs::ellipseCollider()
{
	for (int i = 0; i < GameObjects->size(); i++) {
		if ((*GameObjects)[i]->ellipseCollider_enabled) {
			if ((*GameObjects)[i] != this) {
				if (CollisionDetector->EllipseCompare(nodePos1, nodeRadius1, (*GameObjects)[i]->pos, (*GameObjects)[i]->radius)) {
					isColliding((*GameObjects)[i], 1);
				}
				if (CollisionDetector->EllipseCompare(nodePos2, nodeRadius2, (*GameObjects)[i]->pos, (*GameObjects)[i]->radius)) {
					isColliding((*GameObjects)[i], 2);
				}
			}
		}
	}
}

void Springs::mouseHover()
{
	if (CollisionDetector->EllipseCompare(nodePos1, nodeRadius1, ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2), 0)) {
		mouseOverNode1 = true;
	}
	else if (CollisionDetector->EllipseCompare(nodePos2, nodeRadius2, ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2), 0)) {
		mouseOverNode2 = true;
	}
	else if (CollisionDetector->EllipseCompare(pos, radius, ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2), 0)) {
		mouseOverAnchor = true;
	}
	else {
		color = ofColor(255);
		mouseOverNode1 = false;
		mouseOverNode2 = false;
		mouseOverAnchor = false;
	}
}

void Springs::isColliding(GameObject* _other, int _node)
{
	if (_node == 1) {
		ofVec2f forceVec = nodePos1 - _other->pos;
		ofVec2f accel = forceVec / nodeMass1;
		//nodeVel1 += accel;
		applyForce(accel, 1);
	}
	else if (_node == 2) {
		ofVec2f forceVec = nodePos2 - _other->pos;
		ofVec2f accel = forceVec / nodeMass2;
		//nodeVel2 += accel;
		applyForce(accel, 2);
	}
}

void Springs::dragNodes() 
{
	if (mouseDragNode1) {
		nodePos1.set(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2);
		nodeVel1.set(0);
	}
	else if (mouseDragNode2) {
		nodePos2.set(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2);
		nodeVel2.set(0);
	}
	else if (mouseDragAnchor) {
		pos.set(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2);
	}
}

void Springs::getNodeColor(int _node)
{
	if (_node == 1) {
		if (mouseOverNode1 || mouseDragNode1 == true) {
			ofSetColor(255, 0, 0);
		}
		else {
			ofSetColor(color);
		}
	}
	else if (_node == 2) {
		if (mouseOverNode2 || mouseDragNode2 == true) {
			ofSetColor(255, 0, 0);
		}
		else {
			ofSetColor(color);
		}
	}
	else if (_node == -1) {
		if (mouseOverAnchor || mouseDragAnchor == true) {
			ofSetColor(255, 0, 0);
		}
		else {
			ofSetColor(125);
		}
	}
}

void Springs::update()
{
	dragNodes();
	updateMovementForces();
}

void Springs::applyForce(ofVec2f _force, int _node)
{
	if (_node == 1) {
		nodeAccel1 += _force;
		//nodeVel1 += nodeAccel1;
	}
	else if (_node == 2) {
		nodeAccel2 += _force;
		//nodeVel2 += nodeAccel2;
	}
}

ofVec2f Springs::applyFriction(int _node)
{
	if (_node == 1) {
		friction = nodeVel1 * -1;
		friction *= FRICTION;
		return friction;
	}
	else if (_node == 2) {
		friction = nodeVel2 * -1;
		friction *= FRICTION;
		return friction;
	}
}

ofVec2f Springs::getAcceleration(int _node)
{
	// Adds friction to acceleration
	if (_node == 1) {
		applyForce(applyFriction(1), 1);
		applyForce(updateSprings(1) * timeStep, 1);
		return nodeAccel1;
	}
	else if (_node == 2) {
		applyForce(applyFriction(2), 2);
		applyForce(updateSprings(2) * timeStep, 2);
		return nodeAccel2;
	}
}

void Springs::updateMovementForces()
{
	nodeVel1 += getAcceleration(1);
	//nodeVel1.limit(MAXIMUM_VELOCITY);
	nodePos1 += nodeVel1 * timeStep;

	nodeVel2 += getAcceleration(2);
	//nodeVel2.limit(MAXIMUM_VELOCITY);
	nodePos2 += nodeVel2 * timeStep;
	
	if (GameController->activeObject == this) {
		updateGUI();
	}

	nodeAccel1.set(0);
	nodeAccel2.set(0);
}

void Springs::updateGUI()
{
	if (!initiai_values_triggered) {
		initiai_values_triggered = true;
		gui_Controller->updateValues(pos, vel, accel, mass, radius, 2);
	}
	else {
		gui_Controller->updateValues(pos, vel, accel, gui_Controller->mass2, gui_Controller->radius2, 2);
		mass = gui_Controller->mass2;
		radius = gui_Controller->radius2;
	}
	//mass = gui_Controller->mass;
}

void Springs::mousePressed(int _x, int _y, int _button)
{
	if (!mouse_down_triggered) {
		mouse_down_triggered = true;
		if (_button == 2 && (mouseOverNode1 || mouseOverNode2)) {
			if (GameController->activeObject != this) {
				initiai_values_triggered = false;
				GameController->makeActive(this);
			}
		}
	}
	if (_button == 2) {
		if (mouseOverNode1) {
			mouseDragNode1 = true;
			
		}
		else if (mouseOverNode2) {
			mouseDragNode2 = true;
		}
		else if (mouseOverAnchor) {
			mouseDragAnchor = true;
		}
	}
}

void Springs::mouseReleased(int _x, int _y, int _button)
{
	if (_button == 2) {
		if (mouse_down_triggered) {
			mouse_down_triggered = false;
		}
		if (mouseDragNode1 || mouseDragNode2 || mouseDragAnchor) {
			mouseDragNode1 = false;
			mouseDragNode2 = false;
			mouseDragAnchor = false;
		}
	}

}

void Springs::draw()
{
	ofPushStyle();

	ofNoFill();
	ofSetColor(color);
	ofSetLineWidth(ofMap(mass, 1, 100000, 0.1, 10));

	ofLine(nodePos1.x, nodePos1.y, pos.x, pos.y);
	ofLine(nodePos2.x, nodePos2.y, nodePos1.x, nodePos1.y);
	
	ofFill();
	getNodeColor(-1);
	ofEllipse(pos.x, pos.y, radius, radius);

	ofSetColor(0);
	ofEllipse(nodePos1.x, nodePos1.y, nodeRadius1, nodeRadius1);
	ofEllipse(nodePos2.x, nodePos2.y, nodeRadius2, nodeRadius2);

	ofNoFill();
	getNodeColor(1);
	ofEllipse(nodePos1.x, nodePos1.y, nodeRadius1, nodeRadius1);	
	
	getNodeColor(2);
	ofEllipse(nodePos2.x, nodePos2.y, nodeRadius2, nodeRadius2);
	
	ofPopStyle();
}