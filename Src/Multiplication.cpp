#include "BigNum.hpp"

namespace lab {

namespace {


    /**
     * @brief Points to the max value BigNum array's cell can hold,
     *        same as basis in linear representation
     */
    constexpr int NUM_BASE = 1000000000;

    /**
     * @brief Points to number of digits in (NUM_BASE-1)
     */
    constexpr char SECTION_DIGITS = 9;


    /*
     *  @brief Class for read-only range of elements of some std::vector.
     */

    template <typename Iter>
    class VectorView {
    public:
        explicit VectorView (Iter begin,
                             Iter end)
                : m_begin (std::move(begin)),
                  m_end(std::move(end)),
                  m_size(std::distance(m_begin, m_end))
        {}

        const Iter begin() const {
            return m_begin;
        }

        const Iter end() const {
            return m_end;
        }

        const auto size() const {
            return m_size;
        }

        const auto& operator[] (std::size_t n) const {
            return *(m_begin + n);
        }

    private:
        Iter m_begin;
        Iter m_end;
        std::size_t m_size;
    };

    template <typename Iter>
    VectorView (Iter begin, Iter end) -> VectorView <Iter>;

    using IntVectorView = VectorView <std::vector<int64_t>::iterator>;


    /**
     *  @brief Returns nearest number bigger than n that is degree of two
    */

    inline unsigned upperLog2 (unsigned n) {
        return std::pow (2, static_cast<int>(std::log2(n)) + 1);
    }

    std::vector<int64_t> naiveMultiplication (const IntVectorView& lhs,
                                              const IntVectorView& rhs) {
        std::vector <int64_t> result (lhs.size() + rhs.size());

        for (int i = 0; i < lhs.size(); ++i)
            for (int j = 0; j < rhs.size(); ++j)
                result[i + j] += lhs[i] * rhs[j];

        return result;
    }

    /**
     * @brief Minimum size of vector of digits to do
     *        fast multiplication instead of naive approach
     */

    constexpr inline int MIN_FOR_KARATSUBA = 32;

    /*
     * @brief Karatsuba's method implements fast multiplication of numbers [AB] and [CD] like
     *        like (A * 10 + B) * (C * 10 + D) = AC * 100 + BD + ((A + B) * (C + D) - AC - BD) * 10
     */


        std::vector <int64_t> karatsuba (const IntVectorView& lhs, const IntVectorView& rhs) {

        if (lhs.size() <= MIN_FOR_KARATSUBA)
            return naiveMultiplication(lhs, rhs);

        const auto length = lhs.size();
        std::vector <int64_t> result (length * 2);

        VectorView lhsL (lhs.begin() + length / 2, lhs.end());
        VectorView rhsL (rhs.begin() + length / 2, rhs.end());
        VectorView lhsR (lhs.begin(), lhs.begin() + length / 2);
        VectorView rhsR (rhs.begin(), rhs.begin() + length / 2);

        auto c1 = karatsuba(lhsL, rhsL);
        auto c2 = karatsuba(lhsR, rhsR);

        std::vector <int64_t> lhsLR (length / 2);
        std::vector <int64_t> rhsLR (length / 2);

        for (auto i = 0; i < length / 2; ++i) {
            lhsLR[i] = lhsL[i] + lhsR[i];
            rhsLR[i] = rhsL[i] + rhsR[i];
        }

        auto c3 = karatsuba(IntVectorView(lhsLR.begin(), lhsLR.end()),
                            IntVectorView(rhsLR.begin(), rhsLR.end()));

        for (auto i = 0; i < length; ++i)
            c3[i] -= c2[i] + c1[i];

        for (auto i = 0; i < length; ++i)
            result[i] = c2[i];

        for (auto i = length; i < length * 2; ++i)
            result[i] = c1[i - length];

        for (auto i = length / 2; i < length + length / 2; ++i) {
            result[i] += c3[i - length / 2];
        }

        return result;
    }

    /*
     * @brief Normalizing number ceils to NUM_BASE
     */

    inline void finalize (std::vector <int64_t>& res) {
        for (auto i = 0; i < res.size(); ++i) {
            if (i != res.size() - 1)
                res[i + 1] += res[i] / NUM_BASE;
            res[i] %= NUM_BASE;
        }
    }
}


    BigNum operator* (const BigNum& lhs, const BigNum& rhs) {

        std::vector<int64_t> lhsTemp(lhs._digits.begin(), lhs._digits.end());
        std::vector<int64_t> rhsTemp(rhs._digits.begin(), rhs._digits.end());
        auto maxSize = std::max(lhsTemp.size(), rhsTemp.size());

        lhsTemp.resize(upperLog2(maxSize));
        rhsTemp.resize(upperLog2(maxSize));

        auto nums = karatsuba(IntVectorView(lhsTemp.begin(), lhsTemp.end()),
                              IntVectorView(rhsTemp.begin(), rhsTemp.end()));
        finalize(nums);

        while (nums.back() == 0)
            nums.pop_back();

        BigNum result;
        result._digits = std::vector<int>(nums.begin(), nums.end());
        return result;
    }
}