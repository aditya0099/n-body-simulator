#pragma once

#include "physics_engine.h"
#include "ofVec3f.h"

#include <vector>

using std::vector;


class FewBodyEngine : public PhysicsEngine {
public:
	FewBodyEngine(double interval);
	~FewBodyEngine();

	void update();
private:

	ofVec3f CalculateForce(Body const * body) const;
	ofVec3f CalculateGravity(Body const * body1, Body const * body2) const;
	ofVec3f CalculateVelocity(Body const * body, ofVec3f force) const;
	ofVec3f CalculatePosition(Body const * body) const;
};
