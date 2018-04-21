#pragma once

#include "ofVec3f.h"

class PhysicsEngine
{
public:
	const double kG = 0.000000000066742;

	PhysicsEngine();
	~PhysicsEngine();

	void AddBody(const ofVec3f pos, const ofVec3f v, double m);
	void AddBody(double x, double y, double z,
		double v_x, double v_y, double v_z,
		double m);

	vector<ofVec3f> GetBodyPositions() const;

	virtual void update() = 0;

protected:
	struct Body {
		Body(const ofVec3f pos, const ofVec3f v, double m)
			: position(pos), velocity(v), mass(m) { }

		Body(double x, double y, double z,
			double v_x, double v_y, double v_z,
			double m)
			: position(z, y, z), velocity(v_x, v_y, v_z), mass(m) { }
		
		ofVec3f position;
		ofVec3f velocity;
		double mass;
	};

	int bodies_count;
	vector<Body*> bodies;
};

