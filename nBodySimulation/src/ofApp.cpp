#include "ofApp.h"
#include "engines\few_body.h"
#include "sphere.h"

const string ofApp::kXmlFileName = "setup.xml";

/**
 * Called at the start of the application. Sets up the
 * physics engine, GUI, camera and lights.
 */
void ofApp::setup() {
	state_ = SETUP;

	ofSetFullscreen(false);
	simulation_ = new FewBodyEngine();

	SetupGui();
	SetupLights();

	ofSetBackgroundColor(20, 20, 20);
	camera_.setDistance(500);

	// Get the initial conditions from the XML file
	xml_ = new XmlHelper(kXmlFileName);
	ReadXml();
}

/**
 * Main control loop. Updates depending on the current application state
 */
void ofApp::update() {
	switch (state_) {
	case RUNNING:
		// Toggle pause state if button is clicked
		if (pause_button_) {
			state_ = PAUSED;
		}

		simulation_->update();
		break;

	case PAUSED:
		if (!pause_button_) {
			state_ = RUNNING;
		}
		break;
	}

	// Always update the body position in case of stepping
	UpdateSimulationBodies();
}

/**
 * Main draw loop. Draws depending on the application state
 */
void ofApp::draw() {
	ofEnableLighting();
	ofEnableDepthTest();

	switch (state_) {
	case SETUP:
		DrawSetupBodies();
		break;

	case RUNNING:
	case PAUSED:
		camera_.begin();
		DrawSimulationBodies();
		camera_.end();
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
	delete simulation_;
	delete xml_;
}

/**
 * Adds a body to the simulation using the current state of the setup GUI.
 */
void ofApp::AddBody() {
	// Get the data from the sliders
	ofVec3f position = position_slider_;
	ofVec3f velocity = velocity_slider_;
	double mass = mass_slider_;
	ofColor color = color_slider_;

	// Add the body to a simulation
	simulation_->AddBody(position, velocity, mass, color);

	// Create a new sphere
	ColoredSphere sp;
	sp.sphere.setRadius(PhysicsEngine::CalculateRadius(mass));
	sp.color.set(color);

	body_spheres_.push_back(sp);

	// Randomize the color for the next body
	color_slider_ = ofColor(rand() % 255, rand() % 255, rand() % 255);

	// Add the body to the XML file
	xml_->WriteBody(position, velocity, mass, color);
}

/**
 * Removes the most recently added body.
 */
void ofApp::RemovePreviousBody() {
	simulation_->RemovePreviousBody();
	if (!body_spheres_.empty()) {
		body_spheres_.pop_back();
	}

	xml_->ErasePreviousBody();
}

/**
 * Helper function for setting up the GUI at the start of the application.
 * Initializes all buttons and sliders to their default values and locations.
 */
void ofApp::SetupGui() {
	// Get the average screen dimensions
	double screen_size = (ofGetWidth() + ofGetHeight()) / 2;

	// Gui for setup screen
	add_button_.addListener(this, &ofApp::AddBody);
	remove_button_.addListener(this, &ofApp::RemovePreviousBody);

	setup_gui_.setup("bodies");
	setup_gui_.add(position_slider_.setup("position",
		ofVec3f(0, 0, 0),
		ofVec3f(-screen_size*.25, -screen_size*.25, -screen_size*.25),
		ofVec3f(screen_size*.25, screen_size*.25, screen_size*.25)));
	setup_gui_.add(velocity_slider_.setup("velocity",
		ofVec3f(0, 0, 0), ofVec3f(-10, -10, -10), ofVec3f(10, 10, 10)));
	setup_gui_.add(mass_slider_.setup("mass", 10, 1, 100));
	setup_gui_.add(color_slider_.setup("color", 
		ofColor(rand() % 255, rand() % 255, rand() % 255),
		ofColor(0, 0, 0), ofColor(255, 255, 255)));
	setup_gui_.add(add_button_.setup("add"));
	setup_gui_.add(remove_button_.setup("remove"));


	// Gui for running screen
	run_button_.addListener(this, &ofApp::RunSimulation);

	run_gui_.setup("run");
	run_gui_.add(elastic_button_.setup("elastic collisions", false));
	run_gui_.add(run_button_.setup("start simulation"));
	run_gui_.setPosition(setup_gui_.getWidth() + 20, 10);

	// Gui for paused screen
	return_button_.addListener(this, &ofApp::Return);
	step_button_.addListener(this, &ofApp::Step);

	pause_gui_.setup("pause");
	pause_gui_.add(pause_button_.setup("pause", false));
	pause_gui_.add(return_button_.setup("return", false));

	simulation_gui_.setup("simulation");
	simulation_gui_.add(step_slider_.setup("step amount", 1, 0.01, 10));
	simulation_gui_.add(step_button_.setup("step"));
	simulation_gui_.setPosition(10, pause_gui_.getHeight() + 20);
	
}

/**
 * Reverts a running simulation to its setup state.
 */
void ofApp::Return() {
	// Reset the state
	state_ = SETUP;
	ofSetBackgroundColor(20, 20, 20);

	// Clear the simulation and load the initial conditions from the XML
	body_spheres_.clear();
	delete simulation_;
	simulation_ = new FewBodyEngine();

	ReadXml();
}

/**
 * Handles the keyboard shortcuts for the application.
 * 
 * SETUP:
 *   - BACKSPACE - remove previous body
 *   - ENTER - add body with current settings
 *   - 'r' - run simulation
 *   - ESC - quit
 * RUNNING:
 *   - BACKSPACE - return to setup
 *   - p - pause
 *   - ESC - quit
 * PAUSED:
 *   - BACKSPACE - return to setup
 *   - p - continue
 *   - s - step
 *   - ESC - quit
 *
 * @param key the key that is pressed
 */
void ofApp::keyPressed(int key) {
	switch (key) {
	case OF_KEY_RETURN:
		if (state_ == SETUP) {
			AddBody();
		}
		break;

	case OF_KEY_BACKSPACE:
		if (state_ == SETUP) {
			RemovePreviousBody();
		} else {
			Return();
		}
		break;

	case 'p':
		if (state_ != SETUP) {
			pause_button_ = (state_ == RUNNING) ? true : false;
		}
		break;

	case 's':
		if (state_ == PAUSED) {
			Step();
		}
		break;
	
	case 'r':
		if (state_ == SETUP) {
			RunSimulation();
		}
		break;

	case OF_KEY_ESC:
		exit();
		std::exit(0);
	}
}

/**
 * Helper function that draws the bodies during the setup phase.
 */
void ofApp::DrawSetupBodies() {
	double offset = (double)ofGetWidth() / ((double)body_spheres_.size() + 1);
	double x = offset;
	for (ColoredSphere& sp : body_spheres_) {
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
	switch (state_) {
	case SETUP:
		setup_gui_.draw();
		collision_gui_.draw();
		run_gui_.draw();
		break;

	case RUNNING:
		pause_button_.draw();
		pause_gui_.draw();
		break;

	case PAUSED:
		simulation_gui_.draw();
		pause_gui_.draw();
		break;
	}

	DrawInstructions();
}

/**
 * Helper function that switches the state of the application to running.
 */
void ofApp::RunSimulation() {
	simulation_->SetElasticCollisions(elastic_button_);
	state_ = RUNNING;
	ofSetBackgroundColor(0, 0, 0);
}

/**
 * Draws each body with the correct color.
 */
void ofApp::DrawSimulationBodies() {
	for (ColoredSphere& sp : body_spheres_) {
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
	// If there was an inelastic collision and the number of bodies changed, update the entire list
	if (simulation_->CountBodies() != body_spheres_.size()) {
		body_spheres_ = ColoredSphere::ParseBodies(simulation_);
	}

	vector<ofVec3f> positions = simulation_->GetBodyPositions();
	for (int i = 0; i < body_spheres_.size(); i++) {
		// Set the position of the sphere
		body_spheres_[i].sphere.setPosition(positions[i]);
		
		// Rotate the sphere slightly to aid in the 3d visualization
		body_spheres_[i].sphere.rotate(ofGetElapsedTimef() * 25, 0.15, 1.0, 0.0);
	}
}

/**
 * Called when the step button is pressed. Updates the simulation based on the
 * position of the step slider.
 */
void ofApp::Step() {
	for (int i = 0; i < (int)(step_slider_ / 0.01); i++) {
		simulation_->update();
	}
}

/**
 * Sets up the light types and positions. Places one in each corner of the screen.
 */
void ofApp::SetupLights() {
	light_l_up_.setup();
	light_l_up_.setPointLight();
	light_l_up_.setPosition(0, 0, 0);

	light_r_up_.setup();
	light_r_up_.setPointLight();
	light_r_up_.setPosition(ofGetWidth() - 1, 0, 0);

	light_l_down_.setup();
	light_l_down_.setPointLight();
	light_l_down_.setPosition(0, ofGetHeight() - 1, 0);

	light_r_down_.setup();
	light_r_down_.setPointLight();
	light_r_down_.setPosition(ofGetWidth() - 1, ofGetHeight() - 1, 0);

	light_l_up_.enable();
	light_r_up_.enable();
	light_l_down_.enable();
	light_r_down_.enable();
}

/**
 * Reads initial conditions from the setup.xml file. Uses the ofApp::AddBody function
 * for a cleaner initialization process.
 */
void ofApp::ReadXml() {
	if (xml_->IsEmpty()) {
		return;
	}

	// Stops the AddBody function from creating duplicates
	xml_->SetReadOnly(true);

	// Loop through each body and get the parameters
	int bodies_count = xml_->CountBodies();
	for (int i = 0; i < bodies_count; i++) {
		// Set the position of the GUI sliders so that AddBody can be called
		position_slider_ = xml_->GetPosition(i);
		velocity_slider_ = xml_->GetVelocity(i);
		mass_slider_ = xml_->GetMass(i);
		color_slider_ = xml_->GetColor(i);

		// DRY, reuses AddBody code but prevents XML writing
		AddBody();
	}

	// Restore the writing permissions to the XML reader
	xml_->SetReadOnly(false);
}

/**
 * Draws keyboard shortcut information.
 * 
 * SETUP:
 *   - BACKSPACE - remove previous body
 *   - ENTER - add body with current settings
 *   - 'r' - run simulation
 *   - ESC - quit
 * RUNNING:
 *   - BACKSPACE - return to setup
 *   - p - pause
 *   - ESC - quit
 * PAUSED:
 *   - BACKSPACE - return to setup
 *   - p - continue
 *   - s - step
 *   - ESC - quit
 */
void ofApp::DrawInstructions() {
	string instructions;
	switch (state_) {
	case SETUP:
		instructions = "Keyboard Shortcuts:\n\n"
			" * ENTER - add body with current settings\n"
			" * BACKSPACE - remove previous body\n"
			" * r - run simulation\n"
			" * ESC - exit";
		break;
	case RUNNING:
		instructions = "Keyboard Shortcuts:\n"
			" * BACKSPACE - return to setup\n"
			" * p - pause\n"
			" * ESC - exit";
		break;
	case PAUSED:
		instructions = "Keyboard Shortcuts:\n"
			" * BACKSPACE - return to setup\n"
			" * p - continue\n"
			" * s - step\n"
			" * ESC - exit";
		break;
	}

	ofDrawBitmapString(instructions, ofGetWidth() * 0.6, 20);
}
