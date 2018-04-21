#include "few_body.h"
#include <cmath>

/**
 * Constructor; sets the time interval
 */
FewBodyEngine::FewBodyEngine(double interval) 
	: PhysicsEngine(), time_interval(interval), time(0) { }

/**
 * Destructor, deletes all the bodies
 */
FewBodyEngine::~FewBodyEngine() {
	for (Body*& body : bodies) {
		delete body;
		body = nullptr;
	}
}

/**
 * Main loop, updates the positions of all the bodies
 */
void FewBodyEngine::update() {
	time += time_interval;
	
	// Calculate the forces acting on all the bodies and update the velocity
	for (Body* m : bodies) {
		ofVec3f force = CalculateForce(m);
		m->velocity = CalculateVelocity(m, force);
	}

	// Finally, update all positions based on the new velocities
	for (Body* m : bodies) {
		m->position = CalculatePosition(m);
	}

}

/**
 * Calculates the net gravitational force on a particular body exerted
 * by all other bodies in the simulation at a particular time instant.
 *
 * @param body the body whose net force is to be calculated
 * @return the net force on the body
 */
ofVec3f FewBodyEngine::CalculateForce(Body const * body) const {
	ofVec3f net_force(0, 0, 0);

	// Loop through each body and sum up the forces
	for (Body* m : bodies) {
		net_force += CalculateGravity(m, body);
	}
	
	return net_force;
}


/**
 * Calculates the gravitational force exerted by m2 on m2 using 
 * Newton's law of Universal Gravitation.
 *
 * @param m1 the first body
 * @param m2 the second body
 *
 * @return gravitational force vector
 */
ofVec3f FewBodyEngine::CalculateGravity(Body const* m1, Body const* m2) const {
	// Optimization; a body cannot exert a force on itself
	if (m1 == m2) {
		return ofVec3f(0, 0, 0);
	}

	double dist_sq = m1->position.squareDistance(m2->position);

	// Get the magnitude of the gravitational force by -GmM/r^2
	double magnitude = -(kG * m1->mass * m2->mass / dist_sq);

	// Convert this to a vector by scaling the vector from body 1 to 2 by the magnitude
	return (m1->position - m2->position).scale(magnitude);
}

ofVec3f FewBodyEngine::CalculateVelocity(Body const* body, ofVec3f force) const {
	ofVec3f acceleration = force / body->mass;

	return body->velocity + (acceleration * time_interval);
}

ofVec3f FewBodyEngine::CalculatePosition(Body const* body) const {
	return body->position + body->velocity*time_interval;
}
