#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cassert>

namespace lab {

/**
 * @brief BigNum class can hold big POSITIVE integers
 */
class BigNum
{
public:
    BigNum(const BigNum& that) = default;

    BigNum(std::string_view num_str);

    BigNum() = default;

    BigNum& operator=(const BigNum& that) = default;

    friend std::string to_string(const BigNum& num);

    friend bool operator<(const BigNum& left, const BigNum& right);
    friend bool operator<=(const BigNum& left, const BigNum& right);
    friend bool operator>(const BigNum& left, const BigNum& right);
    friend bool operator>=(const BigNum& left, const BigNum& right);
    friend bool operator==(const BigNum& left, const BigNum& right);
    friend bool operator!=(const BigNum& left, const BigNum& right);

    /**
     * @brief operator- for subtracting two BigNums
     * @note left number must be bigger than right number
     */
    friend BigNum operator-(const BigNum& left, const BigNum& right);
    friend BigNum operator+(const BigNum& left, const BigNum& right);

    friend BigNum operator*(const BigNum& left, int right);

    /// TODO
    friend BigNum operator*(const BigNum& left, const BigNum& right);

    friend BigNum operator%(const BigNum& left, const BigNum& right);

    template<typename OStream>
    friend OStream& operator<<(OStream& os, const BigNum& num);
    template<typename IStream>
    friend IStream& operator>>(IStream& is, BigNum& num);

    /**
     * @brief modify function converts num to a corresponding number in group modulo mod
     * @param num
     * @param mod
     */
    friend void modify(BigNum& num, const BigNum& mod);

    /**
     * @brief add function performs modulo addition of two BigNums
     * @param first
     * @param second
     * @param mod
     * @return summation result
     */
    friend BigNum add(const BigNum& first, const BigNum& second, const BigNum& mod);

    /**
     * @brief subtract function performs modulo subtraction
     * @param first
     * @param second
     * @param mod
     * @return summation result
     */
    friend BigNum subtract(const BigNum& first, const BigNum& second, const BigNum& mod);

    /**
     * @brief extract function performs BigNum division
     * @note complexity is O(n^2)
     * @param first
     * @param second
     * @return pair of BigNum, where the first number is an integer
     * and the second is a remainder of division
     */
    friend std::pair<BigNum, BigNum> extract(const BigNum& first, const BigNum& second);

     /**
      * @brief toOneDigit function returns a vector of BigNum 's digits
      * @param num
      * @return digits
      */
    friend std::vector<char> toOneDigit(const BigNum& num);

    /**
      * @brief toBigNum function returns a BigNum converted from vector of it's digits (reverse to toOneDigit function)
      * @param in_digits
      * @return BigNum
      */
    friend BigNum toBigNum(std::vector<char>& num_digits);

private:
    //// Array of coefficients in representation
    std::vector<int> _digits;
};

template<typename OStream>
OStream& operator<<(OStream& os, const BigNum& num)
{
    for (int last_index = num._digits.size() - 1; last_index >= 0; last_index--) {
        int counter = num._digits[last_index];
        os << counter;
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
