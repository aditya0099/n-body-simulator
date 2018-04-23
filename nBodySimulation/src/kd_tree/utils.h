#pragma once

#include "point.h"
#include "ofVec3f.h"

ofVec3f PointAsVector(Point<3> point);

Point<3> VectorAsPoint(ofVec3f vector);
