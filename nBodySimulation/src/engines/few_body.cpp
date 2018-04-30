#include "few_body.h"

#include "ofVec3f.h"
#include <cmath>

/**
 * Constructor; sets the time interval
 */
FewBodyEngine::FewBodyEngine(double interval) 
	: PhysicsEngine(interval), elastic_collisions(true) { }

FewBodyEngine::~FewBodyEngine() {
	delete kd_tree;
}

/**
 * Main loop, updates the positions of all the bodies
 */
void FewBodyEngine::update() {
	time += time_interval;
	
	// Calculate the forces acting on all the bodies and update the velocity
	for (Body &m : bodies) {
		ofVec3f force = CalculateForce(m);
		m.velocity = CalculateVelocity(m, force);
	}

	// Finally, update all positions based on the new velocities
	for (Body &m : bodies) {
		m.position = CalculatePosition(m);
	}

	HandleCollisions();
}

void FewBodyEngine::SetElasticCollisions(bool elastic) {
	elastic_collisions = elastic;
}

/**
 * Calculates the net gravitational force on a particular body exerted
 * by all other bodies in the simulation at a particular time instant.
 *
 * @param body the body whose net force is to be calculated
 * @return the net force on the body
 */
ofVec3f FewBodyEngine::CalculateForce(const Body &body) const {
	ofVec3f net_force(0, 0, 0);

	// Loop through each body and sum up the forces
	for (const Body &m : bodies) {
		net_force = net_force + CalculateGravity(m, body);
	}

	return net_force;
}


/**
 * Calculates the gravitational force exerted by m1 on m2 using 
 * Newton's law of Universal Gravitation.
 *
 * @param m1 the first body
 * @param m2 the second body
 *
 * @return gravitational force vector
 */
ofVec3f FewBodyEngine::CalculateGravity(const Body &m1, const Body &m2) const {
	// Optimization; a body cannot exert a force on itself
	if (m1.position == m2.position) {
		return ofVec3f(0, 0, 0);
	}

	double dist_sq = m1.position.squareDistance(m2.position);

	// Get the magnitude of the gravitational force by -GmM/r^2
	double magnitude = (kG*1000000000000 * m1.mass * m2.mass / dist_sq);

	// Convert this to a vector by scaling the vector from body 1 to 2 by the magnitude
	return (m1.position - m2.position).scale(magnitude);
}

/**
 * Calculates the new velocity of a body given a force.
 *
 * @param body the body being considered
 * @param force the force acting on the body
 * @return the new velocity of the body
 */
ofVec3f FewBodyEngine::CalculateVelocity(const Body &body, const ofVec3f force) const {
	ofVec3f acceleration = force / body.mass;
	return body.velocity + (acceleration * time_interval);
}

/**
* Calculates the new position of a body using its velocity.
*
* @param body the body being considered
* @return the new position of the body
*/
ofVec3f FewBodyEngine::CalculatePosition(const Body &body) const {
	return body.position + body.velocity * (float)time_interval;
}

/**
 * Handles collisions of the bodies elasitcally or inelastically.
 */
void FewBodyEngine::HandleCollisions() {
	for (int i = 0; i < body_count; i++) {
		for (int j = 0; j < body_count; j++) {
			if (Intersect(i, j)	&& i != j) {
				Collide(i, j);
				return;
			}
		}
	}
}

bool FewBodyEngine::Intersect(int idx_1, int idx_2) {
	double distance = bodies[idx_1].position.squareDistance(bodies[idx_2].position);
	double sum_radii = std::pow(CalculateRadius(bodies[idx_1].mass) 
							  + CalculateRadius(bodies[idx_2].mass), 2);
	
	return distance <= sum_radii;
}

void FewBodyEngine::Collide(int idx_1, int idx_2) {
	Body &m1 = bodies[idx_1];
	Body &m2 = bodies[idx_2];

	if (elastic_collisions) {
		ofVec3f v1 = m1.velocity - (2 * m2.mass / (m1.mass + m2.mass)) * (m1.velocity - m2.velocity).dot(m1.position - m2.position) / (m1.position - m2.position).lengthSquared() * (m1.position - m2.position);
		ofVec3f v2 = m2.velocity - (2 * m1.mass / (m1.mass + m2.mass)) * (m2.velocity - m1.velocity).dot(m2.position - m1.position) / (m2.position - m1.position).lengthSquared() * (m2.position - m1.position);

		m1.velocity = v1;
		m2.velocity = v2;
	} else {
		m1.velocity = m1.mass / (m1.mass * m2.mass) * m1.velocity
					+ m2.mass / (m1.mass * m2.mass) * m2.velocity;
		m1.color = m1.color + m2.color;
		m1.mass = m1.mass + m2.mass;
		m1.position = (m1.position + m2.position) / 2;

		bodies.erase(bodies.begin() + idx_2);
		body_count--;
	}
}