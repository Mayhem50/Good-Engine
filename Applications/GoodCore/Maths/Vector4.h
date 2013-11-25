#pragma once
#include <assert.h>

#include "Math.h"

namespace Good
{
	struct Vector3;

	struct Vector4
	{
		Vector4 ();
		Vector4 (Real fX, Real fY, Real fZ, Real fW);
		Vector4 (const Real* afTuple);
		Vector4 (const Vector4& rkV);
		Vector4( const int coord[4]);
		Vector4( const Vector3& rkV);

		void swap(Vector4& other)
		{
			std::swap(x, other.x);
			std::swap(y, other.y);
			std::swap(z, other.z);
			std::swap(w, other.w);
		}

		// coordinate access
		Real operator[] (const size_t idx) const;
		Real& operator[] (const size_t idx);

		// assignment
		Vector4& operator= (const Vector4& rkV);		
		Vector4& operator= (const Vector3& rkV);

		// comparison
		bool operator== (const Vector4& rkV) const;
		bool operator!= (const Vector4& rkV) const;
		bool operator<  (const Vector4& rkV) const;
		bool operator<= (const Vector4& rkV) const;
		bool operator>  (const Vector4& rkV) const;
		bool operator>= (const Vector4& rkV) const;

		// arithmetic operations
		Vector4 operator+ (const Vector4& rkV) const;		
		const Vector4& operator+ () const;
		Vector4 operator- (const Vector4& rkV) const;
		Vector4 operator* (Real fScalar) const;
		Vector4 operator/ (Real fScalar) const;
		Vector4 operator- () const;

		// arithmetic updates
		Vector4& operator+= (const Vector4& rkV);
		Vector4& operator+= (const Real scalar);
		Vector4& operator-= (const Vector4& rkV);		
		Vector4& operator-= (const Real scalar);
		Vector4& operator*= (Real fScalar);
		Vector4& operator/= (Real fScalar);

		// vector operations
		Real length () const;
		Real sqrLength () const;
		Real dotProduct (const Vector4& rkV) const;
		Real normalize ();

		inline friend ::std::ostream& operator<<(std::ostream& out, const Vector4& rkV)
		{
			out << rkV.x << "|" << rkV.y << "|" << rkV.z << "|" << rkV.w << std::endl;
		}

		inline std::string toString()
		{
			char buffer[MAX_CHAR];
			sprintf_s(buffer, "\n\t%.3lf | %.3lf | %.3lf | %.3lf", x, y, z, w);
			return std::string("\n") + typeid(*this).name() + std::string(buffer);
		}

		// special vectors
		static const Vector4 ZERO;    // (0,0,0,0)
		static const Vector4 UNIT_X;  // (1,0,0,0)
		static const Vector4 UNIT_Y;  // (0,1,0,0)
		static const Vector4 UNIT_Z;  // (0,0,1,0)		
		static const Vector4 UNIT_W;  // (0,0,0,1)
		static const Vector4 UNIT_SCALE;     // (1,1,1,1)

		Real x, y, z, w;		
	};
}
