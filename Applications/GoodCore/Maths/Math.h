#pragma once

#include <cmath>
#include <random>

#include "../Core/GoodFoundationLib.h"

namespace Good
{
	typedef __int64 Integer64;

#ifdef _USEFLOAT
	typedef float Real;
#else
	typedef double Real;
#endif

	enum AXIS
	{
		X_AXIS,
		Y_AXIS,
		Z_AXIS
	};

	class Math
	{
	public:
		static Real ACos	(Real fValue);
		static Real ASin	(Real fValue);
		static Real ATan	(Real fValue);
		static Real ATan	(Real fY, Real fX);
		static Real Ceil	(Real fValue);	//Arrondi
		static Real Cos		(Real fValue);
		static Real Exp		(Real fValue);
		static Real FAbs	(Real fValue);
		static Real Floor	(Real fValue);	//Arrondi par le bas
		static Real FMod	(Real fX, Real fY);
		static Real InvSqrt	(Real fValue);
		static Real Log		(Real fValue);
		static Real Log2	(Real fValue);
		static Real Log10	(Real fValue);
		static Real Pow 	(Real fBase, Real fExponent);
		static Real Sin 	(Real fValue);
		static Real Square 	(Real fValue);
		static Real Sqrt	(Real fValue);
		static Real Tan 	(Real fValue);

		static int Sign (int iValue);
		static Real Sign (Real fValue);

		static Real UnitRandom(unsigned int uiSeed = 0);
		static Real SymRandom(unsigned int uiSeed = 0);
		static Real IntervalRandom(Real fMin, Real fMax, unsigned int uiSeed = 0);

		static Real FastSin	(Real fValue);
		static Real FastCos (Real fValue);
		static Real FastTan (Real fValue);

		static Real FastInvSin(Real fValue);
		static Real FastInvCos(Real fValue);
		static Real FastInvTan(Real fValue);

		static Real FastInvSqrt(Real fValue);

		static Real FastNegExp (Real fValue);

		static const Real EPSILON;
		static const Real ZERO_TOLERANCE;
		static const Real MAX_REAL;
		static const Real PI;
		static const Real TWO_PI;
		static const Real HALF_PI;
		static const Real INV_PI;
		static const Real INV_TWO_PI;
		static const Real DEG_TO_RAD;
		static const Real RAD_TO_DEG;
		static const Real LN_2;
		static const Real LN_10;
		static const Real INV_LN_2;
		static const Real INV_LN_10;
	};
}

