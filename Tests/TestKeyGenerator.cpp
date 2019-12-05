#include <BigNum.hpp>
#include <EllipticCurves.hpp>
#include <PredefineEllipticCurves.hpp>
#include <KeyGenerator.h>

#include "catch.hpp"

TEST_CASE("Key generation test","[keyGen]") {
    using namespace lab;

    SECTION("Testing client"){
        SECTION("Testing result of private key"){
            auto powA = 98765678909876523456788_bn, powB = 987657904356814_bn;
            auto curv = curveDataBase[1].curves[2];
            auto point = Point(3333_bn, 100_bn);
            auto ali = Client (curv, powA, point);
            auto bob = Client (curv, powB, point);
            bob.setPrivateKey(ali.getPublicKey());
            REQUIRE(bob.getPrivateKey() == curv.powerPoint(curv.powerPoint(point, powA), powB));

        }
    }

    SECTION("Comparing got private keys"){
        SECTION("Easy"){
            auto sim = GettingKeySimulation(curveDataBase[0].curves[2],4_bn, 2_bn, Point(535_bn, 12444_bn));
            REQUIRE(sim.getAlicePrivateKey() == sim.getBobPrivateKey());
        }
        SECTION("Brrrr, challenging") {
            auto sim = GettingKeySimulation(curveDataBase[1].curves[0],945674567654356435676543356814_bn, 9876565456434564378909876523456788_bn, Point(262_bn, 0_bn));
            REQUIRE(sim.getAlicePrivateKey() == sim.getBobPrivateKey());
        }
        SECTION("OOA OAA MMM"){
            auto sim = GettingKeySimulation(curveDataBase[2].curves[0],9876579045555555555555665433252634814_bn, 98775654587878846573465678909876523456788_bn, Point(7_bn, 18_bn));
            REQUIRE(sim.getAlicePrivateKey() == sim.getBobPrivateKey());
        }
        SECTION("Razryv"){
            auto sim = GettingKeySimulation(curveDataBase[2].curves[0],98765790455555555555555556654332526348149273494634050943266239450543726284505893673949377394504848_bn,
                                                                              9877565458785678846573465678909876523456085080457683470347583470587340570394750347603475094370943788_bn, Point(7_bn, 18_bn));
            REQUIRE(sim.getAlicePrivateKey() == sim.getBobPrivateKey());
        }
    }

}
