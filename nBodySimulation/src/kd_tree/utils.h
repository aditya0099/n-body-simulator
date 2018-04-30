#pragma once

#include "point.h"
#include "ofVec3f.h"

ofVec3f PointAsVector(Point<3> point);

Point<3> VectorAsPoint(ofVec3f vector);

vector<Point<3>> VectorsAsPoints(vector<ofVec3f> vectors);

vector<Point<3>> PointsAsVectors(vector<ofVec3f> vector);
