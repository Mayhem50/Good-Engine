#include "Vector2.h"

using namespace Good;

const Vector2 Vector2::ZERO( 0, 0 );
const Vector2 Vector2::UNIT_X( 1, 0 );
const Vector2 Vector2::UNIT_Y( 0, 1 );

Vector2::Vector2():
	x(0), y(0)
{
}

Vector2::Vector2(const Real fX, const Real fY):
	x(fX), y(fY)
{
}

Vector2::Vector2(const Real scaler):
	x(scaler), y(scaler)
{
}

Vector2::Vector2(const Real coord[2]):
	x(coord[0]), y(coord[1])
{
}

Real Vector2::operator [] (const size_t idx) const
{
	assert( idx < 2);

	return *(&x+idx);
}

Real& Vector2::operator [] (const size_t idx)
{
	assert( idx < 2);

	return *(&x+idx);
}

Vector2& Vector2::operator = (const Vector2& rkV)
{
	x = rkV.x;
	y = rkV.y;

	return *this;
}

Vector2& Vector2::operator = (const Real rkV)
{
	x = rkV;
	y = rkV;

	return *this;
}

bool Vector2::operator == (const Vector2& rkV) const 
{
	return (x == rkV.x && y == rkV.y);
}

bool Vector2::operator != (const Vector2& rkV) const 
{
	return (x != rkV.x || y != rkV.y);
}

Vector2 Vector2::operator + (const Vector2& rkV) const 
{
	return Vector2(
		x + rkV.x,
		y + rkV.y);
}
Vector2 Vector2::operator - (const Vector2& rkV) const 
{
	return Vector2(
		x - rkV.x,
		y - rkV.y);
}
Vector2 Vector2::operator - () const 
{
	return Vector2(
		-x
		-y);
}

Vector2 Vector2::operator * (const Vector2& rkV) const 
{
	return Vector2(
		x * rkV.x,
		y * rkV.y); 
}
Vector2 Vector2::operator * (const Real scalar) const 
{
	return Vector2(
		x * scalar,
		y * scalar);
}
Vector2 Vector2::operator / (const Vector2& rkV) const 
{
	return Vector2(
		x / rkV.x,
		y / rkV.y);
}

Vector2 Vector2::operator / (const Real scalar) const 
{
	return Vector2(
		x / scalar,
		y / scalar);
}

Vector2& Vector2::operator += (const Vector2& rkV)
{
	x += rkV.x;
	y += rkV.y;

	return *this;
}	

Vector2& Vector2::operator += (const Real scalar)
{
	x += scalar;
	y += scalar;

	return *this;
}

Vector2& Vector2::operator -= (const Vector2& rkV)
{
	x -= rkV.x;
	y -= rkV.y;

	return *this;
}

Vector2& Vector2::operator -= (const Real scalar)
{
	x -= scalar;
	y -= scalar;

	return *this;
}

Vector2& Vector2::operator *= (const Vector2& rkV)
{
	x *= rkV.x;
	y *= rkV.y;

	return *this;
}

Vector2& Vector2::operator *= (const Real scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

Vector2& Vector2::operator /= (const Vector2& rkV)
{
	x /= rkV.x;
	y /= rkV.y;

	return *this;
}

Vector2& Vector2::operator /= (const Real scalar)
{
	x /= scalar;
	y /= scalar;

	return *this;
}

Real Vector2::lenght() const
{
	return Math::Sqrt(x * x + y *y);
}

Real Vector2::sqrLenght() const
{
	return (x * x + y *y);
}

Real Vector2::module() const
{
	return lenght();
}

Real Vector2::distance(const Vector2& rkV) const 
{
	return (*this - rkV).lenght();
}

Real Vector2::sqrDistance(const Vector2& rkV) const 
{
	return (*this - rkV).sqrLenght();
}

Real Vector2::dotProduct(const Vector2& rkV) const 
{
	return x * rkV.x + y * rkV.y;
}

Real Vector2::normalise() 
{
	Real fLength = lenght();

	if ( fLength > Real(0.0f) )
	{
		Real fInvLength = 1.0f / fLength;
		x *= fInvLength;
		y *= fInvLength;
	}

	return fLength;
}

Vector2 Vector2::distanceBetween(const Vector2& rkV) const 
{
	return Vector2(
		(x + rkV.x) * (Real)0.5,
		(y + rkV.y) * (Real)0.5
		);
}

Vector2 Vector2::midpoint() const 
{
	return Vector2(
		x * (Real)0.5,
		y * (Real)0.5);
}

Real Vector2::crosProduct(const Vector2& rkV) const
{
	return (x * rkV.y + y * rkV.x);
}

Vector2 Vector2::perpendicular()
{
	return Vector2(
		-y,
		x);
}
