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
    
    if (multiply(p.y, p.y, _f->modulo)
           == add(multiply(multiply(p.x, p.x, _f->modulo), p.x, _f->modulo), add(multiply(_a, p.x, _f->modulo), _b, _f->modulo), _f->modulo))
       return true;
    else 
       return false;
 }

Point EllipticCurve::invertedPoint(const Point& p) const {
    if (p == neutral)
        return neutral;
    return { p.x,_f->modulo - p.y };
}

Point EllipticCurve::addPoints(const Point& first, const Point& second) const {
    if (first == neutral || second == neutral)
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
        tmp1 = second.y >= first.y ? 
                subtract(second.y, first.y, _f->modulo) 
                : add(subtract(_f->modulo, first.y, _f->modulo), second.y, _f->modulo); //y2-y1

        tmp2 = second.x >= first.x ? 
                subtract(second.x, first.x, _f->modulo) 
                : add(subtract(_f->modulo, first.x, _f->modulo), second.x, _f->modulo); //x2-x1
        } else {      
            tmp1 = multiply(first.x, first.x, _f->modulo); //x1^2
            tmp1 = multiply(3_bn, tmp1, _f->modulo); //3*x1^2
            tmp1 = add(tmp1, _a, _f->modulo);//3*x1^2 + A
            tmp2 = multiply(2_bn, first.y, _f->modulo);//2y1
        }
        m = multiply(tmp1,lab::inverted(tmp2,_f->modulo, BigNum::InversionPolicy::Fermat),_f->modulo); //tmp1 / tmp2

        tmp1 = multiply(m, m, _f->modulo);//= m^2

        tmp2 = add(first.x, second.x, _f->modulo); //= x1+x2
			
        tmp1 = tmp1 >= tmp2 ?
                subtract(tmp1, tmp2, _f->modulo)
                : add(subtract(_f->modulo, tmp2, _f->modulo), tmp1, _f->modulo); //= x3

        tmp2 = first.x >= tmp1 ? 
                subtract(first.x, tmp1, _f->modulo) 
                : add(subtract(_f->modulo, tmp1, _f->modulo), first.x, _f->modulo); //= x1-x3			

        tmp2 = multiply(m, tmp2, _f->modulo); //= m*(x1-x3)

        tmp2 = tmp2 >= first.y ?
                subtract(tmp2, first.y, _f->modulo)
                : add(subtract(_f->modulo, first.y, _f->modulo), tmp2, _f->modulo); //= y3

        return{ tmp1,tmp2 }; //{x3,y3} - answer
    }
}
}