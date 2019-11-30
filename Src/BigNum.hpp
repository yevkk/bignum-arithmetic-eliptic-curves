#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>

namespace lab {

/**
 * @brief Class for holding big positive integers
 */
class BigNum
{
public:
    BigNum(const BigNum& that) = default;

    BigNum(std::string_view num_str);

    BigNum() = default;

    BigNum& operator=(const BigNum& that) = default;

    friend std::string to_string(const BigNum& num);
    friend BigNum from_string(std::string_view str);

    friend bool operator<(const BigNum& left, const BigNum& right);
    friend bool operator<=(const BigNum& left, const BigNum& right);
    friend bool operator>(const BigNum& left, const BigNum& right);
    friend bool operator>=(const BigNum& left, const BigNum& right);
    friend bool operator==(const BigNum& left, const BigNum& right);
    friend bool operator!=(const BigNum& left, const BigNum& right);

    /**
     * @note left number must be bigger than right number
     */
    friend BigNum operator-(const BigNum& left, const BigNum& right);

    friend BigNum operator+(const BigNum& left, const BigNum& right);

    friend BigNum operator*(const BigNum& left, int right);

    friend BigNum operator* (const BigNum &left, const BigNum &right);

    friend BigNum operator%(const BigNum& left, const BigNum& right);

    template<typename OStream>
    friend OStream& operator<<(OStream& os, const BigNum& num);
    template<typename IStream>
    friend IStream& operator>>(IStream& is, BigNum& num);

    /**
     * @brief Converts number to a corresponding in group modulo mod
     */
    friend void modify(BigNum& num, const BigNum& mod);

    /**
     * @brief Modulo addition
     */
    friend BigNum add(const BigNum& first, const BigNum& second, const BigNum& mod);

    /**
     * @brief Modulo subtraction
     */
    friend BigNum subtract(const BigNum& first, const BigNum& second, const BigNum& mod);


    /**
     *  @brief Multiplication of two numbers by Karatsuba or Montgomery algorithm
     */
    friend BigNum multiply (const BigNum& lhs, const BigNum& rhs, const BigNum& mod);

    /**
    * @brief Division of two numbers
    * @return Pair of numbers, the first is an integer, the second is a remainder of division
    */
    friend std::pair<BigNum, BigNum> extract(const BigNum& first, const BigNum& second);

    /**
     *  @brief Euclid method requires number and module to be coprime,
     *         Fermat method - to be mod prime
     */
    enum class InversionPolicy {
        Euclid,
        Fermat
    };

    /**
     *  @return Inverted number to num in group modulo mod
     */
    friend BigNum inverted(const BigNum &num, const BigNum& mod, InversionPolicy policy);


     /**
      * @brief Converts number to vector of its digits
      * @return Vector of digits
      */
    friend std::vector<char> toOneDigit(const BigNum& num);

    /**
     * @brief Converts vector of digits to number
     */
    friend BigNum toBigNum(std::vector<char>& num_digits);

    /**
     * @brief calculate montgomery coef as 10^(mod.length+1) if mod is prime and mod + 1 if not
     * @param montgomery_coefficient is bigger than mod and coprime with mod
     */
    friend BigNum calculateMontgomeryCoefficient(const BigNum &mod);

    /**
     * @brief Convert BigNum to Montgomery form % mod
     * @param montgomery_coefficient is bigger than mod and coprime with mod
     * @return multiplication of num and montgomery_coefficient % mod (BigNum in Montogmery form)
     */
    friend BigNum convertToMontgomeryForm(const BigNum &num, const BigNum &mod, const BigNum &montgomery_coefficient);

    /**
     * @brief Multiply BigNums in Montogomery form in the range [0, mod)
     * @param coefficient = (montgomery_coefficient(montgomery_coefficient^(−1) % mod)−1) / mod .
     *        it is always the same, so pass it not to calculate it on each call of pow
     */
    friend BigNum multiplyMontgomery(const BigNum &left, const BigNum &right, const BigNum &mod, const BigNum &montgomery_coefficient, const BigNum &coefficient);

    /**
     * @brief raises BigNum to the BigNum power using modular exponentiation and Montgomery form
     * @param montgomery_coefficient = coprime and > mod
     * @param mod should be prime, but not obliged to
     */
    friend BigNum powMontgomery(const BigNum &left, BigNum right, const BigNum &mod);

    /**
     * @brief length of BigNum
     */
    friend int length(const BigNum &num);

private:
    ///< Array of coefficients in representation
    std::vector<int> _digits;
};

template<typename OStream>
OStream& operator<<(OStream& os, const BigNum& num)
{
    for (auto it = num._digits.rbegin(); it != num._digits.rend(); ++it) {
        std::string s(std::to_string(*it));
        while (s.size() != 9 && it != num._digits.rbegin())
            s.insert(0, "0");
        os << s;
    }
    return os;
}

template<typename IStream>
IStream& operator>>(IStream& is, BigNum& num)
{
    std::string num_str;
    is >> num_str;
    num = BigNum(num_str);
    return is;
}
} // namespace lab

lab::BigNum operator"" _bn(const char* str);
