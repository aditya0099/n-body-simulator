#include "catch.hpp"


#include "../src/engines/few_body.h"
#include "../src/engines/physics_engine.h"

TEST_CASE("Single body moves at a constant velocity", "[few_body]") {
	FewBodyEngine engine(1.0);
	engine.AddBody(0.0, 0.0, 0.0, 1.0, 2.0, 3.0, 1.0);

	engine.update();
	//ofVec3df = engine.GetBodyPositions()[0];
	
	
}

TEST_CASE("", "[few_body]") {

}

TEST_CASE("", "[few_body]") {

}

TEST_CASE("", "[few_body]") {

}

TEST_CASE("", "[few_body]") {

}

TEST_CASE("", "[few_body]") {

}

TEST_CASE("", "[few_body]") {

}

TEST_CASE("", "[few_body]") {

}