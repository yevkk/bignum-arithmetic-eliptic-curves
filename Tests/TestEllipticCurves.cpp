#include <EllipticCurves.hpp>

#include "catch.hpp"

TEST_CASE("Elliptic curves test", "[curves]") {	
	lab::EllipticCurve c(new lab::Field(73_bn), 60_bn, 61_bn);
	lab::Point a = c.add({ 72_bn,0_bn }, { 72_bn,0_bn });
	std::cout << a.x <<" "<< a.y << std::endl;
}
