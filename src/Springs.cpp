#include "Springs.h"

Springs::Springs(ofVec2f _anchorPos, int _anchorRadius, float _k, float _damping, float _springmass)
{
	pos.set(ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2), ofRandom(-ofGetHeight() / 2, ofGetHeight() / 2));
	color = ofColor(255);

	mouse_down_triggered = false;
	initiai_values_triggered = false;

	isSpring = true;

	gravity = 7;
	timeStep = 0.28;

	k = _k;
	damping = _damping;
	springmass = _springmass;
	pos = _anchorPos;
	radius = _anchorRadius;
	
	nodePos1.set(pos);
	nodeVel1.set(0);
	nodeAccel1.set(0);

	nodePos2.set(pos);
	nodeVel2.set(0);
	nodeAccel2.set(0);

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

	// Mass 1 Acceleration
	//ofVec2f mass1Acceleration;
	//mass1Acceleration.x = mass1Force.x / springmass;
	//mass1Acceleration.y = mass1Force.y / springmass;
	//nodeAccel1.x = mass1Force.x / springmass;
	//nodeAccel1.y = mass1Force.y / springmass;

	if (_node == 1) {
		return mass1Force / springmass;
	}
	else if (_node == 2) {
		return mass2Force / springmass;
	}

	// Mass 2 Acceleration
	//ofVec2f mass2Acceleration;
	//mass2Acceleration.x = mass2Force.x / springmass;
	//mass2Acceleration.y = mass2Force.y / springmass;
	//nodeAccel2.x = mass2Force.x / springmass;
	//nodeAccel2.y = mass2Force.y / springmass;

	// Anchor Acceleration
	//ofVec2f anchorAcceleration;
	//anchorAcceleration.x = mass2Force.x / springmass;
	//anchorAcceleration.y = mass2Force.y / springmass;

	// Mass 1 Velocity
	//nodeVel1.x = nodeVel1.x +
		//nodeAccel1.x * timeStep;
	//nodeVel1.y = nodeVel1.y +
		//nodeAccel1.y * timeStep;

	// Mass 2 Velocity
	//nodeVel2.x = nodeVel2.x +
		//nodeAccel2.x * timeStep;
	//nodeVel2.y = nodeVel2.y +
		//nodeAccel2.y * timeStep;

	// Anchor Velocity
	//anchorVel.x = anchorVel.x +
	//	anchorAcceleration.x * timeStep;
	//anchorVel.y = anchorVel.y +
	//	anchorAcceleration.y * timeStep;

	// Mass 1 Position
	//nodePos1.x = nodePos1.x +
		//nodeVel1.x * timeStep;
	//nodePos1.y = nodePos1.y +
		//nodeVel1.y * timeStep;

	// Mass 2 Position
	//nodePos2.x = nodePos2.x +
		//nodeVel2.x * timeStep;
	//nodePos2.y = nodePos2.y +
		//nodeVel2.y * timeStep;

	// Anchor Position
	//anchorPos.x = anchorPos.x +
	//	anchorVel.x * timeStep;
	//anchorPos.y = anchorPos.y +
	//	anchorVel.y * timeStep;
};

void Springs::ellipseCollider()
{
	for (int i = 0; i < GameObjects->size(); i++) {
		if ((*GameObjects)[i]->ellipseCollider_enabled) {
			if ((*GameObjects)[i] != this) {
				if (CollisionDetector->EllipseCompare(nodePos1, springmass, (*GameObjects)[i]->pos, (*GameObjects)[i]->radius)) {
					isColliding((*GameObjects)[i], 1);
				}
				if (CollisionDetector->EllipseCompare(nodePos2, springmass, (*GameObjects)[i]->pos, (*GameObjects)[i]->radius)) {
					isColliding((*GameObjects)[i], 2);
				}
				if (CollisionDetector->EllipseCompare(pos , springmass / 2, (*GameObjects)[i]->pos, (*GameObjects)[i]->radius)) {
					isColliding((*GameObjects)[i], 3);
				}
			}
		}
	}
}

void Springs::mouseHover()
{
	if (CollisionDetector->EllipseCompare(nodePos1, springmass, ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2), 0)) {
		color = ofColor(255, 0, 0);
		mouseOver1 = true;
	}
	else if (CollisionDetector->EllipseCompare(nodePos2, springmass, ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2), 0)) {
		color = ofColor(255, 0, 0);
		mouseOver2 = true;
	}
	else {
		color = ofColor(255);
		mouseOver1 = false;
		mouseOver2 = false;
	}
}

void Springs::isColliding(GameObject* _other, int _node) {
	if (_node == 1) {
		ofVec2f forceVec = nodePos1 - _other->pos;
		ofVec2f accel = forceVec / mass;
		nodeVel1 += accel;
		//applyForce(accel, 1);
	}
	else if (_node == 2) {
		ofVec2f forceVec = nodePos2 - _other->pos;
		ofVec2f accel = forceVec / mass;
		nodeVel2 += accel;
		//applyForce(accel, 2);
	}
}

void Springs::update()
{
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
		applyForce(updateSprings(1)*0.14, 1);
		return nodeAccel1.limit(MAXIMUM_ACCELERATION);
	}
	else if (_node == 2) {
		applyForce(applyFriction(2), 2);
		applyForce(updateSprings(2)*0.14, 2);
		return nodeAccel2.limit(MAXIMUM_ACCELERATION);
	}
}

void Springs::updateMovementForces()
{
	nodeVel1 += getAcceleration(1);
	nodeVel1.limit(MAXIMUM_VELOCITY);
	nodePos1 += nodeVel1;

	nodeVel2 += getAcceleration(2);
	nodeVel2.limit(MAXIMUM_VELOCITY);
	nodePos2 += nodeVel2;
	
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
		if (_button == 2 && (mouseOver1 || mouseOver2)) {

			if (GameController->activeObject == this) {
				GameController->makeActive(nullptr);
			}
			else {
				initiai_values_triggered = false;
				GameController->makeActive(this);
			}

		}
	}
}

void Springs::mouseReleased(int _x, int _y, int _button)
{
	if (_button == 2 && mouse_down_triggered) {
		mouse_down_triggered = false;
	}
}

void Springs::draw()
{
	ofPushStyle();

	if (GameController->activeObject == this) {
		color = ofColor(255, 0, 0);
	}
	else if (!mouseOver1 && !mouseOver2) {
		color = ofColor(255);
	}
	ofNoFill();
	ofSetColor(color);
	ofSetLineWidth(ofMap(mass, 1, 100000, 0.1, 10));

	//ofEllipse(pos.x, pos.y, radius, radius);

	ofLine(nodePos1.x, nodePos1.y, pos.x, pos.y);
	ofLine(nodePos2.x, nodePos2.y, nodePos1.x, nodePos1.y);
	
	ofFill();
	ofSetColor(125);
	ofEllipse(pos.x, pos.y, 6, 6);

	ofSetColor(0);
	ofEllipse(nodePos1.x, nodePos1.y, springmass, springmass);
	ofEllipse(nodePos2.x, nodePos2.y, springmass, springmass);

	ofNoFill();
	ofSetColor(color);
	ofEllipse(nodePos1.x, nodePos1.y, springmass, springmass);
	ofEllipse(nodePos2.x, nodePos2.y, springmass, springmass);
	
	ofPopStyle();
}