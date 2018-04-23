#include "ofApp.h"
#include "engines\few_body.h"
#include "engines\many_body.h"

//--------------------------------------------------------------
void ofApp::setup() {
	state = SETUP;
	simulation = nullptr;

	submit.addListener(this, &ofApp::AddBody);

	setup_gui.setup();
	setup_gui.add(position.setup("position", 
		ofVec3f(0, 0, 0),
		ofVec3f(-screen_size*.5, -screen_size*.5, -screen_size*.5),
		ofVec3f(screen_size*.5, screen_size*.5, screen_size*.5)));
	setup_gui.add(velocity.setup("position",
		ofVec3f(0, 0, 0),
		ofVec3f(-screen_size*.25, -screen_size*.25, -screen_size*.25),
		ofVec3f(screen_size*.25, screen_size*.25, screen_size*.25)));
	setup_gui.add(mass.setup("mass", 0, 0, 10000000000000000000000000000000.0));
	setup_gui.add(body_color.setup("color", ofColor(50, 100, 150), 
		ofColor(0, 0, 0), ofColor(255, 255, 255)));
	setup_gui.add(submit.setup("submit"));
}

//--------------------------------------------------------------
void ofApp::update() {
	switch (state) {
	case SETUP:
		break;
	case RUNNING:
		break;
	case PAUSED:
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	switch (state) {
	case SETUP:
		setup_gui.draw();
		break;
	case RUNNING:
		break;
	case PAUSED:
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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

void ofApp::exit() {
	delete simulation;
}

void ofApp::AddBody() {
}