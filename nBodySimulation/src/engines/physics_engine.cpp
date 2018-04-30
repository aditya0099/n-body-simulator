#include "physics_engine.h"



double PhysicsEngine::CalculateRadius(double mass) {
	return std::cbrt(mass / kMassDensity);
}

PhysicsEngine::PhysicsEngine(double interval)
	: time_interval(interval), time(0), body_count(0) { }

/**
 * Adds a body to the simulation
 * @param pos the initial position of the body
 * @param v the initial velocity
 * @param m the mass of the boject
 */
void PhysicsEngine::AddBody(const ofVec3f pos, const ofVec3f v, 
		double m, ofColor color) {
	Body body;
	body.mass = m;
	body.velocity = v;
	body.position = pos;
	body.color = color;
	bodies.push_back(body);

	body_count++;
}

/**
 * Adds a body to the simulation
 *
 * @param x, y, z the initial position of the body
 * @param v_x, v_y, v_z the initial velocity
 * @param m the mass of the boject
 */
void PhysicsEngine::AddBody(double x,   double y,   double z,
							double v_x, double v_y, double v_z,
							double m, ofColor color) {
	AddBody(ofVec3f(x, y, z), ofVec3f(v_x, v_y, v_z), m, color);
}

void PhysicsEngine::RemovePreviousBody() {
	if (!bodies.empty()) {
		bodies.pop_back();
		body_count--;
	}
}

/**
 * Returns a vector of all the positions of the bodies
 * @return a vector of updated positions
 */
vector<ofVec3f> PhysicsEngine::GetBodyPositions() const {
	vector<ofVec3f> positions;
	for (Body m : bodies) {
		positions.push_back(m.position);
	}

	return positions;
}

int PhysicsEngine::GetBodyCount() {
	return body_count;
}