#pragma once

#include "EllipticCurves.hpp"
#include <array>

namespace lab {

struct FieldMeta {
    Field field;
    static constexpr int CURVES_PER_FIELED = 3;
    std::array<EllipticCurve, CURVES_PER_FIELED>  curves;
};
    
/**
* @brief Elliptic curves database with thier labels on https://www.lmfdb.org/EllipticCurve/Q/
*        (paste label into a box near the big blue button)
*/
inline const int FIELD_NUMBER = 3;
inline const FieldMeta curveDataBase[] = {
    {Field(234131_bn),
        {EllipticCurve(new Field(234131_bn),228960_bn,91781_bn), //100016.g1
         EllipticCurve(new Field(234131_bn),3133_bn,46606_bn), //100040.g1
         EllipticCurve(new Field(234131_bn),227064_bn,9977_bn) //100040.g4
        } 
    }, 
    {Field(80000005213_bn),
        {EllipticCurve(new Field(80000005213_bn),39912548_bn,7610314_bn), //100016.h1
         EllipticCurve(new Field(80000005213_bn),39796616_bn,38003178_bn), //100040.d2
         EllipticCurve(new Field(80000005213_bn),79966658546_bn,74118524074_bn) //200080.q1
        } 
    },
    {Field(773_bn),
        {EllipticCurve(new Field(773_bn),761_bn,65_bn), //252.a2
         EllipticCurve(new Field(773_bn),446_bn,724_bn), //252.a1
         EllipticCurve(new Field(773_bn),7361_bn,20_bn) //216.a1
        }
    }
};
} // namespace lab
