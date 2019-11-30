#pragma once

#include "BigNum.hpp"
#include <vector>

namespace lab {
	namespace {
		constexpr int CURVES_PER_FIELED = 3;

		constexpr int NUM_FIELDS = 4;
	}

	struct Point {
		BigNum x;
		BigNum y;

		friend bool operator==(const Point& left, const Point& right) {
			return (left.x == right.x) && (left.y == right.y);
		}
	};

	struct Field {
		BigNum generator;
		Field(const BigNum& g):generator(g){}

		friend bool operator==(const Field& left, const Field& right) {
			return left.generator == right.generator;
		}		
	};

	class EllipticCurve {
	public:
		EllipticCurve(const EllipticCurve& that) = default;
		
		EllipticCurve(Field* f, const BigNum& a, const BigNum& b);
		
		EllipticCurve() = default;

		EllipticCurve& operator=(const EllipticCurve& that) = default;

		friend bool operator==(const EllipticCurve& left, const EllipticCurve& right);
		friend bool operator!=(const EllipticCurve& left, const EllipticCurve& right);

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const EllipticCurve& curve);

		/**
		* @return True if elliptic curve contains given point, otherwise false
		*/
		bool contains(const Point& p) const;

		/**
		* @brief Looks for points on curve with given x-coordinate
		* @return Vector of matching points
		*/
		std::vector<Point> findPoints(const BigNum& x);

		/**
		* @brief p must belong to curve
		*/
		Point inverted(const Point& p);

		Point add(const Point& first, const Point& second);

	private:
		///< y^2 = x^3 + a*x + b on field f
		Field* _f;
		BigNum _a;
		BigNum _b;
	};

	template<typename OStream>
	OStream& operator<<(OStream& os, const EllipticCurve& curve) {
		os << "y^2 = x^3 + " << curve._a << "x + " << curve._b;
		return os;
	}

	struct FieldMeta {
		Field F;
		EllipticCurve curves[CURVES_PER_FIELED];
	};
} // namespace lab
