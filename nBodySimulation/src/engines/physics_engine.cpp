#include "physics_engine.h"



PhysicsEngine::PhysicsEngine()
{
}


PhysicsEngine::~PhysicsEngine() {
	// TODO: Rule of 5
}

void PhysicsEngine::AddBody(const ofVec3f pos, const ofVec3f v, double m) {
	Body* body = new Body(pos, v, m);
	bodies.push_back(body);
}

void PhysicsEngine::AddBody(double x, double y, double z, double v_x, double v_y, double v_z, double m) {
	Body* body = new Body(x, y, z, v_x, v_y, v_z, m);
	bodies.push_back(body);
}


vector<ofVec3f> PhysicsEngine::GetBodyPositions() const {
	vector<ofVec3f> positions;
	for (Body* m : bodies) {
		positions.push_back(m->position);
	}

	return positions;
}



