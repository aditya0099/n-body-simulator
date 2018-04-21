#include "catch.hpp"
#include "engines\few_body.h"
#include "ofVec3f.h"

TEST_CASE("Single body moves", "[few]") {
	FewBodyEngine fbe(1);
	fbe.AddBody(0, 0, 0, 2, 4, 6, 1);
	fbe.update();
	
	ofVec3f expected(2, 4, 6);

	REQUIRE(fbe.GetBodyPositions()[0] == expected);
}

TEST_CASE("Single body moves at constant velocity", "[few]") {
	FewBodyEngine fbe(1);
	fbe.AddBody(0, 0, 0, 1, 2, 3, 1);

	for (int i = 0; i < 10; i++) {
		ofVec3f expected(i*1, i*2, i*3);
		REQUIRE(fbe.GetBodyPositions()[0] == expected);
	}
}