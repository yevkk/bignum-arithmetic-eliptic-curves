#include <BigNum.hpp>

#include <sstream>

#include "catch.hpp"

TEST_CASE("Big numbers test", "[BigNum]") {
    using namespace lab;

    SECTION( "Streaming a BigNum" ) {
        BigNum num;

        SECTION("normal") {
            const std::string in = "1234567890";
            std::istringstream iss(in);
            iss >> num;
            std::stringstream out;
            out << num;
            REQUIRE(out.str() == in);
        }
        SECTION( "leading zeros" ) {
            const std::string in = "000000000001234567890";
            const std::string expect = "1234567890";
            std::istringstream iss(in);
            iss >> num;
            std::stringstream out;
            out << num;
            REQUIRE(out.str() == expect);
        }
    }

    SECTION( "BigNum from/to string" ) {
        SECTION( "normal" ) {
            const std::string in = "12345678901234567890";
            const auto num = BigNum{in};
            std::stringstream out;
            out << num;
            REQUIRE(out.str() == in);
            REQUIRE(to_string(num) == in);
        }
        SECTION( "leading zeros" ) {
            const std::string in = "12345678901234567890";
            const BigNum num("0000000000000" + in);
            std::stringstream out;
            out << num;
            REQUIRE(out.str() == in);
            REQUIRE(to_string(num) == in);
        }
    }

    SECTION( "Add BigNum" ) {
        const BigNum mod("666666666666");
        SECTION( "normal" ) {
            const BigNum num1("1234567890");
            const BigNum num2("9876543210");
            REQUIRE(add(num1, num2, mod) == BigNum("11111111100"));
        }
        SECTION( "with modification" ) {
            const BigNum num1("12345678907777456243534");
            const BigNum num2("12345600077741235700399");
            REQUIRE(add(num1, num2, mod) == BigNum("210049889585"));
        }
    }

    SECTION( "Subtract BigNum" ) {
        const BigNum mod("666666666666");
        SECTION( "normal" ) {
            const BigNum num1("123456789000");
            const BigNum num2("67335999999");
            REQUIRE(subtract(num1, num2, mod) == BigNum("56120789001"));
        }
        SECTION( "with modification" ) {
            const BigNum num1("12345678907777456243534");
            const BigNum num2("1234560007774123570039999");
            REQUIRE(subtract(num1, num2, mod) == BigNum("431671874667"));
        }
    }

    SECTION( "BigNum <" ) {
        SECTION( "less" ) {
            const BigNum a("1234567890");
            const BigNum b("1234667890");
            REQUIRE(a < b);
        }
        SECTION( "equal" ) {
            const BigNum a("1234567890");
            const BigNum b("1234567890");
            REQUIRE(!(a < b));
        }
        SECTION( "bigger" ) {
            const BigNum a("2234568890");
            const BigNum b("2234567890");
            REQUIRE(!(a < b));
        }
    }

    SECTION( "BigNum >" ) {
        SECTION( "less" ) {
            const BigNum a("1234567890");
            const BigNum b("1234667890");
            REQUIRE(b > a);
        }
        SECTION( "equal" ) {
            const BigNum a("1234567890");
            const BigNum b("1234567890");
            REQUIRE(!( b > a));
        }
        SECTION( "bigger" ) {
            const BigNum a("2234568890");
            const BigNum b("2234567890");
            REQUIRE(!(b > a));
        }
    }

    SECTION( "BigNum <=" ) {
        SECTION( "less" ) {
            const BigNum a("1234567890");
            const BigNum b("1234667890");
            REQUIRE(a <= b);
        }
        SECTION( "equal" ) {
            const BigNum a("1234567890");
            const BigNum b("1234567890");
            REQUIRE(a <= b);
        }
        SECTION( "bigger" ) {
            const BigNum a("2234568890");
            const BigNum b("2234567890");
            REQUIRE(!(a <= b));
        }
    }

    SECTION( "BigNum >=" ) {
        SECTION( "less" ) {
            const BigNum a("1234567890");
            const BigNum b("1234667890");
            REQUIRE(b >= a);
        }
        SECTION( "equal" ) {
            const BigNum a("1234567890");
            const BigNum b("1234567890");
            REQUIRE( b >= a);
        }
        SECTION( "bigger" ) {
            const BigNum a("2234568890");
            const BigNum b("2234567890");
            REQUIRE(!(b >= a));
        }
    }

    SECTION( "BigNum ==" ) {
        SECTION( "less" ) {
            const BigNum a("1234567890");
            const BigNum b("1234667890");
            REQUIRE(!(a == b));
        }
        SECTION( "equal" ) {
            const BigNum a("1234567890");
            const BigNum b("1234567890");
            REQUIRE(a == b);
        }
        SECTION( "bigger" ) {
            const BigNum a("2234568890");
            const BigNum b("2234567890");
            REQUIRE(!(a == b));
        }
    }

    SECTION( "Copy" ) {
        SECTION( "test" ) {
            const BigNum a("1234567890");
            BigNum b;
            b = a;
            REQUIRE(a == b);
        }
    }

    SECTION( "Multiply" ) {
        SECTION( "test" ) {
            const BigNum a("7752362423526235624");
            REQUIRE(a * 791 == BigNum("6132118677009252378584"));
        }
    }

    SECTION( "Extract BigNum" ) {
        const BigNum num1("123456");

        SECTION( "easy" ) {
            const BigNum num2("123");
            REQUIRE(extract(num1, num2).first == BigNum("1003"));
            REQUIRE(extract(num1, num2).second == BigNum("87"));
        }
        SECTION( "normal" ) {
            const BigNum num2("322");
            REQUIRE(extract(num1, num2).first == BigNum("383"));
            REQUIRE(extract(num1, num2).second == BigNum("130"));
        }
        SECTION( "difficult" ) {
            const BigNum num1("1234567890");
            const BigNum num2("890890");
            REQUIRE(extract(num1, num2).first == BigNum("1385"));
            REQUIRE(extract(num1, num2).second == BigNum("685240"));
        }
        SECTION( "master" ) {
            const BigNum num1("123456789012341");
            const BigNum num2("89089012312345");
            REQUIRE(extract(num1, num2).first == BigNum("1"));
            REQUIRE(extract(num1, num2).second == BigNum("34367776699996"));
        }
        SECTION( "veteran" ) {
            const BigNum num1("31415926535897932384626433");
            const BigNum num2("832795028841971");
            REQUIRE(extract(num1, num2).first == BigNum("37723479905"));
            REQUIRE(extract(num1, num2).second == BigNum("393943945533678"));
        }
        SECTION( "impossible" ) {
            const BigNum num1("499510597317328160963185950244594553469083026425223082533446850352619311881"
                             "71010003137838752886587533208381420617177669147303");
            const BigNum num2("185778053217122680661300192787661119590921642");
            REQUIRE(extract(num1, num2).first == BigNum("268874922880981921356444837383660471746363637968708614244631874788091837363196835"));
            REQUIRE(extract(num1, num2).second == BigNum("1540141020615185186336802365801588561744233"));
        }
    }

    SECTION("Multiplication") {

        SECTION("Common") {
            const auto a = 999999999_bn;
            const auto b = 999999999_bn;
            REQUIRE(a * b == 999999998000000001_bn);
        }

        SECTION ("Rare") {
            const auto a = 99999123456789098765432112345678909876543219999_bn;
            const auto b = 9999101010101000010130929493583285892397887897238874399999_bn;
            REQUIRE(a * b == 999901336365994481304641755778280969957261726037535427297722733918150118427240475620078108944452582380001_bn);
        }
    }

    SECTION("Modulo multiplication") {
        const auto a = 4241229841928441249124921409124091221_bn;
        const auto b = 12901092091309210942109410951309019490_bn;
        const auto mod = 120130924091094109_bn;
        REQUIRE(multiply(a, b, mod) == 88191807529973443_bn);
    }

    SECTION("Inverse number") {

        {
            const auto a = 1442141324241124_bn;
            const auto mod = 23321723123_bn;

            REQUIRE(inverted(a, mod, BigNum::InversionPolicy::Euclid) == 515791030_bn);
        }
        {
            const auto a = 1442141324241124_bn;
            const auto mod = 191_bn;
            REQUIRE(inverted(a, mod, BigNum::InversionPolicy::Fermat) == 12_bn);
        }
    }
}
