#pragma once
#include "Vector3.h"
#include "Math.h"

namespace Good
{
	class Point3
	{
	public:	
		inline Point3(void) {}
		inline Point3(Real px, Real py, Real pz):x(px), y(py), z(pz) {}
		inline Point3(Real p[3]): x(p[0]), y(p[1]), z(p[2]) {}

		inline Point3& operator=(const Point3& rPoint) 
		{
			x = rPoint.x;
			y = rPoint.y;
			z = rPoint.z;

			return *this;
		}

		//Deplacement d'un point
		inline Point3 operator + (const Vector3& rVector) const
		{
			return Point3(
				x + rVector.x,
				y + rVector.y,
				z + rVector.z);
		}

		inline Point3 operator - (const Vector3& rVector) const
		{
			return Point3(
				x - rVector.x,
				y - rVector.y,
				z - rVector.z); 
		}

		//Deplacement via coeff proportionnel
		inline Point3 operator * (const Real coeff) const
		{
			return Point3(
				coeff * x,
				coeff * y,
				coeff * z);
		}

		inline Point3 operator / (const Real coeff) const
		{
			Real newCoeff = 1/coeff;
			return this->operator*(newCoeff);
		}

		//Diff entre 2 points --> un vecteur
		inline Vector3 operator - (const Point3& rPoint) const
		{
			return Vector3(
				rPoint.x - x,
				rPoint.y - y,
				rPoint.z - z);
		}

		inline Real operator * (const Vector3& rVector) const 
		{
			return (x * rVector.x + y * rVector.y + z * rVector.z);
		}

		inline bool operator == (const Point3& rPoint) const 
		{
			return (x == rPoint.x && y == rPoint.y && z == rPoint.z);
		}

		inline bool operator != (const Point3& rPoint) const 
		{
			return (x != rPoint.x || y != rPoint.y || z != rPoint.z);
		}

		static const Point3 ORIGIN;

		Real x, y, z;
	};
}

