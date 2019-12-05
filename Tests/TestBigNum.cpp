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
            const BigNum a("1234567890");
            const BigNum b("9876543210");
            REQUIRE(add(a, b, mod) == BigNum("11111111100"));
        }

        SECTION( "with modification" ) {
            const BigNum a("12345678907777456243534");
            const BigNum b("12345600077741235700399");
            REQUIRE(add(a, b, mod) == BigNum("210049889585"));
        }
    }

    SECTION( "Subtract BigNum" ) {
        const BigNum mod("666666666666");

        SECTION( "normal" ) {
            const BigNum a("123456789000");
            const BigNum b("67335999999");
            REQUIRE(subtract(a, b, mod) == BigNum("56120789001"));
        }

        SECTION( "with modification" ) {
            const BigNum a("12345678907777456243534");
            const BigNum b("1234560007774123570039999");
            REQUIRE(subtract(a, b, mod) == BigNum("431671874667"));
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
        SECTION( "easy" ) {
            const BigNum a("1");
            const BigNum b("2");
            REQUIRE(a % b == 1_bn);
            REQUIRE(a / b == 0_bn);
        }

        SECTION( "normal" ) {
            const BigNum a("123456");
            const BigNum b("322");
            REQUIRE(extract(a, b).first == BigNum("383"));
            REQUIRE(extract(a, b).second == BigNum("130"));
        }

        SECTION( "difficult" ) {
            const BigNum a("1234567890");
            const BigNum b("890890");
            REQUIRE(extract(a, b).first == BigNum("1385"));
            REQUIRE(extract(a, b).second == BigNum("685240"));
        }

        SECTION( "master" ) {
            const BigNum a("123456789012341");
            const BigNum b("89089012312345");
            REQUIRE(extract(a, b).first == BigNum("1"));
            REQUIRE(extract(a, b).second == BigNum("34367776699996"));
        }

        SECTION( "veteran" ) {
            const BigNum a("31415926535897932384626433");
            const BigNum b("832795028841971");
            REQUIRE(extract(a, b).first == BigNum("37723479905"));
            REQUIRE(extract(a, b).second == BigNum("393943945533678"));
        }

        SECTION( "impossible" ) {
            const BigNum a("49951059731732816096318595024459455346908302642522308253344685035261931188171010003137838752886587533208381420617177669147303");
            const BigNum b("185778053217122680661300192787661119590921642");
            REQUIRE(extract(a, b).first == BigNum("268874922880981921356444837383660471746363637968708614244631874788091837363196835"));
            REQUIRE(extract(a, b).second == BigNum("1540141020615185186336802365801588561744233"));
        }

        SECTION( "additional" ) {
            const lab::BigNum a("800012");
            const lab::BigNum b("2");
            const auto res = extract(800012_bn, 2_bn);
            REQUIRE(res.first == lab::BigNum("400006"));
            REQUIRE(res.second == lab::BigNum("0"));
        }
    }

    SECTION( "Multiplication" ) {
        SECTION("Common") {
            const auto a = 999999999_bn;
            const auto b = 999999999_bn;
            REQUIRE(a * b == 999999998000000001_bn);
        }

        SECTION ( "Rare" ) {
            const auto a = 99999123456789098765432112345678909876543219999_bn;
            const auto b = 9999101010101000010130929493583285892397887897238874399999_bn;
            REQUIRE(a * b == 999901336365994481304641755778280969957261726037535427297722733918150118427240475620078108944452582380001_bn);
        }
    }

    SECTION( "Modulo multiplication" ) {
        const auto a = 4241229841928441249124921409124091221_bn;
        const auto b = 12901092091309210942109410951309019490_bn;
        const auto mod = 120130924091094109_bn;
        REQUIRE(multiply(a, b, mod) == 88191807529973443_bn);
    }

    SECTION( "Inverse number" ) {
        REQUIRE(inverted(1442141324241124_bn, 23321723123_bn, BigNum::InversionPolicy::Euclid) == 515791030_bn);
        REQUIRE(inverted(1442141324241124_bn, 191_bn, BigNum::InversionPolicy::Fermat) == 12_bn);
    }

    SECTION( "Square root" ) {
        REQUIRE_FALSE(sqrt(2_bn, 4_bn).has_value());
        REQUIRE(sqrt(4_bn, 17_bn).value() == std::pair(2_bn, 15_bn));
        REQUIRE(sqrt(2_bn, 7_bn).value() == std::pair(4_bn, 3_bn));
        REQUIRE(sqrt(10007_bn, 20011_bn) == std::pair(5382_bn, 14629_bn));
    }

    SECTION("Calculate Montgomery coefficient") {
        {
            const auto mod = 23321723123_bn;
            REQUIRE(calculateMontgomeryCoefficient(mod) == 100000000000_bn);
        }
        {
            const auto mod = 101_bn;
            REQUIRE(calculateMontgomeryCoefficient(mod) == 1000_bn);
        }
        {
            const auto mod = 123421453_bn;
            REQUIRE(calculateMontgomeryCoefficient(mod) == 1000000000_bn);
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
        {
            const auto left = 96_bn;
            const auto right = 94_bn;
            const auto mod = 101_bn;
            const auto montgomery_coefficient = 1000_bn;
            const auto mc_inverted = inverted(montgomery_coefficient, mod, lab::BigNum::InversionPolicy::Euclid);
            const auto coefficient = extract(montgomery_coefficient * mc_inverted - 1_bn, mod).first;
            REQUIRE(multiplyMontgomery(left, right, mod, montgomery_coefficient, coefficient) == 47_bn);
        }
        {
            const auto left = 96_bn;
            const auto right = 94_bn;
            const auto mod = 101_bn;
            const auto montgomery_coefficient = 1000_bn;
            const auto mc_inverted = inverted(montgomery_coefficient, mod, lab::BigNum::InversionPolicy::Euclid);
            const auto coefficient = extract(montgomery_coefficient * mc_inverted - 1_bn, mod).first;
            REQUIRE(multiplyMontgomery(left, right, mod, montgomery_coefficient, coefficient) == 47_bn);
        }
        {
            const auto left = 96_bn;
            const auto right = 94_bn;
            const auto mod = 101_bn;
            const auto montgomery_coefficient = 1000_bn;
            const auto mc_inverted = inverted(montgomery_coefficient, mod, lab::BigNum::InversionPolicy::Euclid);
            const auto coefficient = extract(montgomery_coefficient * mc_inverted - 1_bn, mod).first;
            REQUIRE(multiplyMontgomery(left, right, mod, montgomery_coefficient, coefficient) == 47_bn);
        }
    }

    SECTION("Pow, using Montgomery form") {
        {
            const auto base = 99999993333399992_bn;
            const auto degree = 333334554342_bn;
            const auto mod = 17_bn;
            REQUIRE(powMontgomery(base, degree, mod) == 1_bn);
        }
        {
            const auto base = 2_bn;
            const auto degree = 5_bn;
            const auto mod = 17_bn;
            REQUIRE(powMontgomery(base, degree, mod) == 15_bn);
        }
        {
            const auto base = 999999933333_bn;
            const auto degree = 3333_bn;
            const auto mod = 17_bn;
            REQUIRE(powMontgomery(base, degree, mod) == 5_bn);
        }
        {
            const auto base = 100_bn;
            const auto degree = 100_bn;
            const auto mod = 101_bn;
            REQUIRE(powMontgomery(base, degree, mod) == 1_bn);
        }
        {
            const auto base = 1234512345_bn;
            const auto degree = 123123_bn;
            const auto mod = 6243379_bn;
            REQUIRE(powMontgomery(base, degree, mod) == 1363736_bn);
        }
        {
            const auto base = 1234512345_bn;
            const auto degree = 123123_bn;
            const auto mod = 624334409_bn;
            REQUIRE(powMontgomery(base, degree, mod) == 166746373_bn);
        }
        {
            const auto base = 12345123455485945_bn;
            const auto degree = 12312312341234_bn;
            const auto mod = 624334409_bn;
            REQUIRE(powMontgomery(base, degree, mod) == 404851936_bn);
        }
    }

    SECTION("Length of BigNum") {
        {
            const auto num = 101_bn;
            REQUIRE(length(num) == 3);
        }
        {
            const auto num = 101933321254431244150903214_bn;
            REQUIRE(length(num) == 27);
        }
        {
            const auto num = 1019333212544312441509032_bn;
            REQUIRE(length(num) == 25);
        }
    }

    SECTION("BigNum element order") {
        {
            const auto num = 8_bn;
            const auto mod = 17_bn;
            REQUIRE(powMontgomery(num, elementOrder(num, mod), mod) == 1_bn);
        }
        {
            const auto num = 453_bn;
            const auto mod = 9227_bn;
            REQUIRE(powMontgomery(num, elementOrder(num, mod), mod) == 1_bn);
        }
        {
            const auto num = 4420_bn;
            const auto mod = 9227_bn;
            REQUIRE(powMontgomery(num, elementOrder(num, mod), mod) == 1_bn);
        }
    }
 
    SECTION("Factorization II"){
        SECTION("Rudenko"){
            const auto num = 15_bn;
            std::vector<std::pair<BigNum, BigNum>> result = {{3_bn, 1_bn}, {5_bn, 1_bn}};
            REQUIRE(factorization(num) == result);
        }

        SECTION("Tiapko"){
            const auto num = 108_bn;
            std::vector<std::pair<BigNum, BigNum>> result = {{2_bn, 2_bn}, {3_bn, 3_bn}};
            REQUIRE(factorization(num) == result);
        }

        SECTION("Hryhorchuk"){
            const auto num = 461332_bn;
            std::vector<std::pair<BigNum, BigNum>> result = {{2_bn, 2_bn},
                                                             {29_bn, 1_bn},
                                                             {41_bn, 1_bn},
                                                             {97_bn, 1_bn}};
            REQUIRE(factorization(num) == result);
        }

        SECTION("Oleksyshyn"){
            const auto num = 87348672309467038662900_bn;
            std::vector<std::pair<BigNum, BigNum>> result = {{2_bn, 2_bn},
                                                             {3_bn, 4_bn},
                                                             {5_bn, 2_bn},
                                                             {4421_bn, 1_bn},
                                                             {8863_bn, 1_bn},
                                                             {275213684783_bn, 1_bn}};
            REQUIRE(factorization(num) == result);
        }
    }

    SECTION("sqrt of BigNum") {

        SECTION("easy") {
            {
                const auto num = 8_bn;
                REQUIRE(sqrt(num) == 2_bn);
            }
            {
                const auto num = 25_bn;
                REQUIRE(sqrt(num) == 5_bn);
            }
            {
                const auto num = 101_bn;
                REQUIRE(sqrt(num) == 10_bn);
            }
            {
                const auto num = 260_bn;
                REQUIRE(sqrt(num) == 16_bn);
            }
            {
                const auto num = 0_bn;
                REQUIRE(sqrt(num) == 0_bn);
            }
            {
                const auto num = 1_bn;
                REQUIRE(sqrt(num) == 1_bn);
            }
            {
                const auto num = 3_bn;
                REQUIRE(sqrt(num) == 1_bn);
            }
        }

        SECTION("normal") {
            {
                const auto num = 123443_bn;
                REQUIRE(sqrt(num) == 351_bn);
            }
            {
                const auto num = 77777_bn;
                REQUIRE(sqrt(num) == 278_bn);
            }
            {
                const auto num = 100984_bn;
                REQUIRE(sqrt(num) == 317_bn);
            }
            {
                const auto num = 87543000_bn;
                REQUIRE(sqrt(num) == 9356_bn);
            }
            {
                const auto num = 1000000000_bn;
                REQUIRE(sqrt(num) == 31622_bn);
            }
        }

        SECTION("difficult") {
            {
                const auto num = 124618746182765925923859238750_bn;
                REQUIRE(sqrt(num) == 353013804521531_bn);
            }
            {
                const auto num = 78357937926598235037609376072096706_bn;
                REQUIRE(sqrt(num) == 279924879077580803_bn);
            }
            {
                const auto num = 209352075289659265983270437673534636322_bn;
                REQUIRE(sqrt(num) == 14469003949465881114_bn);
            }
            {
                const auto num = 138429562952385082365083608058283063760_bn;
                REQUIRE(sqrt(num) == 11765609331963435643_bn);
            }
            {
                const auto num = 348563496834760374863470673046703476037_bn;
                REQUIRE(sqrt(num) == 18669855297638500306_bn);
            }
        }
    }

    SECTION("log of BigNum") {
        SECTION("easy") {
            {
                REQUIRE(logStep(57_bn, 3_bn, 113_bn) == 100_bn);
            }
            {
                REQUIRE(logStep(1_bn, 2_bn, 1000_bn) == 0_bn);
            }
            {
                REQUIRE(logStep(40_bn, 10_bn, 127_bn) == 13_bn);
            }
            {
                REQUIRE(logStep(88_bn, 17_bn, 149_bn) == 20_bn);
            }
            {
                REQUIRE(logStep(80_bn, 43_bn, 181_bn) == 26_bn);
            }
            {
                REQUIRE(logStep(74_bn, 9_bn, 163_bn) == 13_bn);
            }
        }
        SECTION("normal") {
            {
                REQUIRE(logStep(47_bn, 142_bn, 367_bn) == 38_bn);
            }
            {
                REQUIRE(logStep(244_bn, 99_bn, 257_bn) == 71_bn);
            }
            {
                REQUIRE(logStep(276_bn, 117_bn, 449_bn) == 101_bn);
            }
            {
                REQUIRE(logStep(48_bn, 261_bn, 683_bn) == 333_bn);
            }
            {
                REQUIRE(logStep(718_bn, 391_bn, 947_bn) == 72_bn);
            }
        }
        SECTION("difficult") {
            {
                REQUIRE(logStep(46304_bn, 1234_bn, 1000669_bn) == 333867_bn);
            }
            {
                REQUIRE(logStep(207775_bn, 512_bn, 1012861_bn) == 44112_bn);
            }
            {
                REQUIRE(logStep(1041299_bn, 46327_bn, 2511953_bn) == 81743_bn);
            }
            {
                REQUIRE(logStep(2749733_bn, 95518_bn, 3920239_bn) == 39227_bn);
            }
        }
    }
}
