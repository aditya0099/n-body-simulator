#pragma once

#include "ofVec3f.h"

class PhysicsEngine
{
public:
	const double kG = 0.000000000066742;

	PhysicsEngine();
	~PhysicsEngine();

	void AddBody(const vector<double>& pos, const vector<double>& v, double m);
	void AddBody(double x, double y, double z,
		double v_x, double v_y, double v_z,
		double m);

	virtual void update() = 0;

protected:
	struct Body {
		Body(const vector<double>& pos, const vector<double>& v, double m)
			: position(pos.at(0), pos.at(1), pos.at(2)), mass(m),
			velocity(v.at(0), v.at(1), v.at(2)) { }

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

