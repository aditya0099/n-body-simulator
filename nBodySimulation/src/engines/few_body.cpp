#include "few_body.h"

#include "ofVec3f.h"
#include <cmath>

/**
 * Constructor that sets the time interval for updates.
 *
 * @param interval the step amount for the update loop
 */
FewBodyEngine::FewBodyEngine(double interval, bool elastic) 
	: PhysicsEngine(interval, elastic) { }

/**
 * Main loop, updates the positions of all the bodies based on the step amount.
 */
void FewBodyEngine::update() {
	time_ += time_interval_;
	
	// Calculate the forces acting on all the bodies and update the velocity
	for (Body &m : bodies_) {
		ofVec3f force = CalculateForce(m);
		m.velocity = CalculateVelocity(m, force);
	}

	// Finally, update all positions based on the new velocities
	for (Body &m : bodies_) {
		m.position = CalculatePosition(m);
	}

	HandleCollisions();
}

/**
 * Allows the user to set the collision type.
 *
 * @param elastic true if the collisions should be elastic
 */
void FewBodyEngine::SetElasticCollisions(bool elastic) {
	elastic_collisions_ = elastic;
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
	for (const Body &m : bodies_) {
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
	return body.velocity + (acceleration * time_interval_);
}

/**
* Calculates the new position of a body using its velocity.
*
* @param body the body being considered
* @return the new position of the body
*/
ofVec3f FewBodyEngine::CalculatePosition(const Body &body) const {
	return body.position + body.velocity * (float)time_interval_;
}

/**
 * Handles collisions of the bodies elastically or inelastically.
 */
void FewBodyEngine::HandleCollisions() {
	for (int i = 0; i < body_count_; i++) {
		for (int j = 0; j < body_count_; j++) {
			if (Intersect(i, j)	&& i != j) {
				Collide(i, j);
				return;
			}
		}
	}
}

/**
 * Helper function for collision detection. Takes two indices and returns if the
 * bodies at these indices are in contact.
 *
 * @param body1_idx the index of the first body in the bodies list
 * @param body2_idx the index of the second body in the bodies list
 * @return true if the bodies are in contact
 */
bool FewBodyEngine::Intersect(int body1_idx, int body2_idx) {
	double distance = bodies_[body1_idx].position.squareDistance(bodies_[body2_idx].position);
	double sum_radii = std::pow(CalculateRadius(bodies_[body1_idx].mass) 
							  + CalculateRadius(bodies_[body2_idx].mass), 2);
	
	return distance <= sum_radii;
}

/**
 * Helper function for collision handling. Calculates the new velocities of the bodies
 * depending on the type of collision. If the collision is inelastic, the function also
 * combines the two bodies, storing the result in the first body and deleting the second.
 *
 * Formulas taken from:
 *  - https://en.wikipedia.org/wiki/Elastic_collision
 *  - https://en.wikipedia.org/wiki/Inelastic_collision
 *
 * @param body1_idx the index of the first body in the bodies list
 * @param body2_idx the index of the second body in the bodies list
 */
void FewBodyEngine::Collide(int body1_idx, int body2_idx) {
	Body &body1 = bodies_[body1_idx];
	Body &body2 = bodies_[body2_idx];

	// Apply the appropriate collision handling strategy
	if (elastic_collisions_) {
		ofVec3f v1 = body1.velocity - (2 * body2.mass / (body1.mass + body2.mass)) * (body1.velocity - body2.velocity).dot(body1.position - body2.position) / (body1.position - body2.position).lengthSquared() * (body1.position - body2.position);
		ofVec3f v2 = body2.velocity - (2 * body1.mass / (body1.mass + body2.mass)) * (body2.velocity - body1.velocity).dot(body2.position - body1.position) / (body2.position - body1.position).lengthSquared() * (body2.position - body1.position);

		body1.velocity = v1;
		body2.velocity = v2;
	} else {
		// If the collision is inelastic, use body1 as the new body and update both its mass and velocity
		// Formula for inelastic collision take from: 
		body1.velocity = body1.mass / (body1.mass * body2.mass) * body1.velocity
					+ body2.mass / (body1.mass * body2.mass) * body2.velocity;
		body1.mass = body1.mass + body2.mass;

		// Take the average of the color and position to make the collision appear more natural
		body1.color = (body1.color + body2.color) / 2;
		body1.position = (body1.position + body2.position) / 2;

		// Delete body 2 as it has been combined with body 1
		bodies_.erase(bodies_.begin() + body2_idx);
		body_count_--;
	}
}