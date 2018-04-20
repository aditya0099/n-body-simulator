#include "physics_engine.h"



PhysicsEngine::PhysicsEngine()
{
}


PhysicsEngine::~PhysicsEngine() {
	// TODO: Rule of 5
}

void PhysicsEngine::AddBody(const vector<double>& pos, const vector<double>& v, double m) {
	Body* body = new Body(pos, v, m);
	bodies.push_back(body);
}

void PhysicsEngine::AddBody(double x, double y, double z, double v_x, double v_y, double v_z, double m) {
	Body* body = new Body(x, y, z, v_x, v_y, v_z, m);
	bodies.push_back(body);
}




