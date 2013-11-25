#include "Point3.h"

using namespace Good;

const Point3 Point3::ORIGIN(0.0f, 0.0f, 0.0f);

inline Point3::Point3(void): x(0), y(0), z(0)
{
}
inline Point3::Point3(Real px, Real py, Real pz):x(px), y(py), z(pz)
{
}

inline Point3::Point3(Real p[3]): x(p[0]), y(p[1]), z(p[2]) 
{
}

inline Point3& Point3::operator=(const Point3& rPoint) 
{
	x = rPoint.x;
	y = rPoint.y;
	z = rPoint.z;

	return *this;
}

//Deplacement d'un point
inline Point3 Point3::operator + (const Vector3& rVector) const
{
	return Point3(
		x + rVector.x,
		y + rVector.y,
		z + rVector.z);
}

inline Point3 Point3::operator - (const Vector3& rVector) const
{
	return Point3(
		x - rVector.x,
		y - rVector.y,
		z - rVector.z); 
}

//Deplacement via coeff proportionnel
inline Point3 Point3::operator * (const Real coeff) const
{
	return Point3(
		coeff * x,
		coeff * y,
		coeff * z);
}

inline Point3 Point3::operator / (const Real coeff) const
{
	Real newCoeff = 1/coeff;
	return this->Point3::operator*(newCoeff);
}

//Diff entre 2 points --> un vecteur
inline Vector3 Point3::operator - (const Point3& rPoint) const
{
	return Vector3(
		rPoint.x - x,
		rPoint.y - y,
		rPoint.z - z);
}

inline Real Point3::operator * (const Vector3& rVector) const 
{
	return (x * rVector.x + y * rVector.y + z * rVector.z);
}

inline bool Point3::operator == (const Point3& rPoint) const 
{
	return (x == rPoint.x && y == rPoint.y && z == rPoint.z);
}

inline bool Point3::operator != (const Point3& rPoint) const 
{
	return (x != rPoint.x || y != rPoint.y || z != rPoint.z);
}

