// -*- lsst-c++ -*-
/**
* @file BigNum.hpp
*
*
*/

#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cassert>

namespace lab {
    namespace big {

        /** NUM_BASE points to the max value BigNum array's cell can hold
         *  (basis in linear representation)
         *
         * SECTION_DIGITS points to the max value of T, where 10**T <= NUM_BASE
         *
         */
        const char SECTION_DIGITS = 9;
        const int NUM_BASE = 1000000000;

        /** @class
         * BigNum class can hold big POSITIVE integers
         *
         */
        class BigNum
        {
        private:
            //// Array of coefficients in representation
            std::vector<int> _digits;
        public:
            /// Copy constructor
            BigNum(const BigNum& r);

            /// String constructor
            BigNum(std::string num);

            /// Default constructor ?
            BigNum();

            /// Copy operator
            BigNum& operator=(const BigNum& r);

            /// Subscript operator
            int& operator[](int index);

            /// Returns number in string format
            std::string str();

            /// Comparison operators
            friend bool operator<(const BigNum& l, const BigNum& r);
            friend bool operator<=(const BigNum& l, const BigNum& r);
            friend bool operator>(const BigNum& l, const BigNum& r);
            friend bool operator>=(const BigNum& l, const BigNum& r);
            friend bool operator==(const BigNum& l, const BigNum& r);
            friend bool operator!=(const BigNum& l, const BigNum& r);

            /**
             * !DO NOT USE THESE OPERATORS!
             * use add() and subscript() instead
             */
            friend BigNum operator-(const BigNum& num1, const BigNum& num2);
            friend BigNum operator+(const BigNum& num1, const BigNum& num2);

            /// Multiply operators
            friend BigNum operator*(const BigNum& num1, int num2);
            /// TODO
            friend BigNum operator*(const BigNum& num1, const BigNum& num2);

            /// Modulo operator
            friend BigNum operator%(const BigNum& num1, const BigNum& num2);

            /// Ostream/istream operators
            friend std::ostream& operator<<(std::ostream& os, const BigNum& num);
            friend std::istream& operator>>(std::istream& os, BigNum& num);

            /// Modify changes num to result of (@param num % @param mod)
            friend void modify(BigNum& num, const BigNum& mod);

            /**
             * add function performs modulo addition
             * @param num1 first BigNum
             * @param num2 second BigNum
             * @param mod modulo value
             * @return summation result
             */
            friend BigNum add(const BigNum& num1, const BigNum& num2, const BigNum& mod);

            /**
             * subtract function performs modulo subtraction
             * @param num1 first BigNum
             * @param num2 second BigNum
             * @param mod modulo value
             * @return summation result
             */
            friend BigNum subtract(const BigNum& num1, const BigNum& num2, const BigNum& mod);

            /**
             * extract function performs BigNum division
             * @param num1 first BigNum
             * @param num2 second BigNum
             * @return pair of BigNum, where the first number is an integer
             * and the second is a remainder of division
             */
            friend std::pair<BigNum, BigNum> extract(const BigNum& num1, const BigNum& num2);

            /// Helper functions
             /**
              * to_one_digit returns a vector of BigNum 's digits
              * @param num1 BigNum
              * @return vector of it's digits
              */
            friend std::vector<char> to_one_digit(const BigNum& num1);
            /**
              * to_big_num returns a BigNum converted from vector of it's digits (reverse to to_one_digit function)
              * @param num1 vector of digits
              * @return BigNum
              */
            friend BigNum to_big_num(std::vector<char>& num1);
        };
    } // namespace big
} // namespace lab
