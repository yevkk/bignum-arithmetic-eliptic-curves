#include <EllipticCurves.hpp>

namespace lab {

EllipticCurve::EllipticCurve(Field* f, const BigNum& a, const BigNum& b): _f(f),_a(a),_b(b){}

bool operator==(const EllipticCurve& left, const EllipticCurve& right) {
    return (*left._f == *right._f) && (left._a == right._a) && (left._b == right._b);
}

bool operator!=(const EllipticCurve& left, const EllipticCurve& right) {
    return !(left == right);
}

bool EllipticCurve::contains(const Point& p) const {
    if (p == neutral)
        return true;

    /// y^2 == x^3 + A*x + B
    if ((p.y * p.y) % _f->modulo == ((p.x * p.x * p.x + _a * p.x + _b) % _f->modulo))
       return true;
    else
       return false;
 }

Point EllipticCurve::invertedPoint(const Point& p) const {
    if (p == neutral)
        return neutral;
    return { p.x, subtract(_f->modulo, p.y,_f->modulo) };
}

Point EllipticCurve::addPoints(const Point& first, const Point& second) const {
    if ((first == neutral) || (second == neutral))
        return first == neutral ? second : first;

    if ((first.x == second.x && first.y != second.y)
        || (first == second && first.y == 0_bn))
    {
        return neutral;
    } else {
        BigNum tmp1;
        BigNum tmp2;
        BigNum m;
        if (first.x != second.x) {
            ///y2-y1
            tmp1 = subtract(second.y, first.y, _f->modulo);

            ///x2-x1
            tmp2 = subtract(second.x, first.x, _f->modulo);
        } else {
            ///x1^2
            tmp1 = powMontgomery(first.x, 2_bn, _f->modulo);
            
            ///3*x1^2
            tmp1 = multiply(3_bn, tmp1, _f->modulo);
            
            ///3*x1^2 + A
            tmp1 = add(tmp1, _a, _f->modulo);
            
            ///2*y1
            tmp2 = multiply(2_bn, first.y, _f->modulo);
        }
        
        ///(y2 - y1)/(x2 - x1) or (3*x1^2 + A)/(2*y1)
        m = multiply(tmp1, inverted(tmp2, _f->modulo, BigNum::InversionPolicy::Fermat), _f->modulo);

        ///m^2
        tmp1 = multiply(m, m, _f->modulo); 

        ///x1 + x2
        tmp2 = add(first.x, second.x, _f->modulo); 
		
        ///x3 = m^2 - x1 - x2
        tmp1 = subtract(tmp1, tmp2, _f->modulo); 

        ///x1 - x3
        tmp2 = subtract(first.x, tmp1, _f->modulo); 			

        ///m*(x1 - x3)
        tmp2 = multiply(m, tmp2, _f->modulo); 
        
        ///y3 = m*(x1 - x3) - y1
        tmp2 = subtract(tmp2, first.y, _f->modulo); 

        ///{x3,y3} - answer
        return{ tmp1,tmp2 };
    }
}

/**
 * @brief Following function provides taking the point to the power of a
 */

    Point EllipticCurve::powerPoint(const Point& point, const BigNum& a) const {
        if (a == 0_bn){
            return neutral;
        }
        if (a == 1_bn){
            return point;
        }
        std::pair<BigNum, BigNum> divMod = extract(a, 2_bn);
        Point squared = powerPoint(point,divMod.first); // let squared be point^(a/2)
        if(divMod.second == 0_bn) { // checking if a % 2 == 0
            return addPoints(squared,squared);

        } else {
            return addPoints(addPoints(squared,squared),point);
        }
    }

    BigNum EllipticCurve::getFieldModulo() const{
        return _f->modulo;
    }

    BigNum EllipticCurve::pointOrder(const Point& p) const {

        // Calculate Q = (q + 1) * p

        Point Q = powerPoint(p, _f->modulo + 1_bn);

        BigNum q_sqrt = sqrt(_f->modulo);
        BigNum m = sqrt(q_sqrt) + 1_bn;

        std::vector<Point> calculated_points;

        // Calculate and store points i * p for i = 1 .. m, where m = [modulo ^ (1/4)]

        Point point = p;
        for (BigNum i = 1_bn; i <= m; i = i + 1_bn){
            calculated_points.push_back(point);
            point = addPoints(point, p);
        }

        bool negative = true;
        point = powerPoint(p, 2_bn * m);
        Point right_part(0_bn, 0_bn);
        BigNum k = m;


        // calculate new point: result = Q + right_part
        // where right_part = k * (2 * m * p)
        // for k = -m, - m + 1, ..., -1, 0, 1, ..., m - 1, m

        while (true){

            if (k == 0_bn) negative = false;

            if (negative){
                right_part = invertedPoint(powerPoint(point, k));
            } else {
                right_part = powerPoint(point, k);
            }

            Point result = addPoints(Q, right_part);

            // check if calculated point result is equal to saved point or ist inverted
            // (result i * p or - i * p)
            // if yes then Q + k * (2 * m * p) = (+-) i * p, hence (while Q = (modulo + 1) * p)
            // ( modulo + 1 + k * (2 * m) (-+) i ) * p = neutral
            // so we get that order is divisor of M = modulo + 1 + k * (2 * m) (-+) i

            BigNum index = 1_bn;
            for (const auto& i : calculated_points){

                if (result == i){
                    BigNum M = negative ? (_f->modulo + 1_bn - 2_bn * m * k - index) :
                                    (_f->modulo + 1_bn + 2_bn * m * k - index);
                    M = M % _f->modulo;
                    return reduce(M, p); // return function which finds divisor which is order
                } else if (result == invertedPoint(i)){
                    BigNum M = negative ? (_f->modulo + 1_bn - 2_bn * m * k + index ) :
                        (_f->modulo + 1_bn + 2_bn * m * k + index);
                    M = M % _f->modulo;
                    return reduce(M, p); // return function which finds divisor which is order
                }

                index = index + 1_bn;
            }

            if (negative){
                k = k - 1_bn;
                if (k == 0_bn) negative = false;
            } else {
                k = k + 1_bn;
            }

            if (k >= m + 1_bn){
                break;
            }
        }


        BigNum left = _f->modulo + 1_bn - 2_bn * q_sqrt;
        BigNum right = _f->modulo + 1_bn + 2_bn * q_sqrt;
        point = powerPoint(p, left);
        for (BigNum i = left; i <= right; i = i + 1_bn){
            if (point == EllipticCurve::neutral){
                return reduce(i, p);
            }
            point = addPoints(point, p);
        }

        return BigNum("Thank you for your attention!!!)");
    }

    BigNum EllipticCurve::reduce(BigNum& M, const Point& p) const {
        auto divisors = factorization(M);

        bool all_not_infinity = true;
        while (all_not_infinity){
            all_not_infinity = false;
            for (auto& div : divisors){
                if (div.second > 0_bn && powerPoint(p, M/div.first) == neutral){
                    div.second = div.second - 1_bn;
                    all_not_infinity = true;
                    M = M/div.first;
                } else div.second = 0_bn;
            }
        }

        return M;
    }

    BigNum EllipticCurve::countPoints() const {
        BigNum left = _f->modulo + 1_bn - 2_bn * sqrt(_f->modulo);
        BigNum right = _f->modulo + 1_bn + 2_bn * sqrt(_f->modulo);
        BigNum lcm = 1_bn;
        BigNum x = 1_bn;
        while (!(left <= lcm && lcm <= right)){
            while (!sqrt(x * x * x + x * _a + _b, _f->modulo) ||
                   !contains(Point(x, sqrt(x * x * x + x * _a + _b, _f->modulo)->second))){
                x = x + 1_bn;
            }
            Point point = Point(x, sqrt(x * x * x + x * _a + _b, _f->modulo)->second);
            if (contains(point)) {
                BigNum point_order = pointOrder(point);
                lcm = point_order * lcm / gcd(point_order, lcm);
            }
            x = x + 1_bn;
        }
        return lcm;
    }
}