// -*- lsst-c++ -*-
/**
* @file BigNum.cpp
*
*
*/

#include <BigNum.hpp>

namespace lab {
    namespace big {

        BigNum::BigNum(const BigNum &r) {
            _digits = r._digits;
        }

        BigNum::BigNum() {
        }

        BigNum::BigNum(std::string num_str) {
            _digits.clear();
            for (int i = num_str.size() - 1; i >= 0; i -= SECTION_DIGITS) {
                std::string curr_section;
                if (i - SECTION_DIGITS + 1 < 0) {
                    curr_section = num_str.substr(0, SECTION_DIGITS + (i - SECTION_DIGITS + 1));
                } else {
                    curr_section = num_str.substr(i - SECTION_DIGITS + 1, SECTION_DIGITS);
                }
                long long counter = 0;
                for (int j = 0; j < curr_section.size(); j++) {
                    counter = counter * 10 + (curr_section[j] - '0');
                }
                _digits.push_back(counter);
            }
            while (!_digits.empty() && _digits.back() == 0) {
                _digits.pop_back();
            }
        }

        BigNum& BigNum::operator=(const BigNum &r) {
            if (this == &r) {
                return *this;
            }
            _digits = r._digits;
            return *this;
        }

        int& BigNum::operator[](int index)
        {
            if (!((index >= 0)&&(index < _digits.size()))) {
                throw "no such index";
            }
            return _digits[index];
        }

        std::string BigNum::str()
        {
            std::string result = "";
            int leading_zeros = 0;
            for (int curr_pos = 0; curr_pos <_digits.size() ; curr_pos++) {
                std::string temp = "";
                int counter = _digits[curr_pos];
                int i = 0;
                while (i < SECTION_DIGITS) {
                    if ((counter % 10) == 0) {
                        leading_zeros++;
                    }else leading_zeros = 0;
                    temp = static_cast<char>((counter % 10) + '0') + temp;
                    counter = counter / 10;
                    i++;
                }
                result = temp + result;
            }
            result.erase(0, leading_zeros);
            return result;
        }

        bool operator<(const BigNum& l, const BigNum& r) {
            if (l._digits.size() < r._digits.size()) return true;
            if (l._digits.size() > r._digits.size()) return false;
            for (int curr_pos = l._digits.size() - 1; curr_pos >= 0; curr_pos--) {
                if (l._digits[curr_pos] < r._digits[curr_pos]) return true;
                if (l._digits[curr_pos] > r._digits[curr_pos]) return false;
            }
            return false;
        }

        bool operator>(const BigNum &l, const BigNum &r) {
            return (r < l);
        }

        bool operator<=(const BigNum &l, const BigNum &r) {
            return !(r < l);
        }

        bool operator>=(const BigNum &l, const BigNum &r) {
            return !(l < r);
        }

        bool operator==(const BigNum &l, const BigNum &r) {
            return ((!(r < l)) && (!(l < r)));
        }

        bool operator!=(const BigNum &l, const BigNum &r) {
            return !(l == r);
        }

        std::ostream &operator<<(std::ostream &os, const BigNum &num) {
            for (int last_index = num._digits.size() - 1; last_index >= 0; last_index--) {
                int counter = num._digits[last_index];
                os << counter;
            }
            return os;
        }

        std::istream &operator>>(std::istream &is, BigNum &num) {
            std::string num_str;
            is >> num_str;
            num = BigNum(num_str);
            return is;
        }

        BigNum operator+(const BigNum &num1, const BigNum &num2) {
            BigNum result;
            if (num2._digits.size() > num1._digits.size()) {
                result = num2;
                int addition = 0;
                for (int curr_pos = 0; curr_pos < num1._digits.size(); curr_pos++) {
                    result._digits[curr_pos] += num1._digits[curr_pos] + addition;
                    addition = result._digits[curr_pos] / NUM_BASE;
                    result._digits[curr_pos] = result._digits[curr_pos] % NUM_BASE;
                }
            } else {
                result = num1;
                int addition = 0;
                for (int curr_pos = 0; curr_pos < num2._digits.size(); curr_pos++) {
                    long long temp = result._digits[curr_pos] + num2._digits[curr_pos] + addition;
                    result._digits[curr_pos] = temp % NUM_BASE;
                    addition = temp / NUM_BASE;
                    result._digits[curr_pos] = result._digits[curr_pos] % NUM_BASE;
                }
            }
            return result;
        }

        BigNum operator-(const BigNum &num1, const BigNum &num2) {
            BigNum result = num1;
            for (int curr_pos = 0; curr_pos < num2._digits.size(); curr_pos++) {
                if (result._digits[curr_pos] < num2._digits[curr_pos]) {
                    result._digits[curr_pos] = result._digits[curr_pos] - num2._digits[curr_pos] + NUM_BASE;
                    result._digits[curr_pos + 1] -= 1;
                } else {
                    result._digits[curr_pos] = result._digits[curr_pos] - num2._digits[curr_pos];
                }
            }
            if (num1._digits.size() > num2._digits.size()) {
                if (result._digits[num2._digits.size()] < 0) {
                    result._digits[num2._digits.size()] += NUM_BASE;
                    result._digits[num2._digits.size() + 1] -= 1;
                }
            }
            return result;
        }

        std::vector<char> to_one_digit(const BigNum &num1) {
            std::vector<char> fnum;
            for (int curr_pos = 0; curr_pos < num1._digits.size(); curr_pos++) {
                int counter = num1._digits[curr_pos];
                for (int i = 0; i < SECTION_DIGITS; i++) {
                    fnum.push_back(counter % 10);
                    counter = counter / 10;
                }
            }
            while (!fnum.empty() && fnum.back() == 0) {
                fnum.pop_back();
            }
            return fnum;
        }

        BigNum to_big_num(std::vector<char> &num1) {
            std::string str_num = "";
            for (int i = num1.size() - 1; i >= 0; i--) {
                str_num += ('0' + num1[i]);
            }
            BigNum result(str_num);
            return result;
        }

        BigNum operator*(const BigNum &num1, int num2) {
            BigNum result = num1;
            unsigned long long addition = 0;
            for (int curr_pos = 0; curr_pos < result._digits.size(); curr_pos++) {
                unsigned long long temp = static_cast<long long>(result._digits[curr_pos]) * num2 + addition;
                result._digits[curr_pos] = temp % NUM_BASE;
                addition = temp / NUM_BASE;
            }
            if (addition != 0) {
                result._digits.push_back(addition);
            }
            return result;
        }

        bool is_lower_digits(std::vector<char> &num1, std::vector<char> &num2, int step) {
            if ((step > num2.size()) && (step <= num1.size())) return false;
            if ((step < num2.size()) || (num1.size() < num2.size())) return true;
            if (step > num1.size()) return true;
            for (int i = num2.size() - 1; i >= 0; i--) {
                if (num1[num1.size() + i - step] < num2[i]) return true;
                if (num1[num1.size() + i - step] > num2[i]) return false;
            }
            return false;
        }

        bool is_bigger_digits(std::vector<char> &num1, std::vector<char> &num2, int step) {
            return !(is_lower_digits(num1, num2, step));
        }

        std::vector<char> multiply_digits(std::vector<char> &num1, int num2) {
            std::vector<char> result = num1;
            int addition = 0;
            for (int curr_pos = 0; curr_pos < result.size(); curr_pos++) {
                long long temp = result[curr_pos] * num2 + addition;
                result[curr_pos] = temp % 10;
                addition = temp / 10;
            }
            if (addition != 0) {
                result.push_back(addition);
            }
            return result;
        }

        void left_substract(std::vector<char> &num1, std::vector<char> &num2, int side) {
            for (int i = 0; i < num2.size(); i++) {
                if (num1[num1.size() - side + i] < num2[i]) {
                    num1[num1.size() - side + i] = 10 + num1[num1.size() - side + i] - num2[i];
                    num1[num1.size() - side + i + 1] -= 1;
                } else {
                    num1[num1.size() - side + i] = num1[num1.size() - side + i] - num2[i];
                }
            }
        }

        std::pair<BigNum, BigNum> extract(const BigNum &num1, const BigNum &num2) {
            if (num1 < num2)
                return std::pair<BigNum, BigNum>(BigNum("0"), num1);
            std::vector<char> fnum = to_one_digit(num1);
            std::vector<char> snum = to_one_digit(num2);
            std::vector<char> result;
            std::vector<char> current = snum;
            std::vector<char> temp;
            int side = 1;
            int power = 1;

            side = current.size();
            while ((is_lower_digits(fnum, current, side))) {
                side++;
            }
            while (true) {
                if ((power == 1) && (is_lower_digits(fnum, current, side))) {
                    side++;
                    if (side > fnum.size()) {
                        break;
                    }
                    result.push_back(0);
                }
                if (is_bigger_digits(fnum, current, side)) {
                    power++;
                    current = multiply_digits(snum, power);
                }
                if ((power != 1) && (is_lower_digits(fnum, current, side))) {
                    current = multiply_digits(snum, power - 1);
                    left_substract(fnum, current, side);
                    int prev_size = temp.size();
                    temp.clear();
                    while (!fnum.empty() && fnum.back() == 0) {
                        fnum.pop_back();
                        side--;
                    }
                    result.push_back(power - 1);
                    power = 1;
                    current = snum;
                    side++;
                }
            }
            std::reverse(result.begin(), result.end());
            return std::pair<BigNum, BigNum>(to_big_num(result), to_big_num(fnum));
        }

        void modify(BigNum &num, const BigNum &mod) {
            num = extract(num, mod).second;
        }

        BigNum add(const BigNum &num1, const BigNum &num2, const BigNum &mod) {
            auto t_num2 = num2 % mod;
            auto t_num1 = num1 % mod;
            BigNum result = t_num1 + t_num2;
            modify(result, mod);
            return result;
        }

        BigNum subtract(const BigNum &num1, const BigNum &num2, const BigNum &mod) {
            auto t_num2 = num2 % mod;
            auto t_num1 = num1 % mod;
            BigNum result;
            if (t_num1 >= t_num2) {
                result = t_num1 - t_num2;
            } else {
                result = mod - t_num2 + t_num1;
            }
            return result;
        }

        BigNum operator%(const BigNum &num1, const BigNum &num2) {
            BigNum result = extract(num1, num2).second;
            return result;
        }

        ///TODO
        BigNum operator*(const BigNum &num1, const BigNum &num2) {
            return BigNum("0");
        }
    }
}