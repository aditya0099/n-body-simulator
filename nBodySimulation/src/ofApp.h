#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "engines\physics_engine.h"
#include "sphere.h"
#include "xml_helpers.h"

class ofApp : public ofBaseApp {

public:
	// Default OF functions and loops
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);

private:
	static const string kXmlFileName;
	/**
	 * Enumeration to represent the state of the program
	 * 
	 * SETUP - the phase where the initial conditions are set
	 * RUNNING - the simulation is allowed to run at the default rate
	 * PAUSED - the simulation is frozen and can be stepped through
	 */
	enum ProgramState {
		INIT,
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
	void ReadXml();

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
	void DrawInstructions();

	// Control variables
	ProgramState state_;
	
	// Main simulation driver
	PhysicsEngine *simulation_;

	// 3d objects, lights and camera
	vector<ColoredSphere> body_spheres_;
	ofLight light_l_up_;
	ofLight light_r_up_;
	ofLight light_l_down_;
	ofLight light_r_down_;
	ofEasyCam camera_;

	// XML reader and writer
	XmlHelper* xml_;

	// GUI items
	ofxPanel setup_gui_;
	ofxVec3Slider position_slider_;
	ofxVec3Slider velocity_slider_;
	ofxSlider<double> mass_slider_;
	ofxColorSlider color_slider_;
	ofxButton add_button_;
	ofxButton remove_button_;

	ofxPanel collision_gui_;
	ofxToggle elastic_button_;

	ofxPanel run_gui_;
	ofxButton run_button_;

	ofxPanel simulation_gui_;
	ofxPanel pause_gui_;
	ofxToggle pause_button_;
	ofxButton step_button_;
	ofxSlider<double> step_slider_;
	ofxButton return_button_;
};
