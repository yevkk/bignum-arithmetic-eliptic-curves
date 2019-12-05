#include <EllipticCurves.hpp>
#include <PredefineEllipticCurves.hpp>

#include <sstream>

#include "catch.hpp"

TEST_CASE("Elliptic curves test", "[curves]") {
    using namespace lab;

    SECTION("Streaming an Elliptic Curve") {
        std::stringstream out;
        out << curveDataBase[0].curves[0];
        REQUIRE(out.str() == "y^2 = x^3 + 228960*x + 91781 mod 234131");
    }

    SECTION("Check if a point belongs to curve") {
        SECTION("Belongs") {
            const lab::Point p = { 89_bn, 320_bn };
            REQUIRE(curveDataBase[0].curves[0].contains(p));
        }
        
        SECTION("Doesn't belong") {
            lab::Point p = { 364738_bn, 9585794_bn };
            REQUIRE_FALSE(curveDataBase[1].curves[0].contains(p));
        }
    }

    SECTION("Inverted point") {
        SECTION("Regular point") {
            const lab::Point p = { 535_bn, 12444_bn };
            const lab::Point expected = { 535_bn, 221687_bn };
            REQUIRE(expected == curveDataBase[0].curves[2].invertedPoint(p));
        }

        SECTION("Point with y = 0") {
            const lab::Point p = { 234117_bn, 0_bn };
            REQUIRE(p == curveDataBase[0].curves[2].invertedPoint(p));
        }
    }
    
    SECTION("Add 2 points") {
        SECTION("Easy") {
            const lab::Point p1 = { 769_bn, 7_bn };
            const lab::Point p2 = { 70_bn, 585_bn };
            const lab::Point expected = { 519_bn, 149_bn};
            REQUIRE(expected == curveDataBase[2].curves[0].addPoints(p1,p2));
        }

        SECTION("Normal") {
            const lab::Point p1 = { 2570_bn, 130216_bn};
            const lab::Point p2 = { 110_bn,574_bn };
            const lab::Point expected = { 96091_bn, 21870_bn };
            REQUIRE(expected == curveDataBase[0].curves[2].addPoints(p1, p2));
        }

        SECTION("Neutral point") {
            const lab::Point p1 = {89_bn,320_bn};
            const lab::Point p2 = { 89_bn,233811_bn };
            REQUIRE(lab::EllipticCurve::neutral == curveDataBase[0].curves[0].addPoints(p1, p2));
        }
    }

    SECTION("Point to the power"){
        SECTION("Power_0") {
            const lab::Point p1 = {3333_bn, 100_bn};
            REQUIRE(lab::EllipticCurve::neutral == curveDataBase[1].curves[2].powerPoint(p1,0_bn));
        }

        SECTION("Power_1"){
            const lab::Point p1 = {325_bn, 3192_bn};
            REQUIRE(p1 == curveDataBase[1].curves[0].powerPoint(p1,1_bn));
        }

        SECTION("Power_2") {
            const lab::Point p1 = {3333_bn, 100_bn};
            const lab::Point p2 = {3333_bn, 100_bn};
            REQUIRE(curveDataBase[1].curves[2].addPoints(p1,p2) == curveDataBase[1].curves[2].powerPoint(p1,2_bn));
        }

        SECTION("Power_3") {
            const lab::Point p1 = {325_bn, 3192_bn};
            REQUIRE(curveDataBase[1].curves[0].addPoints(curveDataBase[1].curves[0].addPoints(p1,p1),p1)
                    == curveDataBase[1].curves[0].powerPoint(p1,3_bn));
        }

        SECTION("Power_5") {
            const lab::Point p1 = {7_bn, 18_bn};
            lab::Point p2 = curveDataBase[2].curves[1].addPoints(p1, p1);
            for(int i = 3; i <= 5; i++){
                p2 = curveDataBase[2].curves[1].addPoints(p1, p2);
            }
            REQUIRE(p2 == curveDataBase[2].curves[1].powerPoint(p1, 5_bn));
        }

        SECTION("Power_8") {
            const lab::Point p1 = {10_bn, 30_bn};
            lab::Point p2 = curveDataBase[2].curves[2].addPoints(p1, p1);
            for(int i = 3; i <= 8; i++){
                p2 = curveDataBase[2].curves[2].addPoints(p1, p2);
            }
            REQUIRE(p2 == curveDataBase[2].curves[2].powerPoint(p1, 8_bn));
        }
    }

    SECTION("Point Order"){
        SECTION("Bortnik"){

        }

        SECTION("Golovach"){

        }
    }
}
