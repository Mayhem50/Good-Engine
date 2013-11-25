#pragma once
#include <assert.h>

#include "Math.h"

namespace Good
{
	struct Vector2;

	struct GOOD_DLL Vector3
	{
		Vector3 ();
		Vector3 (Real fX, Real fY, Real fZ);
		Vector3 (const Real* afTuple);
		Vector3 (const Vector3& rkV);
		Vector3( const int coord[3]);
		Vector3(const Vector2& rkV);

		void swap(Vector3& other)
		{
			std::swap(x, other.x);
			std::swap(y, other.y);
			std::swap(z, other.z);
		}

		// coordinate access
		Real operator[] (const size_t i) const;
		Real& operator[] (const size_t i);

		// assignment
		Vector3& operator= (const Vector3& rkV);

		// comparison
		bool operator== (const Vector3& rkV) const;
		bool operator!= (const Vector3& rkV) const;
		bool operator<  (const Vector3& rkV) const;
		bool operator<= (const Vector3& rkV) const;
		bool operator>  (const Vector3& rkV) const;
		bool operator>= (const Vector3& rkV) const;

		// arithmetic operations
		Vector3 operator+ (const Vector3& rkV) const;
		Vector3 operator- (const Vector3& rkV) const;
		Vector3 operator* (Real fScalar) const;
		Vector3 operator/ (Real fScalar) const;
		Vector3 operator- () const;
		const Vector3& operator+ () const;

		// arithmetic updates
		Vector3& operator+= (const Vector3& rkV);
		Vector3& operator-= (const Vector3& rkV);
		Vector3& operator*= (Real fScalar);
		Vector3& operator/= (Real fScalar);

		// vector operations
		Real length () const;
		Real sqrLength () const;
		Real dotProduct (const Vector3& rkV) const;
		Real normalize ();

		// The cross products are computed using the right-handed rule.  Be aware
		// that some graphics APIs use a left-handed rule.  If you have to compute
		// a cross product with these functions and send the result to the API
		// that expects left-handed, you will need to change sign on the vector
		// (replace each component value c by -c).
		Vector3 cross (const Vector3& rkV) const;
		Vector3 unitCross (const Vector3& rkV) const;

		// Gram-Schmidt orthonormalization.  Take linearly independent vectors
		// U, V, and W and compute an orthonormal set (unit length, mutually
		// perpendicular).
		static void orthonormalize (Vector3& rkU, Vector3& rkV, Vector3& rkW);
		static void orthonormalize (Vector3* akV);

		// Input W must be a nonzero vector. The output is an orthonormal basis
		// {U,V,W}.  The input W is normalized by this function.  If you know
		// W is already unit length, use GenerateComplementBasis to compute U
		// and V.
		static void generateOrthonormalBasis (Vector3& rkU, Vector3& rkV,
			Vector3& rkW);

		// Input W must be a unit-length vector.  The output vectors {U,V} are
		// unit length and mutually perpendicular, and {U,V,W} is an orthonormal
		// basis.
		static void generateComplementBasis (Vector3& rkU, Vector3& rkV,
			const Vector3& rkW);

		// Compute the extreme values.
		static void computeExtremes (int iVQuantity, const Vector3* akPoint,
			Vector3& rkMin, Vector3& rkMax);

		inline friend ::std::ostream& operator<<(std::ostream& out, const Vector3& rkV)
		{
			out << rkV.x << "|" << rkV.y << "|" << rkV.z << std::endl;
		}

		inline std::string toString()
		{
			char buffer[MAX_CHAR];
			sprintf_s(buffer, "\n\t%.3lf | %.3lf | %.3lf", x, y, z);
			return std::string("\n") + typeid(*this).name() + std::string(buffer);
		}

		// special vectors
		static const Vector3 ZERO;    // (0,0,0)
		static const Vector3 UNIT_X;  // (1,0,0)
		static const Vector3 UNIT_Y;  // (0,1,0)
		static const Vector3 UNIT_Z;  // (0,0,1)
		static const Vector3 UNIT_SCALE;     // (1,1,1)

		Real x, y, z;		
	};
}
