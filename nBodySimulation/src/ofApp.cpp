#include "ofApp.h"
#include "engines\few_body.h"
#include "engines\many_body.h"

//--------------------------------------------------------------
void ofApp::setup() {
	state = SETUP;
	simulation = new FewBodyEngine(0.01);
	body_count = 0;
	ofSetBackgroundColor(20, 20, 20);

	SetupGui();
	light.setup();
	light.setPointLight();

	camera.setDistance(100);
}

//--------------------------------------------------------------
void ofApp::update() {
	static int i = 0;
	switch (state) {
	case SETUP:
		break;
	case RUNNING: {
		++i;
		simulation->update();
		if (i % 100 == 0) {
			auto positions = simulation->GetBodyPositions();
			for (auto i : positions) {
				cout << i << endl;
			}
		}
		}
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
		light.enable();
		DrawSetupBodies();
		DrawGui();
		break;
	case RUNNING:
		camera.begin();
		DrawSimulationBodies();
		camera.end();
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
	// Get the data from the sliders
	ofVec3f position = position_slider;
	ofVec3f velocity = velocity_slider;
	double mass = mass_slider;
	ofColor color = color_slider;

	// Add the body to a simulation
	simulation->AddBody(position, velocity, mass);

	// Map the position of the body in the vector to a specific color
	body_color.push_back(color);

	// Create a new sphere
	ofSpherePrimitive sphere;
	sphere.setRadius(75);
	body_spheres.push_back(sphere);

	body_count++;
}

void ofApp::SetupGui() {
	add_button.addListener(this, &ofApp::AddBody);

	setup_gui.setup("Bodies", "../data/setup.xml");

	setup_gui.add(position_slider.setup("position",
		ofVec3f(0, 0, 0),
		ofVec3f(-screen_size*.5, -screen_size*.5, -screen_size*.5),
		ofVec3f(screen_size*.5, screen_size*.5, screen_size*.5)));

	setup_gui.add(velocity_slider.setup("velocity",
		ofVec3f(0, 0, 0),
		ofVec3f(-screen_size*.25, -screen_size*.25, -screen_size*.25),
		ofVec3f(screen_size*.25, screen_size*.25, screen_size*.25)));

	setup_gui.add(mass_slider.setup("mass", 10, 1, 1000000));

	setup_gui.add(color_slider.setup("color", ofColor(50, 100, 150),
		ofColor(0, 0, 0), ofColor(255, 255, 255)));

	setup_gui.add(add_button.setup("add"));


	run_button.addListener(this, &ofApp::RunSimulation);

	run_gui.setup("run");
	run_gui.add(run_button.setup("start simulation"));
	run_gui.setPosition(10, setup_gui.getHeight()*1.1);
}

void ofApp::DrawSetupBodies() {
	double offset = (double)ofGetWidth() / ((double)body_spheres.size() + 1);
	double x = offset;
	for (int i = 0; i < body_spheres.size(); i++) {
		body_spheres[i].setPosition(x, ofGetHeight()*.6, 0);
		x += offset;

		body_spheres[i].rotate(ofGetElapsedTimef() * 75, 0.15, 1.0, 0.0);

		ofPushStyle();
		ofSetColor(body_color[i]);
		body_spheres[i].drawWireframe();
		ofPopStyle();
	}
}

void ofApp::DrawGui() {
	switch (state) {
	case SETUP:
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		position_slider.draw();
		velocity_slider.draw();
		mass_slider.draw();
		color_slider.draw();
		add_button.draw();
		setup_gui.draw();

		run_button.draw();
		run_gui.draw();

		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
	}
}

void ofApp::RunSimulation() {
	state = RUNNING;
}

void ofApp::DrawSimulationBodies() {
	vector<ofVec3f> positions = simulation->GetBodyPositions();
	for (int i = 0; i < body_spheres.size(); i++) {
		body_spheres[i].setPosition(positions[i]);

		//body_spheres[i].rotate(ofGetElapsedTimef() * 75, 0.15, 1.0, 0.0);

		ofPushStyle();
		ofSetColor(body_color[i]);
		body_spheres[i].drawWireframe();
		ofPopStyle();
	}
}