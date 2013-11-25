#pragma once
#include "Vector3.h"
#include "Math.h"

namespace Good
{
	struct GOOD_DLL Point3
	{
		Point3(void);
		Point3(Real px, Real py, Real pz);
		Point3(Real p[3]);

		Point3& operator=(const Point3& rPoint);
		//Deplacement d'un point
		Point3 operator + (const Vector3& rVector) const;
		Point3 operator - (const Vector3& rVector) const;
		//Deplacement via coeff proportionnel
		Point3 operator * (const Real coeff) const;
		Point3 operator / (const Real coeff) const;
		//Diff entre 2 points --> un vecteur
		Vector3 operator - (const Point3& rPoint) const;
		Real operator * (const Vector3& rVector) const;
		bool operator == (const Point3& rPoint) const;
		bool operator != (const Point3& rPoint) const;

		friend ::std::ostream& operator<<(std::ostream& out, const Point3& rPoint)
		{
			out << rPoint.x << "|" << rPoint.y << "|" << rPoint.z << std::endl;
		}

		std::string toString()
		{
			char buffer[MAX_CHAR];
			sprintf_s(buffer, "\n\t%.3lf | %.3lf | %.3lf", x, y, z);
			return std::string("\n") + typeid(*this).name() + std::string(buffer);
		}

		static const Point3 ORIGIN;

		Real x, y, z;
	};
}

