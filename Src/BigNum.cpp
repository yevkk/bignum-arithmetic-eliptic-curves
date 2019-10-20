#include <BigNum.hpp>

namespace lab {

/**
 * @brief NUM_BASE points to the max value BigNum array's cell can hold,
 * same as basis in linear representation
 */
constexpr int NUM_BASE = 1000000000;

/**
 * @brief SECTION_DIGITS points to number of digits in (NUM_BASE-1)
 */
constexpr char SECTION_DIGITS = 9;

BigNum::BigNum(std::string_view num_str) {
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

std::string to_string(const BigNum &num)
{
    std::string result = "";
    int leading_zeros = 0;
    for (int curr_pos = 0; curr_pos <num._digits.size() ; curr_pos++) {
        std::string temp = "";
        int counter = num._digits[curr_pos];
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

bool operator<(const BigNum &left, const BigNum &right) {
    if (left._digits.size() < right._digits.size()) return true;
    if (left._digits.size() > right._digits.size()) return false;
    for (int curr_pos = left._digits.size() - 1; curr_pos >= 0; curr_pos--) {
        if (left._digits[curr_pos] < right._digits[curr_pos]) return true;
        if (left._digits[curr_pos] > right._digits[curr_pos]) return false;
    }
    return false;
}

bool operator>(const BigNum &left, const BigNum &right) {
    return (right < left);
}

bool operator<=(const BigNum &left, const BigNum &right) {
    return !(right < left);
}

bool operator>=(const BigNum &left, const BigNum &right) {
    return !(left < right);
}

bool operator==(const BigNum &left, const BigNum &right) {
    return ((!(right < left)) && (!(left < right)));
}

bool operator!=(const BigNum &left, const BigNum &right) {
    return !(left == right);
}

BigNum operator+(const BigNum &left, const BigNum &right) {
    BigNum result;
    if (right._digits.size() > left._digits.size()) {
        result = right;
        int addition = 0;
        for (int curr_pos = 0; curr_pos < left._digits.size(); curr_pos++) {
            result._digits[curr_pos] += left._digits[curr_pos] + addition;
            addition = result._digits[curr_pos] / NUM_BASE;
            result._digits[curr_pos] = result._digits[curr_pos] % NUM_BASE;
        }
    } else {
        result = left;
        int addition = 0;
        for (int curr_pos = 0; curr_pos < right._digits.size(); curr_pos++) {
            long long temp = static_cast<long long>(result._digits[curr_pos])
                    + static_cast<long long>(right._digits[curr_pos]) + addition;
            result._digits[curr_pos] = temp % NUM_BASE;
            addition = temp / NUM_BASE;
            result._digits[curr_pos] = result._digits[curr_pos] % NUM_BASE;
        }
    }
    return result;
}

BigNum operator-(const BigNum &left, const BigNum &right) {
    BigNum result = left;
    for (int curr_pos = 0; curr_pos < right._digits.size(); curr_pos++) {
        if (result._digits[curr_pos] < right._digits[curr_pos]) {
            result._digits[curr_pos] = result._digits[curr_pos] - right._digits[curr_pos] + NUM_BASE;
            result._digits[curr_pos + 1] -= 1;
        } else {
            result._digits[curr_pos] = result._digits[curr_pos] - right._digits[curr_pos];
        }
    }
    if (left._digits.size() > right._digits.size()) {
        if (result._digits[right._digits.size()] < 0) {
            result._digits[right._digits.size()] += NUM_BASE;
            result._digits[right._digits.size() + 1] -= 1;
        }
    }
    return result;
}

std::vector<char> toOneDigit(const BigNum &num) {
    std::vector<char> fnum;
    for (int curr_pos = 0; curr_pos < num._digits.size(); curr_pos++) {
        int counter = num._digits[curr_pos];
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

BigNum toBigNum(std::vector<char> &num_digits) {
    std::string str_num = "";
    for (int i = num_digits.size() - 1; i >= 0; i--) {
        str_num += ('0' + num_digits[i]);
    }
    BigNum result(str_num);
    return result;
}

BigNum operator*(const BigNum &left, int right) {
    BigNum result = left;
    unsigned long long addition = 0;
    for (int curr_pos = 0; curr_pos < result._digits.size(); curr_pos++) {
        unsigned long long temp = static_cast<long long>(result._digits[curr_pos]) * right + addition;
        result._digits[curr_pos] = temp % NUM_BASE;
        addition = temp / NUM_BASE;
    }
    if (addition != 0) {
        result._digits.push_back(addition);
    }
    return result;
}

/**
 * @brief isLowerDigits applies operator< for vectors of digits
 * @param left
 * @param right
 * @param step points to number of digits from beginning of left var to compare
 * @return result
 */
bool isLowerDigits(std::vector<char> &left, std::vector<char> &right, int step) {
    if ((step > right.size()) && (step <= left.size())) return false;
    if ((step < right.size()) || (left.size() < right.size())) return true;
    if (step > left.size()) return true;
    for (int i = right.size() - 1; i >= 0; i--) {
        if (left[left.size() + i - step] < right[i]) return true;
        if (left[left.size() + i - step] > right[i]) return false;
    }
    return false;
}

/**
 * @brief isBiggerDigits applies operator>= for vectors of digits
 * @param left
 * @param right
 * @param step points to number of digits from beginning of left var to compare
 * @return result
 */
bool isBiggerDigits(std::vector<char> &num1, std::vector<char> &num2, int step) {
    return !(isLowerDigits(num1, num2, step));
}

/**
 * @brief multiplyDigits applies multiplication for vector of digits and int
 * @param left
 * @param right
 * @return result
 */
std::vector<char> multiplyDigits(std::vector<char> &num1, int num2) {
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

/**
 * @brief isBiggerDigits applies subtraction for vectors of digits
 * where the second number will be multiplied until has max basis rank
 * @param left
 * @param right
 * @param side points to number of digits from beginning of left var to delete
 * @return result
 */
void leftSubstract(std::vector<char> &num1, std::vector<char> &num2, int side) {
    for (int i = 0; i < num2.size(); i++) {
        if (num1[num1.size() - side + i] < num2[i]) {
            num1[num1.size() - side + i] = 10 + num1[num1.size() - side + i] - num2[i];
            num1[num1.size() - side + i + 1] -= 1;
        } else {
            num1[num1.size() - side + i] = num1[num1.size() - side + i] - num2[i];
        }
    }
}

std::pair<BigNum, BigNum> extract(const BigNum &left, const BigNum &right) {
    if (left < right)
        return std::pair<BigNum, BigNum>(BigNum("0"), left);
    std::vector<char> fnum = toOneDigit(left);
    std::vector<char> snum = toOneDigit(right);
    std::vector<char> result;
    std::vector<char> current = snum;
    std::vector<char> temp;
    int side = 1;
    int power = 1;

    side = current.size();
    while ((isLowerDigits(fnum, current, side))) {
        side++;
    }
    while (true) {
        if ((power == 1) && (isLowerDigits(fnum, current, side))) {
            side++;
            if (side > fnum.size()) {
                break;
            }
            result.push_back(0);
        }
        if (isBiggerDigits(fnum, current, side)) {
            power++;
            current = multiplyDigits(snum, power);
        }
        if ((power != 1) && (isLowerDigits(fnum, current, side))) {
            current = multiplyDigits(snum, power - 1);
            leftSubstract(fnum, current, side);
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
    return std::pair<BigNum, BigNum>(toBigNum(result), toBigNum(fnum));
}

void modify(BigNum &num, const BigNum &mod) {
    num = extract(num, mod).second;
}

BigNum add(const BigNum &left, const BigNum &right, const BigNum &mod) {
    auto t_num2 = right % mod;
    auto t_num1 = left % mod;
    BigNum result = t_num1 + t_num2;
    modify(result, mod);
    return result;
}

BigNum subtract(const BigNum &left, const BigNum &right, const BigNum &mod) {
    auto t_num2 = right % mod;
    auto t_num1 = left % mod;
    BigNum result;
    if (t_num1 >= t_num2) {
        result = t_num1 - t_num2;
    } else {
        result = mod - t_num2 + t_num1;
    }
    return result;
}

BigNum operator%(const BigNum &left, const BigNum &right) {
    BigNum result = extract(left, right).second;
    return result;
}

///TODO
BigNum operator*(const BigNum &left, const BigNum &right) {
    return BigNum("0");
}
}