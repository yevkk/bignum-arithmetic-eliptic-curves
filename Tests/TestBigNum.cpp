#include <BigNum.hpp>

#include <sstream>

#include "catch.hpp"

TEST_CASE("Big numbers test", "[BigNum]") {
    SECTION( "Streaming a BigNum" ) {
        lab::BigNum num;

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
            const lab::BigNum num(in);
            std::stringstream out;
            out << num;
            REQUIRE(out.str() == in);
            REQUIRE(to_string(num) == in);
        }
        SECTION( "leading zeros" ) {
            const std::string in = "12345678901234567890";
            const lab::BigNum num("0000000000000" + in);
            std::stringstream out;
            out << num;
            REQUIRE(out.str() == in);
            REQUIRE(to_string(num) == in);
        }
    }

    SECTION( "Add BigNum" ) {
        const lab::BigNum mod("666666666666");
        SECTION( "normal" ) {
            const lab::BigNum num1("1234567890");
            const lab::BigNum num2("9876543210");
            REQUIRE(add(num1, num2, mod) == lab::BigNum("11111111100"));
        }
        SECTION( "with modification" ) {
            const lab::BigNum num1("12345678907777456243534");
            const lab::BigNum num2("12345600077741235700399");
            REQUIRE(add(num1, num2, mod) == lab::BigNum("210049889585"));
        }
    }

    SECTION( "Subtract BigNum" ) {
        const lab::BigNum mod("666666666666");
        SECTION( "normal" ) {
            const lab::BigNum num1("123456789000");
            const lab::BigNum num2("67335999999");
            REQUIRE(subtract(num1, num2, mod) == lab::BigNum("56120789001"));
        }
        SECTION( "with modification" ) {
            const lab::BigNum num1("12345678907777456243534");
            const lab::BigNum num2("1234560007774123570039999");
            REQUIRE(subtract(num1, num2, mod) == lab::BigNum("431671874667"));
        }
    }

    SECTION( "BigNum <" ) {
        SECTION( "less" ) {
            const lab::BigNum a("1234567890");
            const lab::BigNum b("1234667890");
            REQUIRE(a < b);
        }
        SECTION( "equal" ) {
            const lab::BigNum a("1234567890");
            const lab::BigNum b("1234567890");
            REQUIRE(!(a < b));
        }
        SECTION( "bigger" ) {
            const lab::BigNum a("2234568890");
            const lab::BigNum b("2234567890");
            REQUIRE(!(a < b));
        }
    }

    SECTION( "BigNum >" ) {
        SECTION( "less" ) {
            const lab::BigNum a("1234567890");
            const lab::BigNum b("1234667890");
            REQUIRE(b > a);
        }
        SECTION( "equal" ) {
            const lab::BigNum a("1234567890");
            const lab::BigNum b("1234567890");
            REQUIRE(!( b > a));
        }
        SECTION( "bigger" ) {
            const lab::BigNum a("2234568890");
            const lab::BigNum b("2234567890");
            REQUIRE(!(b > a));
        }
    }

    SECTION( "BigNum <=" ) {
        SECTION( "less" ) {
            const lab::BigNum a("1234567890");
            const lab::BigNum b("1234667890");
            REQUIRE(a <= b);
        }
        SECTION( "equal" ) {
            const lab::BigNum a("1234567890");
            const lab::BigNum b("1234567890");
            REQUIRE(a <= b);
        }
        SECTION( "bigger" ) {
            const lab::BigNum a("2234568890");
            const lab::BigNum b("2234567890");
            REQUIRE(!(a <= b));
        }
    }

    SECTION( "BigNum >=" ) {
        SECTION( "less" ) {
            const lab::BigNum a("1234567890");
            const lab::BigNum b("1234667890");
            REQUIRE(b >= a);
        }
        SECTION( "equal" ) {
            const lab::BigNum a("1234567890");
            const lab::BigNum b("1234567890");
            REQUIRE( b >= a);
        }
        SECTION( "bigger" ) {
            const lab::BigNum a("2234568890");
            const lab::BigNum b("2234567890");
            REQUIRE(!(b >= a));
        }
    }

    SECTION( "BigNum ==" ) {
        SECTION( "less" ) {
            const lab::BigNum a("1234567890");
            const lab::BigNum b("1234667890");
            REQUIRE(!(a == b));
        }
        SECTION( "equal" ) {
            const lab::BigNum a("1234567890");
            const lab::BigNum b("1234567890");
            REQUIRE(a == b);
        }
        SECTION( "bigger" ) {
            const lab::BigNum a("2234568890");
            const lab::BigNum b("2234567890");
            REQUIRE(!(a == b));
        }
    }

    SECTION( "Copy" ) {
        SECTION( "test" ) {
            const lab::BigNum a("1234567890");
            lab::BigNum b;
            b = a;
            REQUIRE(a == b);
        }
    }

    SECTION( "Multiply" ) {
        SECTION( "test" ) {
            const lab::BigNum a("7752362423526235624");
            REQUIRE(a * 791 == lab::BigNum("6132118677009252378584"));
        }
    }

    SECTION( "Extract BigNum" ) {
        const lab::BigNum num1("123456");

        SECTION( "easy" ) {
            const lab::BigNum num2("123");
            REQUIRE(extract(num1, num2).first == lab::BigNum("1003"));
            REQUIRE(extract(num1, num2).second == lab::BigNum("87"));
        }
        SECTION( "normal" ) {
            const lab::BigNum num2("322");
            REQUIRE(extract(num1, num2).first == lab::BigNum("383"));
            REQUIRE(extract(num1, num2).second == lab::BigNum("130"));
        }
        SECTION( "difficult" ) {
            const lab::BigNum num1("1234567890");
            const lab::BigNum num2("890890");
            REQUIRE(extract(num1, num2).first == lab::BigNum("1385"));
            REQUIRE(extract(num1, num2).second == lab::BigNum("685240"));
        }
        SECTION( "master" ) {
            const lab::BigNum num1("123456789012341");
            const lab::BigNum num2("89089012312345");
            REQUIRE(extract(num1, num2).first == lab::BigNum("1"));
            REQUIRE(extract(num1, num2).second == lab::BigNum("34367776699996"));
        }
        SECTION( "veteran" ) {
            const lab::BigNum num1("31415926535897932384626433");
            const lab::BigNum num2("832795028841971");
            REQUIRE(extract(num1, num2).first == lab::BigNum("37723479905"));
            REQUIRE(extract(num1, num2).second == lab::BigNum("393943945533678"));
        }
        SECTION( "impossible" ) {
            const lab::BigNum num1("499510597317328160963185950244594553469083026425223082533446850352619311881"
                             "71010003137838752886587533208381420617177669147303");
            const lab::BigNum num2("185778053217122680661300192787661119590921642");
            REQUIRE(extract(num1, num2).first == lab::BigNum("268874922880981921356444837383660471746363637968708614244631874788091837363196835"));
            REQUIRE(extract(num1, num2).second == lab::BigNum("1540141020615185186336802365801588561744233"));
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

            REQUIRE(inverted(a, mod, lab::BigNum::InversionPolicy::Euclid) == 515791030_bn);
        }
        {
            const auto a = 1442141324241124_bn;
            const auto mod = 191_bn;
            REQUIRE(inverted(a, mod, lab::BigNum::InversionPolicy::Fermat) == 12_bn);
        }
    }

    SECTION("Calculate Montgomery coefficient") {
        {
            const auto mod = 23321723123_bn;
            REQUIRE(calculateMontgomeryCoefficient(mod) == 23321723124_bn);
        }
        {
            const auto mod = 101_bn;
            REQUIRE(calculateMontgomeryCoefficient(mod) == 10000000000_bn);
        }
    }

    SECTION("Convert to Montgomery form") {
        SECTION("Common") {
            {
                const auto num = 3_bn;
                const auto mod = 17_bn;
                const auto montgomery_coefficient = 100_bn;
                REQUIRE(convertToMontgomeryForm(num, mod, montgomery_coefficient) == 11_bn);
            }
            {
                const auto num = 5_bn;
                const auto mod = 17_bn;
                const auto montgomery_coefficient = 100_bn;
                REQUIRE(convertToMontgomeryForm(num, mod, montgomery_coefficient) == 7_bn);
            }
            {
                const auto num = 7_bn;
                const auto mod = 17_bn;
                const auto montgomery_coefficient = 100_bn;
                REQUIRE(convertToMontgomeryForm(num, mod, montgomery_coefficient) == 3_bn);
            }
            {
                const auto num = 15_bn;
                const auto mod = 17_bn;
                const auto montgomery_coefficient = 100_bn;
                REQUIRE(convertToMontgomeryForm(num, mod, montgomery_coefficient) == 4_bn);
            }
        }
        SECTION("Pro") {
            {
                const auto num = 3_bn;
                const auto mod = 101_bn;
                const auto montgomery_coefficient = 10000000000_bn;
                REQUIRE(convertToMontgomeryForm(num, mod, montgomery_coefficient) == 98_bn);
            }
            {
                const auto num = 5_bn;
                const auto mod = 211_bn;
                const auto montgomery_coefficient = 10000000000_bn;
                REQUIRE(convertToMontgomeryForm(num, mod, montgomery_coefficient) == 136_bn);
            }
            {
                const auto num = 31415926535_bn;
                const auto mod = 101_bn;
                const auto montgomery_coefficient = 10000000000_bn;
                REQUIRE(convertToMontgomeryForm(num, mod, montgomery_coefficient) == 43_bn);
            }
        }
    }

    SECTION("Multiply in Montgomery form") {
        {
            const auto left = 3_bn;
            const auto right = 4_bn;
            const auto mod = 17_bn;
            const auto montgomery_coefficient = 100_bn;
            const auto coefficient = 47_bn;
            REQUIRE(multiplyMontgomery(left, right, mod, montgomery_coefficient, coefficient) == 11_bn);
        }
    }
}
