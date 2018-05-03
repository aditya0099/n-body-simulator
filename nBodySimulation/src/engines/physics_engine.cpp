#include "physics_engine.h"


/**
 * Helper function that returns a radius given a mass based on the mass-density constant.
 */
double PhysicsEngine::CalculateRadius(double mass) {
	return std::cbrt(mass / kMassDensity);
}

/**
 * Constructor. Takes the time increment interval for the update function and the collision type.
 */
PhysicsEngine::PhysicsEngine(double interval, bool elastic)
	: time_interval_(interval), elastic_collisions_(elastic), time_(0), body_count_(0) { }

/**
 * Adds a body to the simulation
 * @param position the initial position of the body
 * @param velocity the initial velocity
 * @param mass the mass of the object
 */
void PhysicsEngine::AddBody(ofVec3f position, ofVec3f velocity, 
		double mass, ofColor color) {
	Body body;
	body.mass = mass;
	body.velocity = velocity;
	body.position = position;
	body.color = color;
	bodies_.push_back(body);

	body_count_++;
}

/**
 * Adds a body to the simulation
 *
 * @param x, y, z the initial position of the body
 * @param v_x, v_y, v_z the initial velocity
 * @param mass the mass of the object
 */
void PhysicsEngine::AddBody(double x,   double y,   double z,
							double v_x, double v_y, double v_z,
							double mass, ofColor color) {
	AddBody(ofVec3f(x, y, z), ofVec3f(v_x, v_y, v_z), mass, color);
}

/**
 * Removes the most recently added body.
 */
void PhysicsEngine::RemovePreviousBody() {
	if (!bodies_.empty()) {
		bodies_.pop_back();
		body_count_--;
	}
}

/**
 * Returns a vector of all the positions of the bodies
 * @return a vector of updated positions
 */
vector<ofVec3f> PhysicsEngine::GetBodyPositions() const {
	vector<ofVec3f> positions;
	for (Body m : bodies_) {
		positions.push_back(m.position);
	}

	return positions;
}
/**
 * Returns the total number of bodies in the simulation at the current time.
 */
int PhysicsEngine::CountBodies() {
	return body_count_;
}