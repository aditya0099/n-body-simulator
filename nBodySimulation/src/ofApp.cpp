#include "ofApp.h"
#include "engines\few_body.h"

/**
 * Called at the start of the application. Sets up the
 * physics engine, GUI, camera and lights.
 */
void ofApp::setup() {
	state = SETUP;
	simulation = new FewBodyEngine(0.01);
	body_count = 0;
	ofSetBackgroundColor(20, 20, 20);

	SetupGui();
	
	SetupLights();

	camera.setDistance(500);
}

/**
 * Main control loop. Updates depending on the current application state
 */
void ofApp::update() {
	switch (state) {
	case SETUP:
		break;

	case RUNNING:
		// Toggle pause state if button is clicked
		if (pause_button) {
			state = PAUSED;
		}

		simulation->update();
		break;

	case PAUSED:
		if (!pause_button) {
			state = RUNNING;
		}
		break;
	}

	// Always update the body posiiton incase of stepping
	UpdateSimulationBodies();
}

/**
 * Main draw loop. Draws depending on the application state
 */
void ofApp::draw() {
	ofEnableLighting();
	ofEnableDepthTest();

	switch (state) {
	case SETUP:
		DrawSetupBodies();
		break;

	case RUNNING: case PAUSED:
		camera.begin();
		DrawSimulationBodies();
		camera.end();
		break;
	}

	ofDisableLighting();
	ofDisableDepthTest();
	DrawGui();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// TODO: Keyboard Shortcuts
}

/**
 * Cleans up memory before exiting.
 */
void ofApp::exit() {
	delete simulation;
}

/**
 * Adds a body to the simulation using the current state of the setup GUI.
 */
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

/**
 * Removes the most recently added body.
 */
void ofApp::RemovePreviousBody() {
	simulation->RemovePreviousBody();
	body_color.pop_back();
	body_spheres.pop_back();
}

// TODO: clean up this function
/**
 * Helper function for setting up the GUI at the start of the application.
 * Initilaizes all buttons and sliders to their default values and locations.
 */
void ofApp::SetupGui() {
	// SETUP GUI
	add_button.addListener(this, &ofApp::AddBody);
	remove_button.addListener(this, &ofApp::RemovePreviousBody);

	setup_gui.setup("bodies", "../data/setup.xml");

	setup_gui.add(position_slider.setup("position",
		ofVec3f(0, 0, 0),
		ofVec3f(-screen_size*.5, -screen_size*.5, -screen_size*.5),
		ofVec3f(screen_size*.5, screen_size*.5, screen_size*.5)));

	setup_gui.add(velocity_slider.setup("velocity",
		ofVec3f(0, 0, 0), ofVec3f(-25, -25, -25), ofVec3f(25, 25, 25)));

	setup_gui.add(mass_slider.setup("mass", 10, 1, 100));

	setup_gui.add(color_slider.setup("color", ofColor(50, 100, 150),
		ofColor(0, 0, 0), ofColor(255, 255, 255)));

	setup_gui.add(add_button.setup("add"));
	setup_gui.add(remove_button.setup("remove"));

	// RUN GUI
	run_button.addListener(this, &ofApp::RunSimulation);

	run_gui.setup("run");
	run_gui.add(run_button.setup("start simulation"));
	run_gui.setPosition(10, setup_gui.getHeight() + 20);


	step_button.addListener(this, &ofApp::Step);
	exit_button.addListener(this, &ofApp::Reset);

	// PAUSE GUI
	pause_gui.setup("pause");
	pause_gui.add(pause_button.setup("pause", false));
	pause_gui.add(exit_button.setup("exit", false));

	simulation_gui.setup("simulation");
	simulation_gui.add(step_slider.setup("step amount", 1, 0.01, 10));
	simulation_gui.add(step_button.setup("step"));
	simulation_gui.setPosition(10, pause_gui.getHeight() + 20);
	
}

/**
 * Resets a running simulation to its setup state.
 */
void ofApp::Reset() {
	delete simulation;
	simulation = new FewBodyEngine(0.01);

	body_color.clear();
	body_spheres.clear();

	state = SETUP;
	ofSetBackgroundColor(20, 20, 20);
}

/**
 * Helper function that draws the bodies during the setup phase.
 */
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

// TODO: clean up this function
/**
 * Helper function that draws the GUI to the screen.
 */
void ofApp::DrawGui() {
	switch (state) {
	case SETUP:
		position_slider.draw();
		velocity_slider.draw();
		mass_slider.draw();
		color_slider.draw();
		add_button.draw();
		setup_gui.draw();

		run_button.draw();
		run_gui.draw();
		break;

	case RUNNING:
		pause_button.draw();
		pause_gui.draw();
		break;

	case PAUSED:
		step_slider.draw();
		step_button.draw();
		simulation_gui.draw();
		pause_button.draw();
		pause_gui.draw();
		break;
	}
}

/**
 * Helper function that switches the state of the application to running.
 */
void ofApp::RunSimulation() {
	state = RUNNING;
	ofSetBackgroundColor(0, 0, 0);
}

/**
 * Draws each body with the correct color.
 */
void ofApp::DrawSimulationBodies() {
	for (int i = 0; i < body_spheres.size(); i++) {
		// Push a new style for each color
		ofPushStyle();
		ofSetColor(body_color[i]);
		body_spheres[i].drawWireframe();
		ofPopStyle();
	}
}

/**
 * Updates the local body list with the positions from the simulation.
 * Also adds rotation to the bodies to make them look more realistic.
 */
void ofApp::UpdateSimulationBodies() {
	vector<ofVec3f> positions = simulation->GetBodyPositions();
	for (int i = 0; i < body_spheres.size(); i++) {
		// Set the position of the sphere
		body_spheres[i].setPosition(positions[i]);
		
		// Rotate the sphere slightly to aid in the 3d visulaization
		body_spheres[i].rotate(ofGetElapsedTimef() * 25, 0.15, 1.0, 0.0);
	}
}

/**
 * Called when the step button is pressed. Updates the simulation based on the
 * position of the step slider.
 */
void ofApp::Step() {
	for (int i = 0; i < (int)(step_slider / 0.01); i++) {
		simulation->update();
	}
}

/**
 * Sets up the light types and positions. Places one in each corner of the screen.
 */
void ofApp::SetupLights() {
	light1.setup();
	light1.setPointLight();
	light1.setPosition(0, 0, 0);

	light2.setup();
	light2.setPointLight();
	light2.setPosition(ofGetWidth() - 1, 0, 0);

	light3.setup();
	light3.setPointLight();
	light3.setPosition(0, ofGetHeight() - 1, 0);

	light4.setup();
	light4.setPointLight();
	light4.setPosition(ofGetWidth() - 1, ofGetHeight() - 1, 0);

	light1.enable();
	light2.enable();
	light3.enable();
	light4.enable();
}








//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}