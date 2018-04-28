#pragma once

#include "physics_engine.h"
#include "ofVec3f.h"
#include "../kd_tree/kdtree.h"
#include "../kd_tree/utils.h"

#include <vector>

using std::vector;


class FewBodyEngine : public PhysicsEngine {
public:
	FewBodyEngine(double interval);
	~FewBodyEngine();

	void update();


private:
	ofVec3f CalculateForce(const Body &body) const;
	ofVec3f CalculateGravity(const Body &body1, const Body &body2) const;
	ofVec3f CalculateVelocity(const Body &body, const ofVec3f force) const;
	ofVec3f CalculatePosition(const Body &body) const;

	void HandleCollisions();

	// Used for efficiently handling collisions
	KDTree<3>* kd_tree;
};

