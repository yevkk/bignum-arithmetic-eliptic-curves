#pragma once

#include <string_view>
#include <algorithm>
#include <optional>
#include <iostream>
#include <utility>
#include <vector>
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

    explicit BigNum(std::string_view num_str);

    BigNum() = default;

    BigNum& operator=(const BigNum& that) = default;

    friend std::string to_string(const BigNum& num);

    static const BigNum& inf();

    friend bool operator<(const BigNum& left, const BigNum& right) noexcept;
    friend bool operator<=(const BigNum& left, const BigNum& right) noexcept;
    friend bool operator>(const BigNum& left, const BigNum& right) noexcept;
    friend bool operator>=(const BigNum& left, const BigNum& right) noexcept;
    friend bool operator==(const BigNum& left, const BigNum& right) noexcept;
    friend bool operator!=(const BigNum& left, const BigNum& right) noexcept;

    /**
     * @note left number must be bigger than right number
     */
    friend BigNum operator-(const BigNum& left, const BigNum& right);
    friend BigNum operator+(const BigNum& left, const BigNum& right);
    friend BigNum operator/(const BigNum& left, int right);
    friend BigNum operator*(const BigNum& left, int right);
    friend BigNum operator*(const BigNum& left, const BigNum& right);
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
     * @brief Multiplication of two numbers by Karatsuba or Montgomery algorithm
     */
    friend BigNum multiply(const BigNum& lhs, const BigNum& rhs, const BigNum& mod);

    /**
     * @brief Division of two numbers
     * @return Pair of numbers, the first is an integer, the second is a remainder of division
     */
    friend std::pair<BigNum, BigNum> extract(const BigNum& first, const BigNum& second);

    /**
     * @brief Euclid method requires number and module to be coprime,
     *        Fermat method - to be mod prime
     */
    enum class InversionPolicy {
        Euclid,
        Fermat
    };

    /**
     * @brief Return inverted number to num in group modulo mod
     */
    friend BigNum inverted(const BigNum& num, const BigNum& mod, InversionPolicy policy);

    /**
     * @brief Finds square root of @a num modulo @a mod using Tonelli–Shanks algorithm
     */
    friend std::optional<std::pair<BigNum, BigNum>> sqrt(const BigNum& num, const BigNum& mod);

    /**
     * @brief Converts number to vector of its digits
     * @return Vector of digits
     */
    // FIXME(aoyako): remove this garbage
    friend std::vector<char> toOneDigit(const BigNum& num);

    /**
     * @brief Converts vector of digits to number
     */
    // FIXME(aoyako): remove this garbage
    friend BigNum toBigNum(std::vector<char>& num_digits);

private:
    /// Array of coefficients in representation
    std::vector<int64_t> _digits;
};

template<typename OStream>
OStream& operator<<(OStream& os, const BigNum& num) {
    for (auto it = num._digits.rbegin(); it != num._digits.rend(); ++it) {
        std::string s(std::to_string(*it));
        while (s.size() != 9 && it != num._digits.rbegin()) {
            s.insert(0, "0");
        }
        os << s;
    }
    return os;
}

template<typename IStream>
IStream& operator>>(IStream& is, BigNum& num) {
    std::string num_str;
    is >> num_str;
    num = BigNum(num_str);
    return is;
}


inline lab::BigNum operator""_bn(const char* str) {
    return lab::BigNum(str);
}

} // namespace lab
