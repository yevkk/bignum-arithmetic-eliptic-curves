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
    if (powMontgomery(p.y, 2_bn, _f->modulo)
           == add(powMontgomery(p.x, 3_bn,_f->modulo), add(multiply(_a, p.x, _f->modulo), _b, _f->modulo), _f->modulo))
       return true;
    else 
       return false;
 }

Point EllipticCurve::invertedPoint(const Point& p) const {
    if (p == neutral)
        return neutral;
    return { p.x,subtract( _f->modulo, p.y,_f->modulo) };
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

} // namespace lab