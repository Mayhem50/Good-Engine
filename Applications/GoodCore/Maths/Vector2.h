#pragma once

#include <assert.h>

#include "Math.h"

namespace Good
{
	class Vector2
	{
	public:
		Vector2(void);
		Vector2(const Real fX, const Real fY);
		Vector2(const Real scaler);
		Vector2(const Real coord[2]);
		Vector2(const int coord[2]);

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
		Real module() const const ;
		Real distance(const Vector2& rkV) const ;
		Real sqrDistance(const Vector2& rkV) const ;
		Real dotProduct(const Vector2& rkV) const ;
		Real normalise();
		Vector2 distanceBetween(const Vector2& rkV) const ;
		Vector2 midpoint() const;
		Real crosProduct(const Vector2& rkV) const;

		Vector2 perpendicular();
		
		Real x, y;
	};
}

