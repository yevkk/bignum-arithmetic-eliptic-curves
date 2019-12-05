#include <KeyGenerator.h>

namespace lab{

Client::Client(const EllipticCurve& curve, const BigNum& pow, const Point& point)
                : _curve(curve), _pow(pow), _point(point), _private_key(Point(0_bn, 0_bn)) {}

Point Client::getPrivateKey() const{
    return _private_key;
}

Point Client::getPublicKey() const{
    return _curve.powerPoint(_point, _pow);
}

Point Client::getPoint() const{
    return _point;
}

EllipticCurve Client::getCurve() const{
    return _curve;
}

void Client::setPrivateKey(const Point& gotPublicKey) {
    try{
        _private_key = _curve.powerPoint(gotPublicKey, _pow);
    }
    catch(std::exception& e){
        std::cout << _pow << std::endl;
    }
}

GettingKeySimulation::GettingKeySimulation(const EllipticCurve& curve, const BigNum& xPow, const BigNum& yPow, const Point& point)
                                           : _curve(curve), _point(point), _x_pow(xPow), _y_pow(yPow),
                                             _alice(Client(curve, xPow, point)), _bob(Client(curve, yPow, point)) {
    _alice.setPrivateKey(_bob.getPublicKey());
    _bob.setPrivateKey(_alice.getPublicKey());
}

Point GettingKeySimulation::getAlicePrivateKey() const {
    return _alice.getPublicKey();
}

Point GettingKeySimulation::getBobPrivateKey() const {
    return _bob.getPublicKey();
}

}