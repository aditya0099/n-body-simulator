#pragma once

#include "physics_engine.h"
#include "ofVec3f.h"
#include "../kd_tree/kdtree.h"
#include "../kd_tree/utils.h"

#include <vector>

using std::vector;


class FewBodyEngine : public PhysicsEngine {
public:
	// Setup functions
	FewBodyEngine(double interval, bool elastic = false);
	void SetElasticCollisions(bool elastic);

	// Main loop
	void update();

private:
	// Position and velocity updating functions
	ofVec3f CalculateForce(const Body &body) const;
	ofVec3f CalculateGravity(const Body &body1, const Body &body2) const;
	ofVec3f CalculateVelocity(const Body &body, const ofVec3f force) const;
	ofVec3f CalculatePosition(const Body &body) const;

	// Collision handling and detection functions
	void HandleCollisions();
	void Collide(int body1_idx, int body2_idx);
	bool Intersect(int body1_idx, int body2_idx);


	KDTree<3>* kd_tree; // TODO: remove
};

