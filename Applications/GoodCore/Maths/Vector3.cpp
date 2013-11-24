#include "Vector3.h"

using namespace Good; 

const Vector3 Vector3::ZERO( 0, 0, 0 );
const Vector3 Vector3::UNIT_X( 1, 0, 0 );
const Vector3 Vector3::UNIT_Y( 0, 1, 0 );
const Vector3 Vector3::UNIT_Z( 0, 0, 1 );
const Vector3 Vector3::UNIT_SCALE(1, 1, 1);

inline Vector3::Vector3 ()
{
	// uninitialized for performance in array construction
}

inline Vector3::Vector3 (Real fX, Real fY, Real fZ):
	x(fX), y(fY), z(fZ)
{
}

inline Vector3::Vector3 (const Real* coord):
	x((Real)coord[0]), y((Real)coord[1]), z((Real)coord[2])
{
}

inline Vector3::Vector3 (const Vector3& rkV):
	x(rkV.x), y(rkV.y), z(rkV.z)
{
}

inline Vector3::Vector3(const int coord[3]):
	x((Real)coord[0]), y((Real)coord[1]), z((Real)coord[2])
{
}

inline Real Vector3::operator[] (const size_t i) const
{
	assert( i < 3 );

	return *(&x+i);
}

inline Real& Vector3::operator[] (const size_t i)
{
	assert( i < 3 );

	return *(&x+i);
}

inline Vector3& Vector3::operator= (const Vector3& rkV)
{
	x = rkV.x;
	y = rkV.y;
	z = rkV.z;
	return *this;
}

inline bool Vector3::operator== (const Vector3& rkV) const
{
	return (x == rkV.x && y == rkV.y && z == rkV.z);
}

inline bool Vector3::operator!= (const Vector3& rkV) const
{
	return !(this->operator==(rkV));
}

inline Vector3 Vector3::operator+ (const Vector3& rkV) const
{
	return Vector3(
		x+rkV.x,
		y+rkV.y,
		z+rkV.z);
}

inline Vector3 Vector3::operator- (const Vector3& rkV) const
{
	return Vector3(
		x-rkV.x,
		y-rkV.y,
		z-rkV.z);
}

inline Vector3 Vector3::operator* (Real fScalar) const
{
	return Vector3(
		fScalar*x,
		fScalar*y,
		fScalar*z);
}

inline Vector3 Vector3::operator/ (Real fScalar) const
{
	Vector3 kQuot;

	if (fScalar != (Real)0.0)
	{
		Real fInvScalar = ((Real)1.0)/fScalar;
		kQuot.x = fInvScalar*x;
		kQuot.y = fInvScalar*y;
		kQuot.z = fInvScalar*z;
	}
	else
	{
		kQuot.x = Math::MAX_REAL;
		kQuot.y = Math::MAX_REAL;
		kQuot.z = Math::MAX_REAL;
	}

	return kQuot;
}

inline Vector3 Vector3::operator- () const
{
	return Vector3(
		-x,
		-y,
		-z);
}

inline const Vector3& Vector3::operator+ () const
{
	return *this;
}

inline Vector3 operator* (Real fScalar, const Vector3& rkV)
{
	return Vector3(
		fScalar*rkV[0],
		fScalar*rkV[1],
		fScalar*rkV[2]);
}

inline Vector3& Vector3::operator+= (const Vector3& rkV)
{
	x += rkV.x;
	y += rkV.y;
	z += rkV.z;
	return *this;
}

inline Vector3& Vector3::operator-= (const Vector3& rkV)
{
	x -= rkV.x;
	y -= rkV.y;
	z -= rkV.z;
	return *this;
}

inline Vector3& Vector3::operator*= (Real fScalar)
{
	x *= fScalar;
	y *= fScalar;
	z *= fScalar;
	return *this;
}

inline Vector3& Vector3::operator/= (Real fScalar)
{
	if (fScalar != (Real)0.0)
	{
		Real fInvScalar = ((Real)1.0)/fScalar;
		x *= fInvScalar;
		y *= fInvScalar;
		z *= fInvScalar;
	}
	else
	{
		x = Math::MAX_REAL;
		y = Math::MAX_REAL;
		z = Math::MAX_REAL;
	}

	return *this;
}

inline Real Vector3::length () const
{
	return Math::Sqrt(
		x*x +
		y*y +
		z*z);
}

inline Real Vector3::sqrLength () const
{
	return
		x*x +
		y*y +
		z*z;
}

inline Real Vector3::dotProduct (const Vector3& rkV) const
{
	return
		x*rkV.x +
		y*rkV.y +
		z*rkV.z;
}

inline Real Vector3::normalize ()
{
	Real fLength = length();

	if (fLength > Math::ZERO_TOLERANCE)
	{
		Real fInvLength = ((Real)1.0)/fLength;
		x *= fInvLength;
		y *= fInvLength;
		z *= fInvLength;
	}
	else
	{
		fLength = (Real)0.0;
		x = (Real)0.0;
		y = (Real)0.0;
		z = (Real)0.0;
	}

	return fLength;
}

inline Vector3 Vector3::cross (const Vector3& rkV) const
{
	return Vector3(
		y*rkV.z - z*rkV.y,
		z*rkV.x - x*rkV.z,
		x*rkV.y - y*rkV.x);
}

inline Vector3 Vector3::unitCross (const Vector3& rkV) const
{
	Vector3 kCross(
		y*rkV.z - z*rkV.y,
		z*rkV.x - x*rkV.z,
		x*rkV.y - y*rkV.x);
	kCross.normalize();
	return kCross;
}

void Vector3::orthonormalize (Vector3& rkU, Vector3& rkV, Vector3& rkW)
{
	// If the input vectors are v0, v1, and v2, then the Gram-Schmidt
	// orthonormalization produces vectors u0, u1, and u2 as follows,
	//
	//   u0 = v0/|v0|
	//   u1 = (v1-(u0*v1)u0)/|v1-(u0*v1)u0|
	//   u2 = (v2-(u0*v2)u0-(u1*v2)u1)/|v2-(u0*v2)u0-(u1*v2)u1|
	//
	// where |A| indicates length of vector A and A*B indicates dot
	// product of vectors A and B.

	// compute u0
	rkU.normalize();

	// compute u1
	Real fDot0 = rkU.dotProduct(rkV); 
	rkV -= fDot0*rkU;
	rkV.normalize();

	// compute u2
	Real fDot1 = rkV.dotProduct(rkW);
	fDot0 = rkU.dotProduct(rkW);
	rkW -= fDot0*rkU + fDot1*rkV;
	rkW.normalize();
}

void Vector3::orthonormalize (Vector3* akV)
{
	orthonormalize(akV[0],akV[1],akV[2]);
}

void Vector3::generateOrthonormalBasis (Vector3& rkU, Vector3& rkV,
										Vector3& rkW)
{
	rkW.normalize();
	generateComplementBasis(rkU,rkV,rkW);
}

void Vector3::generateComplementBasis (Vector3& rkU, Vector3& rkV,
									   const Vector3& rkW)
{
	Real fInvLength;

	if (Math::FAbs(rkW.x) >=
		Math::FAbs(rkW.y) )
	{
		// W.x or W.z is the largest magnitude component, swap them
		fInvLength = Math::InvSqrt(rkW.x*rkW.x +
			rkW.z*rkW.z);
		rkU.x = -rkW.z*fInvLength;
		rkU.y = (Real)0.0;
		rkU.z = +rkW.x*fInvLength;
		rkV.x = rkW.y*rkU.z;
		rkV.y = rkW.z*rkU.x -
			rkW.x*rkU.z;
		rkV.z = -rkW.y*rkU.x;
	}
	else
	{
		// W.y or W.z is the largest magnitude component, swap them
		fInvLength = Math::InvSqrt(rkW.y*rkW.y +
			rkW.z*rkW.z);
		rkU.x = (Real)0.0;
		rkU.y = +rkW.z*fInvLength;
		rkU.z = -rkW.y*fInvLength;
		rkV.x = rkW.y*rkU.z -
			rkW.z*rkU.y;
		rkV.y = -rkW.x*rkU.z;
		rkV.z = rkW.x*rkU.y;
	}
}

void Vector3::computeExtremes (int iVQuantity, const Vector3* akPoint,
							   Vector3& rkMin, Vector3& rkMax)
{
	assert(iVQuantity > 0 && akPoint);

	rkMin = akPoint[0];
	rkMax = rkMin;
	for (int i = 1; i < iVQuantity; i++)
	{
		const Vector3& rkPoint = akPoint[i];
		for (int j = 0; j < 3; j++)
		{
			if (rkPoint[j] < rkMin[j])
			{
				rkMin[j] = rkPoint[j];
			}
			else if (rkPoint[j] > rkMax[j])
			{
				rkMax[j] = rkPoint[j];
			}
		}
	}
}

