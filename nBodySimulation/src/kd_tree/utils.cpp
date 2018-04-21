#include "point.h"
#include "ofVec3f.h"
#include "utils.h"

ofVec3f PointAsVector(Point<3> point) {
	return ofVec3f(point[0], point[1], point[2]);
}

Point<3> VectorAsPoint(ofVec3f vector) {
	return Point<3>(vector[0], vector[1], vector[2]);
}