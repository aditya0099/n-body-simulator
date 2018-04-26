#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "engines\physics_engine.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
private:
	void DrawSetupBodies();
	void SetupGui();
	void AddBody();
	void DrawGui();

	enum ProgramState {
		SETUP,
		RUNNING,
		PAUSED
	};

	ProgramState state;
	
	PhysicsEngine *simulation;
	int body_count;

	int screen_size = 1000;

	ofxPanel setup_gui;
	ofxVec3Slider position_slider;
	ofxVec3Slider velocity_slider;
	ofxSlider<double> mass_slider;
	ofxColorSlider color_slider;
	ofxButton add_button;

	vector<ofSpherePrimitive> body_spheres;
	vector<ofColor> body_color;

	ofLight light;
};
