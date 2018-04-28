#pragma once

#include "ofVec3f.h"

class PhysicsEngine {
public:
	static constexpr double kRadius = 100.0;
	static constexpr double kG = 0.000000000066742;


	struct Body {
		ofVec3f position;
		ofVec3f velocity;
		double mass;
		double radius;
	};


	PhysicsEngine(double interval);

	void AddBody(const ofVec3f pos, const ofVec3f v, double  m, double r = kRadius);
	void AddBody(double x, double y, double z,
		double v_x, double v_y, double v_z,
		double m, double r = kRadius);

	void RemovePreviousBody();

	vector<ofVec3f> GetBodyPositions() const;

	virtual void update() = 0;

protected:
	int bodies_count;
	vector<Body> bodies;
	double time_interval;
	double time;
};

