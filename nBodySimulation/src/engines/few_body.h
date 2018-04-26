#pragma once

#include "physics_engine.h"
#include "ofVec3f.h"

#include <vector>

using std::vector;


class FewBodyEngine : public PhysicsEngine {
public:
	FewBodyEngine(double interval);

	void update();
private:

	ofVec3f CalculateForce(const Body &body) const;
	ofVec3f CalculateGravity(const Body &body1, const Body &body2) const;
	ofVec3f CalculateVelocity(const Body &body, ofVec3f force) const;
	ofVec3f CalculatePosition(const Body &body) const;
};

