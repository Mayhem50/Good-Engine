#include "Vector4.h"

using namespace Good; 

const Vector4 Vector4::ZERO( 0, 0, 0, 0 );
const Vector4 Vector4::UNIT_X( 1, 0, 0, 0 );
const Vector4 Vector4::UNIT_Y( 0, 1, 0, 0 );
const Vector4 Vector4::UNIT_Z( 0, 0, 1, 0 );
const Vector4 Vector4::UNIT_W( 0, 0, 0, 1 );
const Vector4 Vector4::UNIT_SCALE(1, 1, 1, 1);

inline Vector4::Vector4 ()
{
	// uninitialized for performance in array construction
}

inline Vector4::Vector4 (Real fX, Real fY, Real fZ, Real fW):
	x(fX), y(fY), z(fZ), w(fW)
{
}

inline Vector4::Vector4 (const Real* coord):
	x((Real)coord[0]), y((Real)coord[1]), 
	z((Real)coord[2]), w((Real)coord[3])
{
}

inline Vector4::Vector4 (const Vector4& rkV):
	x(rkV.x), y(rkV.y), z(rkV.z), w(rkV.w)
{
}

inline Vector4::Vector4(const int coord[4]):
	x((Real)coord[0]), y((Real)coord[1]), 
	z((Real)coord[2]), w((Real)coord[3])
{
}

inline Vector4::Vector4(const Vector3& rkV):
	x(rkV.x), y(rkV.y), z(rkV.z), w((Real)1.0)
{
}

inline Real Vector4::operator[] (const size_t i) const
{
	assert( i < 4 );

	return *(&x+i);
}

inline Real& Vector4::operator[] (const size_t i)
{
	assert( i < 4 );

	return *(&x+i);
}

inline Vector4& Vector4::operator= (const Vector4& rkV)
{
	x = rkV.x;
	y = rkV.y;
	z = rkV.z;
	w = rkV.w;

	return *this;
}

inline Vector4& Vector4::operator= (const Vector3& rkV)
{
	x = rkV.x;
	y = rkV.y;
	z = rkV.z;
	w = (Real)1.0;

	return *this;
}

inline bool Vector4::operator== (const Vector4& rkV) const
{
	return (x == rkV.x && y == rkV.y && 
		z == rkV.z && w == rkV.w);
}

inline bool Vector4::operator!= (const Vector4& rkV) const
{
	return !(this->operator==(rkV));
}

inline Vector4 Vector4::operator+ (const Vector4& rkV) const
{
	return Vector4(
		x + rkV.x,
		y + rkV.y,
		z + rkV.z,
		w + rkV.w);
}

inline Vector4 Vector4::operator- (const Vector4& rkV) const
{
	return Vector4(
		x - rkV.x,
		y - rkV.y,
		z - rkV.z,
		w - rkV.w);
}

inline Vector4 Vector4::operator* (Real scalar) const
{
	return Vector4(
		scalar * x,
		scalar * y,
		scalar * z,
		scalar * w);
}

inline Vector4 Vector4::operator/ (Real scalar) const
{
	Vector4 kQuot;

	if (scalar != (Real)0.0)
	{
		Real fInvScalar = ((Real)1.0)/scalar;
		kQuot.x = fInvScalar * x;
		kQuot.y = fInvScalar * y;
		kQuot.z = fInvScalar * z;		
		kQuot.w = fInvScalar * w;
	}

	else
	{
		kQuot.x = Math::MAX_REAL;
		kQuot.y = Math::MAX_REAL;
		kQuot.z = Math::MAX_REAL;
		kQuot.w = Math::MAX_REAL;
	}

	return kQuot;
}

inline const Vector4& Vector4::operator+ () const
{
	return *this;
}

inline Vector4 Vector4::operator- () const
{
	return Vector4(
		-x,
		-y,
		-z,
		-w);
}

inline Vector4 operator* (Real scalar, const Vector4& rkV)
{
	return Vector4(
		scalar * rkV[0],
		scalar * rkV[1],
		scalar * rkV[2],
		scalar * rkV[3]);
}

inline Vector4& Vector4::operator+= (const Vector4& rkV)
{
	x += rkV.x;
	y += rkV.y;
	z += rkV.z;
	w += rkV.w;

	return *this;
}

inline Vector4& Vector4::operator+= (const Real scalar)
{
	x += scalar;
	y += scalar;
	z += scalar;
	w += scalar;

	return *this;
}

inline Vector4& Vector4::operator-= (const Vector4& rkV)
{
	x -= rkV.x;
	y -= rkV.y;
	z -= rkV.z;
	w -= rkV.w;

	return *this;
}

inline Vector4& Vector4::operator-= (const Real scalar)
{
	x -= scalar;
	y -= scalar;
	z -= scalar;
	w -= scalar;

	return *this;
}

inline Vector4& Vector4::operator*= (Real scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;

	return *this;
}

inline Vector4& Vector4::operator/= (Real scalar)
{
	if (scalar != (Real)0.0)
	{
		Real fInvScalar = ((Real)1.0)/scalar;
		x *= fInvScalar;
		y *= fInvScalar;
		z *= fInvScalar;
		w *= fInvScalar;
	}

	else
	{
		x = Math::MAX_REAL;
		y = Math::MAX_REAL;
		z = Math::MAX_REAL;
		w = Math::MAX_REAL;
	}

	return *this;
}

inline Real Vector4::length () const
{
	return Math::Sqrt(
		x * x +
		y * y +
		z * z + 
		w * w);
}

inline Real Vector4::sqrLength () const
{
	return
		x * x +
		y * y +
		z * z +
		w * w;
}

inline Real Vector4::dotProduct (const Vector4& rkV) const
{
	return
		x * rkV.x +
		y * rkV.y +
		z * rkV.z +
		w * rkV.w;
}

inline Real Vector4::normalize ()
{
	Real fLength = length();

	if (fLength > Math::ZERO_TOLERANCE)
	{
		Real fInvLength = ((Real)1.0)/fLength;
		x *= fInvLength;
		y *= fInvLength;
		z *= fInvLength;
		w *= fInvLength;
	}
	else
	{
		fLength = (Real)0.0;
		x = (Real)0.0;
		y = (Real)0.0;
		z = (Real)0.0;
		w = (Real)0.0;
	}

	return fLength;
}
