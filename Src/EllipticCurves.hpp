#pragma once

#include "BigNum.hpp"
#include <vector>


namespace lab {

struct Point {
    BigNum x;
    BigNum y;

    Point(const BigNum& X, const BigNum& Y) :x(X), y(Y) {}
    friend bool operator==(const Point& left, const Point& right) {
        return (left.x == right.x) && (left.y == right.y);
    }
};

struct Field {
    BigNum modulo;
    Field(const BigNum& g) :modulo(g) {}

    friend bool operator==(const Field& left, const Field& right) {
        return left.modulo == right.modulo;
    }
};

class EllipticCurve {
public:
    EllipticCurve(const EllipticCurve& that) = default;

    EllipticCurve(Field* f, const BigNum& a, const BigNum& b);

    EllipticCurve() = default;

    EllipticCurve& operator=(const EllipticCurve& that) = default;

    static inline const Point neutral = { BigNum::inf(), BigNum::inf() };

    friend bool operator==(const EllipticCurve& left, const EllipticCurve& right);
    friend bool operator!=(const EllipticCurve& left, const EllipticCurve& right);

    template<typename OStream>
    friend OStream& operator<<(OStream& os, const EllipticCurve& curve);

    /**
    * @return True if elliptic curve contains given point, otherwise false
    */
    bool contains(const Point& p) const;

    /**
    * @param Point p must belong to curve
    */
    Point invertedPoint(const Point& p) const;

    //TODO: fix namespace issue
    /**
    * @param Both points should belong to curve
    */
    Point addPoints(const Point& first, const Point& second) const;

    Point powerPoint(const Point& p, const BigNum& a) const;

    BigNum getFieldModulo() const;

    ///< y^2 = x^3 + a*x + b on field f
    BigNum pointOrder(const Point& p) const;

private:

    /**
     * @brief Takes BigNum n, Point P such that nP == infinity and finds minimal order for Point
     * */
    BigNum reduce(BigNum& num, const Point& p) const;

    /// y^2 = x^3 + a*x + b on field f
    Field* _f;
    BigNum _a;
    BigNum _b;
};

template<typename OStream>
OStream& operator<<(OStream& os, const EllipticCurve& curve) {
    os << "y^2 = x^3 + " << curve._a << "*x + " << curve._b << " mod " << curve._f->modulo;
    return os;
}

} // namespace lab
