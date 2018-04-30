#pragma once

#include "ofVec3f.h"
#include "ofColor.h"

class PhysicsEngine {
	friend struct ColoredSphere;
public:
	static constexpr double kMassDensity = 0.001;
	static constexpr double kG = 0.000000000066742;

	static double CalculateRadius(double mass);


	struct Body {
		ofVec3f position;
		ofVec3f velocity;
		double mass;
		ofColor color;
	};


	PhysicsEngine(double interval);

	void AddBody(const ofVec3f pos, const ofVec3f v, double  m, ofColor color);
	void AddBody(double x, double y, double z,
		double v_x, double v_y, double v_z,
		double m, ofColor color);
	void RemovePreviousBody();

	virtual void update() = 0;

	vector<ofVec3f> GetBodyPositions() const;
	int GetBodyCount();

	virtual void SetElasticCollisions(bool elastic) = 0;

protected:
	virtual void HandleCollisions() = 0;

	int body_count;
	vector<Body> bodies;
	double time_interval;
	double time;
};

