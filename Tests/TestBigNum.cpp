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
            const lab::BigNum a("999999999");
            const lab::BigNum b("999999999");
            a * b == lab::BigNum("999999998000000001");
            REQUIRE(a * b == lab::BigNum("999999998000000001"));
        }

        SECTION ("Rare") {
            const lab::BigNum a("99999123456789098765432112345678909876543219999");
            const lab::BigNum b("9999101010101000010130929493583285892397887897238874399999");
            REQUIRE(a * b == lab::BigNum("999901336365994481304641755778280969957261726037535427297722733918150118427240475620078108944452582380001"));
        }

        SECTION("Epic") {
            const lab::BigNum a("1010101010101010112345678987654323456789876543456010210201201021021020120120120102102099999123456789098765432112345678909876543219999");
            const lab::BigNum b("999910101010100034778239230943294903240934093904109412094091409134092340923092309423904230942309432094010130929493583285892397887897238874399999");
            REQUIRE(a * b == lab::BigNum("1010010203040505096969144002304102964934745672431934438795543769602041311552198728885697776938386026694281996784271367735387706565055641253207902666918261682251696085795287808239879856322580095000506537316821954969596318279264779071639918150118427240475620078108944452582380001"));
        }

        SECTION("Legendary") {
            const lab::BigNum a("987654321234567898765432112345678987654321234"
                                "567876543234567876543213456787654323456789876"
                                "5432123456789876543234567876543234567876543234"
                                "5678765432345678765432345678765434567876543456"
                                "6543456787654321234567876543234567898765432345"
                                "4375783945879435894375893478953478957834583457"
                                "8934534000000000000000000000000000000000000000"
                                "00000000000000000000009999399999");
            const lab::BigNum b("1010101010101011010010392309349246834602566929"
                                "4926409504509435094309543095340950934509435094"
                                "3509430594309534095094350934509439054309503945"
                                "9034509345093409543095430950934509435093409634"
                                "09090404040404030345454358435899999");


            REQUIRE(a * b == lab::BigNum("997630627509665441985572889371067901778048644358530244308913721174363445004158589383933611219647417433925332386784619962686533215866115875741459965669977010672372173488102925466110683636076261233124898531879897526038426141678529975094140338549824010608021326524081752794008361767267833378893254549677391668856765683722993722338394847760020932489071986404968917236383577392368467004191984530270256323583835345166075953138759532148315785081563714051621845580375607383110532678402523305624418708419550613504270767910269433853086003517622752525656995932281398484091564700001"));
        }
    }

    SECTION("Inverse number") {

        const lab::BigNum a("100");
        const lab::BigNum mod("21");
        REQUIRE(inverse(a, mod) == lab::BigNum("4"));
    }
}
