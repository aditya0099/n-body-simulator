#include "physics_engine.h"



PhysicsEngine::PhysicsEngine(double interval) : time_interval(interval), time(0) { }


PhysicsEngine::~PhysicsEngine() {
	// TODO: Rule of 5
}

/**
 * Adds a body to the simulation
 * @param pos the initial position of the body
 * @param v the initial velocity
 * @param m the mass of the boject
 */
void PhysicsEngine::AddBody(const ofVec3f pos, const ofVec3f v, double m) {
	Body* body = new Body(pos, v, m);
	bodies.push_back(body);
}

/**
* Adds a body to the simulation
* @param z,y,z the initial position of the body
* @param v_x,v_y,v_z the initial velocity
* @param m the mass of the boject
*/
void PhysicsEngine::AddBody(double x, double y, double z, double v_x, double v_y, double v_z, double m) {
	Body* body = new Body(x, y, z, v_x, v_y, v_z, m);
	bodies.push_back(body);
}

/**
 * Returns a vector of all the positions of the bodies
 * @return a vector of updated positions
 */
vector<ofVec3f> PhysicsEngine::GetBodyPositions() const {
	vector<ofVec3f> positions;
	for (Body* m : bodies) {
		positions.push_back(m->position);
	}

	return positions;
}



