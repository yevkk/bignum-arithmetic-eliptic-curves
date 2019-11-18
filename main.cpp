#include <BigNum.hpp>
#include <EllipticCurves.hpp>
#include <BigNum.cpp>



int main()
{

    const lab::BigNum a("999999999");
    const lab::BigNum b("999999999");
    std::cout << lab::to_string(a * b);
    return 0;
}
