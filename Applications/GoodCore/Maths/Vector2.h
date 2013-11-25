#pragma once

#include <assert.h>

#include "Math.h"

namespace Good
{
	struct GOOD_DLL Vector2
	{
		Vector2(void);
		Vector2(const Real fX, const Real fY);
		Vector2(const Real scaler);
		Vector2(const Real coord[2]);

		inline void swap(Vector2& rkV)
		{
			std::swap(x, rkV.x);
			std::swap(y, rkV.y);
		}

		Real operator [] (const size_t idx) const;
		Real& operator [] (const size_t idx);

		Vector2& operator = (const Vector2& rkV);
		Vector2& operator = (const Real rkV);

		bool operator == (const Vector2& rkV) const ;
		bool operator != (const Vector2& rkV) const ;

		Vector2 operator + (const Vector2& rkV) const ;
		Vector2 operator - (const Vector2& rkV) const ;
		Vector2 operator - () const ;
		Vector2 operator * (const Vector2& rkV) const ;
		Vector2 operator * (const Real scalar) const ;
		Vector2 operator / (const Vector2& rkV) const ;
		Vector2 operator / (const Real rkV) const ;

		Vector2& operator += (const Vector2& rkV);		
		Vector2& operator += (const Real scalar);
		Vector2& operator -= (const Vector2& rkV);
		Vector2& operator -= (const Real scalar);
		Vector2& operator *= (const Vector2& rkV);
		Vector2& operator *= (const Real scalar);
		Vector2& operator /= (const Vector2& rkV);
		Vector2& operator /= (const Real scalar);

		Real lenght() const;
		Real sqrLenght() const;
		Real module() const;
		Real distance(const Vector2& rkV) const ;
		Real sqrDistance(const Vector2& rkV) const ;
		Real dotProduct(const Vector2& rkV) const ;
		Real normalise();
		Vector2 distanceBetween(const Vector2& rkV) const ;
		Vector2 midpoint() const;
		Real crosProduct(const Vector2& rkV) const;

		Vector2 perpendicular();

		static const Vector2 ZERO;    // (0,0)
		static const Vector2 UNIT_X;  // (1,0)
		static const Vector2 UNIT_Y;  // (0,1)

		inline friend ::std::ostream& operator<<(std::ostream& out, const Vector2& rkV)
		{
			out << rkV.x << "|" << rkV.y << std::endl;
		}

		inline std::string toString()
		{
			char buffer[MAX_CHAR];
			sprintf_s(buffer, "\n\t%.3lf | %.3lf", x, y);
			return std::string("\n") + typeid(*this).name() + std::string(buffer);
		}
		
		Real x, y;
	};
}

