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
    if (multiply(p.y, p.y, _f->generator)
           == lab::add(multiply(multiply(p.x, p.x, _f->generator), p.x, _f->generator), lab::add(multiply(_a, p.x, _f->generator), _b, _f->generator), _f->generator))
       return true;
    else 
       return false;
 }

Point EllipticCurve::inverted(const Point& p) {
    return { p.x,_f->generator - p.y };
}

Point EllipticCurve::add(const Point& first, const Point& second) {
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
                subtract(second.y, first.y, _f->generator) 
                : lab::add(subtract(_f->generator, first.y, _f->generator), second.y, _f->generator); //y2-y1

        tmp2 = second.x >= first.x ? 
                subtract(second.x, first.x, _f->generator) 
                : lab::add(subtract(_f->generator, first.x, _f->generator), second.x, _f->generator); //x2-x1
        } else {      
            tmp1 = multiply(first.x, first.x, _f->generator); //x1^2
            tmp1 = multiply(3_bn, tmp1, _f->generator); //3*x1^2
            tmp1 = lab::add(tmp1, _a, _f->generator);//3*x1^2 + A
            tmp2 = multiply(2_bn, first.y, _f->generator);//2y1
        }
        m = multiply(tmp1,lab::inverted(tmp2,_f->generator, BigNum::InversionPolicy::Fermat),_f->generator); //tmp1 / tmp2

        tmp1 = multiply(m, m, _f->generator);//= m^2

        tmp2 = lab::add(first.x, second.x, _f->generator); //= x1+x2
			
        tmp1 = tmp1 >= tmp2 ?
                subtract(tmp1, tmp2, _f->generator)
                : lab::add(subtract(_f->generator, tmp2, _f->generator), tmp1, _f->generator); //= x3

        tmp2 = first.x >= tmp1 ? 
                subtract(first.x, tmp1, _f->generator) 
                : lab::add(subtract(_f->generator, tmp1, _f->generator), first.x, _f->generator); //= x1-x3			

        tmp2 = multiply(m, tmp2, _f->generator); //= m*(x1-x3)

        tmp2 = tmp2 >= first.y ?
                subtract(tmp2, first.y, _f->generator)
                : lab::add(subtract(_f->generator, first.y, _f->generator), tmp2, _f->generator); //= y3

        return{ tmp1,tmp2 }; //{x3,y3} - answer
    }
}
}