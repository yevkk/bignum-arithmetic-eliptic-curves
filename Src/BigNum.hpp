#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

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
     * @brief Division of two numbers
     * @return Pair of numbers, the first is an integer, the second is a remainder of division
     */
    friend std::pair<BigNum, BigNum> extract(const BigNum& first, const BigNum& second);

     /**
      * @brief Converts number to vector of its digits
      * @return Vector of digits
      */
    friend std::vector<char> toOneDigit(const BigNum& num);

    /**
     * @brief Converts vector of digits to number
     */
    friend BigNum toBigNum(std::vector<char>& num_digits);

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
