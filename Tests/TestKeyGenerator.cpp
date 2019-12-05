#include <BigNum.hpp>
#include <EllipticCurves.hpp>
#include <PredefineEllipticCurves.hpp>
#include <KeyGenerator.h>

#include "catch.hpp"

TEST_CASE("Key generation test","[keyGen]") {
    using namespace lab;

    SECTION("Testing client"){
        SECTION("Public key on curve"){
            auto bob = Client (curveDataBase[1].curves[0], 98765678909876523456788_bn, Point(262_bn, 0_bn));
            REQUIRE(curveDataBase[1].curves[0].contains(bob.getPublicKey()) == true);
        }
        SECTION("Public key on curve"){
            auto ali = Client (curveDataBase[1].curves[0], 98765678909876523456788_bn, Point(262_bn, 0_bn));
            auto bob = Client (curveDataBase[1].curves[0], 987657904356814_bn, Point(262_bn, 0_bn));
            bob.setPrivateKey(ali.getPublicKey());
            REQUIRE(curveDataBase[1].curves[0].contains(bob.getPrivateKey()) == true);

        }
    }

    SECTION("Comparing got private keys"){
        SECTION("Easy"){
            auto sim = GettingKeySimulation(curveDataBase[1].curves[0],4_bn, 2_bn, Point(262_bn, 0_bn));
            REQUIRE(sim.getAlicePrivateKey() == sim.getBobPrivateKey());
        }
        SECTION("Not so easy"){
            auto sim = GettingKeySimulation(curveDataBase[1].curves[0],987657904356814_bn, 98765678909876523456788_bn, Point(262_bn, 0_bn));
            REQUIRE(sim.getAlicePrivateKey() == sim.getBobPrivateKey());
        }
    }

}
