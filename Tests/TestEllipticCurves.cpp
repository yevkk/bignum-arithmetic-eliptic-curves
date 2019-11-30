#include <EllipticCurves.hpp>
#include <PredefineEllipticCurves.hpp>
using lab::curveDataBase;

#include <sstream>

#include "catch.hpp"

TEST_CASE("Elliptic curves test", "[curves]") {
   SECTION("Streaming an Elliptic Curve") {
       std::stringstream out;
       out << curveDataBase[0].curves[0];
       REQUIRE(out.str() == "y^2 = x^3 + 228960*x + 91781 mod 234131");
    }

    SECTION("Check if a point belongs to curve") {
        SECTION("Belongs") {
            lab::Point p = { 89_bn,320_bn };
            REQUIRE(curveDataBase[0].curves[0].contains(p) == true);
        }
        
        SECTION("Doesn't belong") {
            lab::Point p = { 364738_bn, 9585794_bn };
            REQUIRE(curveDataBase[1].curves[0].contains(p) == false);
        }
    }

    SECTION("Find points by x-coordinate") {

    }

    SECTION("Inverted point") {
        SECTION("Regular point") {
            lab::Point p = { 535_bn, 12444_bn };
            lab::Point expected = { 535_bn, 221687_bn };
            REQUIRE(expected == curveDataBase[0].curves[2].inverted(p));
        }
        SECTION("Point with y = 0") {
            lab::Point p = { 234131_bn, 0_bn };
            REQUIRE(p == curveDataBase[0].curves[2].inverted(p));
        }
    }
    
    

    SECTION("Add 2 points") {
        SECTION("Easy") {
            lab::Point p1 = { 769_bn, 7_bn };
            lab::Point p2 = {70_bn,585_bn};
            lab::Point expected = { 519_bn, 149_bn};
            REQUIRE(expected == curveDataBase[2].curves[0].add(p1,p2));
        }
        SECTION("Normal") {
            lab::Point p1 = { 2570_bn, 130216_bn};
            lab::Point p2 = { 110_bn,574_bn };
            lab::Point expected = { 96091_bn, 21870_bn };
            REQUIRE(expected == curveDataBase[0].curves[2].add(p1, p2));
        }
        SECTION("Challenging") {
            //using std::cout, std::endl;
            //lab::Point p = curveDataBase[1].curves[2].add({ 1653_bn,153340_bn }, { 3333_bn, 100_bn });
            //cout << lab::inverted(1680_bn,80000005213_bn,lab::BigNum::InversionPolicy::Euclid) << endl;
            //cout << curveDataBase[1].curves[2].contains(p) << endl;

            //lab::Point p1 = { , };
            //lab::Point p2 = { , };
            //lab::Point expected = { , };
            //REQUIRE(expected == curveDataBase[1].curves[2].add(p1, p2));
        }
        SECTION("Neutral point") {
            lab::Point p1 = {89_bn,320_bn};
            lab::Point p2 = { 89_bn,233811_bn };
            REQUIRE(lab::EllipticCurve::neutral == curveDataBase[0].curves[0].add(p1, p2));
        }
    }

    system("pause");
}
