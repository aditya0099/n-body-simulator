#include "point.h"
#include "ofVec3f.h"
#include "utils.h"

ofVec3f PointAsVector(Point<3> point) {
	return ofVec3f(point[0], point[1], point[2]);
}

Point<3> VectorAsPoint(ofVec3f vec) {
	return Point<3>(vec[0], vec[1], vec[2]);
}

vector<Point<3> > VectorsAsPoints(vector<ofVec3f> vectors) {
	vector<Point<3> > points;
	for (ofVec3f vec : vectors) {
		points.push_back(VectorAsPoint(vec));
	}

	return points;
}

vector<ofVec3f> PointsAsVectors(vector<Point<3> > points) {
	vector<ofVec3f> vectors;
	for (Point<3> pt : points) {
		vectors.push_back(PointAsVector(pt));
	}

	return vectors;
}