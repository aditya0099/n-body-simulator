#include "ofApp.h"
#include "engines\few_body.h"
#include "sphere.h"

/**
 * Called at the start of the application. Sets up the
 * physics engine, GUI, camera and lights.
 */
void ofApp::setup() {
	ofSetFullscreen(true);
	state = SETUP;
	simulation = new FewBodyEngine(0.02);

	SetupGui();
	SetupLights();

	ofSetBackgroundColor(20, 20, 20);
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

	case RUNNING:
	case PAUSED:
		camera.begin();
		DrawSimulationBodies();
		camera.end();
		break;
	}

	// Disable lighting before drawing GUI
	ofDisableLighting();
	ofDisableDepthTest();
	DrawGui();
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
	simulation->AddBody(position, velocity, mass, color);

	// Create a new sphere
	ColoredSphere sp;
	sp.sphere.setRadius(PhysicsEngine::CalculateRadius(mass));
	sp.color.set(color);

	body_spheres.push_back(sp);

	// Randomize the color for the next body
	color_slider = ofColor(rand() % 255, rand() % 255, rand() % 255);
}

/**
 * Removes the most recently added body.
 */
void ofApp::RemovePreviousBody() {
	simulation->RemovePreviousBody();
	if (!body_spheres.empty()) {
		body_spheres.pop_back();
	}
}

/**
 * Helper function for setting up the GUI at the start of the application.
 * Initializes all buttons and sliders to their default values and locations.
 */
void ofApp::SetupGui() {
	// SETUP
	add_button.addListener(this, &ofApp::AddBody);
	remove_button.addListener(this, &ofApp::RemovePreviousBody);

	setup_gui.setup("bodies");
	setup_gui.add(position_slider.setup("position",
		ofVec3f(0, 0, 0),
		ofVec3f(-screen_size*.5, -screen_size*.5, -screen_size*.5),
		ofVec3f(screen_size*.5, screen_size*.5, screen_size*.5)));
	setup_gui.add(velocity_slider.setup("velocity",
		ofVec3f(0, 0, 0), ofVec3f(-10, -10, -10), ofVec3f(10, 10, 10)));
	setup_gui.add(mass_slider.setup("mass", 10, 1, 100));
	setup_gui.add(color_slider.setup("color", 
		ofColor(rand() % 255, rand() % 255, rand() % 255),
		ofColor(0, 0, 0), ofColor(255, 255, 255)));
	setup_gui.add(add_button.setup("add"));
	setup_gui.add(remove_button.setup("remove"));


	// RUNNING
	run_button.addListener(this, &ofApp::RunSimulation);

	run_gui.setup("run");
	run_gui.add(elastic_button.setup("elastic collisions", false));
	run_gui.add(run_button.setup("start simulation"));
	run_gui.setPosition(setup_gui.getWidth() + 20, 10);

	// PAUSED
	exit_button.addListener(this, &ofApp::Return);
	step_button.addListener(this, &ofApp::Step);

	pause_gui.setup("pause");
	pause_gui.add(pause_button.setup("pause", false));
	pause_gui.add(exit_button.setup("exit", false));

	simulation_gui.setup("simulation");
	simulation_gui.add(step_slider.setup("step amount", 1, 0.01, 10));
	simulation_gui.add(step_button.setup("step"));
	simulation_gui.setPosition(10, pause_gui.getHeight() + 20);
	
}

/**
 * Reverts a running simulation to its setup state.
 */
void ofApp::Return() {
	// TODO: load from xml
	state = SETUP;
	ofSetBackgroundColor(20, 20, 20);
}

/**
 * Handles the keyboard shortcuts for the application.
 *
 * @param key the key that is pressed
 */
void ofApp::keyPressed(int key) {
	switch (key) {
	case OF_KEY_RETURN:
		if (state == SETUP) {
			AddBody();
		}
		break;

	case OF_KEY_BACKSPACE:
		if (state == SETUP) {
			RemovePreviousBody();
		} else {
			Return();
		}
		break;

	case 'p':
		if (state != SETUP) {
			pause_button = (state == RUNNING) ? true : false;
		}
		break;

	case 's':
		if (state == PAUSED) {
			Step();
		}
		break;

	case 'r':
		RunSimulation();
		break;
	}
}

/**
 * Helper function that draws the bodies during the setup phase.
 */
void ofApp::DrawSetupBodies() {
	double offset = (double)ofGetWidth() / ((double)body_spheres.size() + 1);
	double x = offset;
	for (ColoredSphere& sp : body_spheres) {
		sp.sphere.setPosition(x, ofGetHeight()*.6, 0);
		x += offset;

		sp.sphere.rotate(ofGetElapsedTimef() * 75, 0.15, 1.0, 0.0);

		ofPushStyle();
		ofSetColor(sp.color);
		auto small_sp = sp.sphere;
		small_sp.setRadius(75);
		small_sp.drawWireframe();
		ofPopStyle();
	}
}

/**
 * Helper function that draws the GUI to the screen.
 */
void ofApp::DrawGui() {
	switch (state) {
	case SETUP:
		setup_gui.draw();
		collision_gui.draw();
		run_gui.draw();
		break;

	case RUNNING:
		pause_button.draw();
		pause_gui.draw();
		break;

	case PAUSED:
		simulation_gui.draw();
		pause_gui.draw();
		break;
	}
}

/**
 * Helper function that switches the state of the application to running.
 */
void ofApp::RunSimulation() {
	simulation->SetElasticCollisions(elastic_button);
	state = RUNNING;
	ofSetBackgroundColor(0, 0, 0);
}

/**
 * Draws each body with the correct color.
 */
void ofApp::DrawSimulationBodies() {
	for (ColoredSphere& sp : body_spheres) {
		// Push a new style for each color
		ofPushStyle();
		ofSetColor(sp.color);
		sp.sphere.drawWireframe();
		ofPopStyle();
	}
}

/**
 * Updates the local body list with the positions from the simulation.
 * Also adds rotation to the bodies to make them look more realistic.
 */
void ofApp::UpdateSimulationBodies() {
	// If there was an inelastic collosion and the number of bodies changed, update the entire list
	if (simulation->GetBodyCount() != body_spheres.size()) {
		body_spheres = ColoredSphere::ParseBodies(simulation);
	}

	vector<ofVec3f> positions = simulation->GetBodyPositions();
	for (int i = 0; i < body_spheres.size(); i++) {
		// Set the position of the sphere
		body_spheres[i].sphere.setPosition(positions[i]);
		
		// Rotate the sphere slightly to aid in the 3d visualization
		body_spheres[i].sphere.rotate(ofGetElapsedTimef() * 25, 0.15, 1.0, 0.0);
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
	light_l_up.setup();
	light_l_up.setPointLight();
	light_l_up.setPosition(0, 0, 0);

	light_r_up.setup();
	light_r_up.setPointLight();
	light_r_up.setPosition(ofGetWidth() - 1, 0, 0);

	light_l_down.setup();
	light_l_down.setPointLight();
	light_l_down.setPosition(0, ofGetHeight() - 1, 0);

	light_r_down.setup();
	light_r_down.setPointLight();
	light_r_down.setPosition(ofGetWidth() - 1, ofGetHeight() - 1, 0);

	light_l_up.enable();
	light_r_up.enable();
	light_l_down.enable();
	light_r_down.enable();
}