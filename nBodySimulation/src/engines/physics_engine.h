#pragma once

#include "ofVec3f.h"
#include "ofColor.h"

/**
 * Base class for all n-body simulation implementations that contains
 * important core data points and required public methods.
 *
 * It requires that all derived classes implement an update function and
 * a collision handling function.
 */
class PhysicsEngine {
	friend struct ColoredSphere;
public:
	// Constants
	// The default density of a body
	static constexpr double kMassDensity = 0.001;
	// Newton's gravitational constant
	static constexpr double kG = 0.000000000066742;

	// Static function used to scale body radius by mass
	static double CalculateRadius(double mass);

	// Setup functions
	PhysicsEngine(double interval, bool elastic);

	void AddBody(ofVec3f position, ofVec3f velocity, double  mass, ofColor color);
	void AddBody(double x,   double y,   double z, 
				 double v_x, double v_y, double v_z,
				 double mass, ofColor color);
	void RemovePreviousBody();
	virtual void SetElasticCollisions(bool elastic) = 0;

	// Main loop
	virtual void update() = 0;

	// Getters
	vector<ofVec3f> GetBodyPositions() const;
	int GetBodyCount();
protected:
	/**
	 * Represents a body which has an associated mass, velocity and position.
	 * The color is used simply to differentiate between the bodies.
	 */
	struct Body {
		ofVec3f position;
		ofVec3f velocity;
		double mass;
		ofColor color;
	};

	// All implementations must consider collisions, even if it does nothing
	virtual void HandleCollisions() = 0;

	// Stores the simulation bodies
	vector<Body> bodies;

	// Auxiliary information
	int body_count;
	double time_interval;
	double time;
	bool elastic_collisions;
};

