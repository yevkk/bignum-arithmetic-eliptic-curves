#include <BigNum.hpp>
#include <sstream>

#include "catch.hpp"

TEST_CASE("Big numbers test", "[BigNum]") {
    SECTION( "Streaming a BigNum" ) {
        lab::big::BigNum num;
        std::istream input();

        SECTION( "normal" ) {
            std::string in = "1234567890";
            std::istringstream iss (in);
            iss>>num;
            std::stringstream out;
            out<<num;
            REQUIRE(out.str() == in);
        }
        SECTION( "leading zeros" ) {
            std::string in = "000000000001234567890";
            std::string expect = "1234567890";
            std::istringstream iss (in);
            iss>>num;
            std::stringstream out;
            out<<num;
            REQUIRE(out.str() == expect);
        }
    }

    SECTION( "BigNum from/to string" ) {
        SECTION( "normal" ) {
            std::string in = "12345678901234567890";
            lab::big::BigNum num(in);
            std::stringstream out;
            out<<num;
            REQUIRE(out.str() == in);
            REQUIRE(num.str() == in);
        }
        SECTION( "leading zeros" ) {
            std::string in = "12345678901234567890";
            lab::big::BigNum num("0000000000000" + in);
            std::stringstream out;
            out<<num;
            REQUIRE(out.str() == in);
            REQUIRE(num.str() == in);
        }
    }

    SECTION( "Add BigNum" ) {
        lab::big::BigNum mod("666666666666");
        SECTION( "normal" ) {
            lab::big::BigNum num1("1234567890");
            lab::big::BigNum num2("9876543210");
            REQUIRE(add(num1, num2, mod) == lab::big::BigNum("11111111100"));
        }
        SECTION( "with modification" ) {
            lab::big::BigNum num1("12345678907777456243534");
            lab::big::BigNum num2("12345600077741235700399");
            REQUIRE(add(num1, num2, mod) == lab::big::BigNum("210049889585"));
        }
    }

    SECTION( "Subtract BigNum" ) {
        lab::big::BigNum mod("666666666666");
        SECTION( "normal" ) {
            lab::big::BigNum num1("123456789000");
            lab::big::BigNum num2("67335999999");
            REQUIRE(subtract(num1, num2, mod) == lab::big::BigNum("56120789001"));
        }
        SECTION( "with modification" ) {
            lab::big::BigNum num1("12345678907777456243534");
            lab::big::BigNum num2("1234560007774123570039999");
            REQUIRE(subtract(num1, num2, mod) == lab::big::BigNum("431671874667"));
        }
    }

    /// Other operators use '<', no need to check them
    SECTION( "BigNum <" ) {
        SECTION( "less" ) {
            lab::big::BigNum a ("1234567890");
            lab::big::BigNum b ("1234667890");
            REQUIRE(a < b);
        }
        SECTION( "equal" ) {
            lab::big::BigNum a ("1234567890");
            lab::big::BigNum b ("1234567890");
            REQUIRE(!(a < b));
        }
        SECTION( "bigger" ) {
            lab::big::BigNum a ("2234568890");
            lab::big::BigNum b ("2234567890");
            REQUIRE(!(a < b));
        }
    }

    SECTION( "Copy" ) {
        SECTION( "test" ) {
            lab::big::BigNum a ("1234567890");
            lab::big::BigNum b;
            b = a;
            REQUIRE(a == b);
        }
    }

    SECTION( "Subscript" ) {
        SECTION( "test" ) {
            lab::big::BigNum a ("77000000000");
            REQUIRE(a[1] == 77);
        }
        SECTION( "error" ) {
            lab::big::BigNum a ("0");
            REQUIRE_THROWS(a[1]);
            REQUIRE_THROWS(a[-1]);
        }
    }

    SECTION( "Multiply" ) {
        SECTION( "test" ) {
            lab::big::BigNum a ("7752362423526235624");
            REQUIRE(a*791 == lab::big::BigNum("6132118677009252378584"));
        }
    }

    SECTION( "Extract BigNum" ) {
        lab::big::BigNum num1("123456");

        SECTION( "easy" ) {
            lab::big::BigNum num2("123");
            REQUIRE(extract(num1, num2).first == lab::big::BigNum("1003"));
            REQUIRE(extract(num1, num2).second == lab::big::BigNum("87"));
        }
        SECTION( "normal" ) {
            lab::big::BigNum num2("322");
            REQUIRE(extract(num1, num2).first == lab::big::BigNum("383"));
            REQUIRE(extract(num1, num2).second == lab::big::BigNum("130"));
        }
        SECTION( "difficult" ) {
            lab::big::BigNum num1("1234567890");
            lab::big::BigNum num2("890890");
            REQUIRE(extract(num1, num2).first == lab::big::BigNum("1385"));
            REQUIRE(extract(num1, num2).second == lab::big::BigNum("685240"));
        }
        SECTION( "master" ) {
            lab::big::BigNum num1("123456789012341");
            lab::big::BigNum num2("89089012312345");
            REQUIRE(extract(num1, num2).first == lab::big::BigNum("1"));
            REQUIRE(extract(num1, num2).second == lab::big::BigNum("34367776699996"));
        }
        SECTION( "veteran" ) {
            lab::big::BigNum num1("31415926535897932384626433");
            lab::big::BigNum num2("832795028841971");
            REQUIRE(extract(num1, num2).first == lab::big::BigNum("37723479905"));
            REQUIRE(extract(num1, num2).second == lab::big::BigNum("393943945533678"));
        }
        SECTION( "impossible" ) {
            lab::big::BigNum num1("499510597317328160963185950244594553469083026425223082533446850352619311881"
                             "71010003137838752886587533208381420617177669147303");
            lab::big::BigNum num2("185778053217122680661300192787661119590921642");
            REQUIRE(extract(num1, num2).first == lab::big::BigNum("268874922880981921356444837383660471746363637968708614244631874788091837363196835"));
            REQUIRE(extract(num1, num2).second == lab::big::BigNum("1540141020615185186336802365801588561744233"));
        }
    }
}
