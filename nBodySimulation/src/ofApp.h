#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "engines\physics_engine.h"
#include "sphere.h"
#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp {

public:
	// Default OF functions and loops
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);

private:
	/**
	 * Enumeration to represent the state of the program
	 *
	 * SETUP - the phase where the initial conditions are set
	 * RUNNING - the simulation is allowed to run at the default rate
	 * PAUSED - the simulation is frozen and can be stepped through
	 */
	enum ProgramState {
		SETUP,
		RUNNING,
		PAUSED
	};

	// Initial application setup functions
	void SetupGui();
	void SetupLights();

	// Simulation setup functions
	void AddBody();
	void RemovePreviousBody();

	// Button handlers
	void RunSimulation();
	void Step();
	void Return();

	// Update loop helper functions
	void UpdateSimulationBodies();

	// Draw loop helper functions
	void DrawSetupBodies();
	void DrawSimulationBodies();
	void DrawGui();

	// Control variable
	ProgramState state;
	
	// Simulation and auxiliary information
	PhysicsEngine *simulation;
	int body_count;

	// 3d objects, lights and camera
	vector<ColoredSphere> body_spheres;
	ofLight light_l_up;
	ofLight light_r_up;
	ofLight light_l_down;
	ofLight light_r_down;
	ofEasyCam camera;

	// XML reader and writer
	ofxXmlSettings xml;

	// GUI items
	ofxPanel setup_gui;
	ofxVec3Slider position_slider;
	ofxVec3Slider velocity_slider;
	ofxSlider<double> mass_slider;
	ofxColorSlider color_slider;
	ofxButton add_button;
	ofxButton remove_button;

	ofxPanel collision_gui;
	ofxToggle elastic_button;

	ofxPanel run_gui;
	ofxButton run_button;

	ofxPanel simulation_gui;
	ofxPanel pause_gui;
	ofxToggle pause_button;
	ofxButton step_button;
	ofxSlider<double> step_slider;
	ofxButton exit_button;
};
