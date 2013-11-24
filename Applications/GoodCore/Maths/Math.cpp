#include "Math.h"

using namespace Good;

const Real Math::EPSILON = FLT_EPSILON;
const Real Math::ZERO_TOLERANCE = 1e-06f;
const Real Math::MAX_REAL = FLT_MAX;
const Real Math::PI = (Real)(4.0*atan(1.0));
const Real Math::TWO_PI = 2.0f*Math::PI;
const Real Math::HALF_PI = 0.5f*Math::PI;
const Real Math::INV_PI = 1.0f/Math::PI;
const Real Math::INV_TWO_PI = 1.0f/Math::TWO_PI;
const Real Math::DEG_TO_RAD = Math::PI/180.0f;
const Real Math::RAD_TO_DEG = 180.0f/Math::PI;
const Real Math::LN_2 = Math::Log(2.0f);
const Real Math::LN_10 = Math::Log(10.0f);
const Real Math::INV_LN_2 = 1.0f/Math::LN_2;
const Real Math::INV_LN_10 = 1.0f/Math::LN_10;

double Math::FastInvSqrt (Real dValue)
{
	double dHalf = 0.5*dValue;
	Integer64 i  = *(Integer64*)&dValue;

	i = 0x5fe6ec85e7de30daLL - (i >> 1);

	dValue = *(double*)&i;
	dValue = dValue*(1.5 - dHalf*dValue*dValue);
	return dValue;
}

//For float use
/*Real Math::FastInvSqrt (Real fValue)
{
Real fHalf = 0.5f*fValue;
int i  = *(int*)&fValue;
i = 0x5f3759df - (i >> 1);
fValue = *(Real*)&i;
fValue = fValue*(1.5f - fHalf*fValue*fValue);
return fValue;
}*/

Real Math::ACos (Real fValue)
{
	if (-(Real)1.0 < fValue)
	{
		if (fValue < (Real)1.0)
		{
			return (Real)acos((double)fValue);
		}
		else
		{
			return (Real)0.0;
		}
	}
	else
	{
		return PI;
	}
}

Real Math::ASin (Real fValue)
{
	if (-(Real)1.0 < fValue)
	{
		if (fValue < (Real)1.0)
		{
			return (Real)asin((double)fValue);
		}
		else
		{
			return HALF_PI;
		}
	}
	else
	{
		return -HALF_PI;
	}
}

Real Math::ATan (Real fValue)
{
	return (Real)atan((double)fValue);
}

Real Math::ATan (Real fY, Real fX)
{
	return (Real)atan2((double)fY,(double)fX);
}

Real Math::Ceil (Real fValue)
{
	return (Real)ceil((double)fValue);
}

Real Math::Cos (Real fValue)
{
	return (Real)cos((double)fValue);
}

Real Math::Exp (Real fValue)
{
	return (Real)exp((double)fValue);
}

Real Math::FAbs (Real fValue)
{
	return (Real)fabs((double)fValue);
}

Real Math::Floor (Real fValue)
{
	return (Real)floor((double)fValue);
}


Real Math::FMod (Real fX, Real fY)
{
	return (Real)fmod((double)fX,(double)fY);
}

Real Math::InvSqrt (Real fValue)
{
	return (Real)(1.0/sqrt((double)fValue));
}

Real Math::Log (Real fValue)
{
	return (Real)log((double)fValue);
}

Real Math::Log2 (Real fValue)
{
	return Math::INV_LN_2 * (Real)log((double)fValue);
}

Real Math::Log10 (Real fValue)
{
	return Math::INV_LN_10 * (Real)log((double)fValue);
}

Real Math::Pow (Real fBase, Real fExponent)
{
	return (Real)pow((double)fBase,(double)fExponent);
}

Real Math::Sin (Real fValue)
{
	return (Real)sin((double)fValue);
}

Real Math::Square (Real fValue)
{
	return fValue*fValue;
}

Real Math::Sqrt (Real fValue)
{
	return (Real)sqrt((double)fValue);
}

Real Math::Tan (Real fValue)
{
	return (Real)tan((double)fValue);
}

int Math::Sign (int iValue)
{
	if (iValue > 0)
	{
		return 1;
	}

	if (iValue < 0)
	{
		return -1;
	}

	return 0;
}

Real Math::Sign (Real fValue)
{
	if (fValue > (Real)0.0)
	{
		return (Real)1.0;
	}

	if (fValue < (Real)0.0)
	{
		return -(Real)1.0;
	}

	return (Real)0.0;
}

Real Math::UnitRandom (unsigned int uiSeed)
{
	if (uiSeed > 0)
	{
		srand(uiSeed);
	}

	double dRatio = ((double)rand())/((double)(RAND_MAX));
	return (Real)dRatio;
}

Real Math::SymRandom (unsigned int uiSeed)
{
	if (uiSeed > 0.0)
	{
		srand(uiSeed);
	}

	double dRatio = ((double)rand())/((double)(RAND_MAX));
	return (Real)(2.0*dRatio - 1.0);
}

Real Math::IntervalRandom (Real fMin, Real fMax, unsigned int uiSeed)
{
	if (uiSeed > 0)
	{
		srand(uiSeed);
	}

	double dRatio = ((double)rand())/((double)(RAND_MAX));
	return fMin+(fMax-fMin)*((Real)dRatio);
}

Real Math::FastSin (Real fAngle)
{
	Real fASqr = fAngle*fAngle;
	Real fResult = -(Real)2.39e-08;
	fResult *= fASqr;
	fResult += (Real)2.7526e-06;
	fResult *= fASqr;
	fResult -= (Real)1.98409e-04;
	fResult *= fASqr;
	fResult += (Real)8.3333315e-03;
	fResult *= fASqr;
	fResult -= (Real)1.666666664e-01;
	fResult *= fASqr;
	fResult += (Real)1.0;
	fResult *= fAngle;
	return fResult;
}

Real Math::FastCos (Real fAngle)
{
	Real fASqr = fAngle*fAngle;
	Real fResult = -(Real)2.605e-07;
	fResult *= fASqr;
	fResult += (Real)2.47609e-05;
	fResult *= fASqr;
	fResult -= (Real)1.3888397e-03;
	fResult *= fASqr;
	fResult += (Real)4.16666418e-02;
	fResult *= fASqr;
	fResult -= (Real)4.999999963e-01;
	fResult *= fASqr;
	fResult += (Real)1.0;
	return fResult;
}

Real Math::FastTan (Real fAngle)
{
	Real fASqr = fAngle*fAngle;
	Real fResult = (Real)9.5168091e-03;
	fResult *= fASqr;
	fResult += (Real)2.900525e-03;
	fResult *= fASqr;
	fResult += (Real)2.45650893e-02;
	fResult *= fASqr;
	fResult += (Real)5.33740603e-02;
	fResult *= fASqr;
	fResult += (Real)1.333923995e-01;
	fResult *= fASqr;
	fResult += (Real)3.333314036e-01;
	fResult *= fASqr;
	fResult += (Real)1.0;
	fResult *= fAngle;
	return fResult;
}

Real Math::FastInvSin (Real fValue)
{
	Real fRoot = Math::Sqrt(FAbs(((Real)1.0)-fValue));
	Real fResult = -(Real)0.0012624911;
	fResult *= fValue;
	fResult += (Real)0.0066700901;
	fResult *= fValue;
	fResult -= (Real)0.0170881256;
	fResult *= fValue;
	fResult += (Real)0.0308918810;
	fResult *= fValue;
	fResult -= (Real)0.0501743046;
	fResult *= fValue;
	fResult += (Real)0.0889789874;
	fResult *= fValue;
	fResult -= (Real)0.2145988016;
	fResult *= fValue;
	fResult += (Real)1.5707963050;
	fResult = HALF_PI - fRoot*fResult;
	return fResult;
}

Real Math::FastInvCos (Real fValue)
{
	Real fRoot = Math::Sqrt(FAbs(((Real)1.0)-fValue));
	Real fResult = -(Real)0.0012624911;
	fResult *= fValue;
	fResult += (Real)0.0066700901;
	fResult *= fValue;
	fResult -= (Real)0.0170881256;
	fResult *= fValue;
	fResult += (Real)0.0308918810;
	fResult *= fValue;
	fResult -= (Real)0.0501743046;
	fResult *= fValue;
	fResult += (Real)0.0889789874;
	fResult *= fValue;
	fResult -= (Real)0.2145988016;
	fResult *= fValue;
	fResult += (Real)1.5707963050;
	fResult *= fRoot;
	return fResult;
}

Real Math::FastInvTan (Real fValue)
{
	Real fVSqr = fValue*fValue;
	Real fResult = (Real)0.0028662257;
	fResult *= fVSqr;
	fResult -= (Real)0.0161657367;
	fResult *= fVSqr;
	fResult += (Real)0.0429096138;
	fResult *= fVSqr;
	fResult -= (Real)0.0752896400;
	fResult *= fVSqr;
	fResult += (Real)0.1065626393;
	fResult *= fVSqr;
	fResult -= (Real)0.1420889944;
	fResult *= fVSqr;
	fResult += (Real)0.1999355085;
	fResult *= fVSqr;
	fResult -= (Real)0.3333314528;
	fResult *= fVSqr;
	fResult += (Real)1.0;
	fResult *= fValue;
	return fResult;
}

Real Math::FastNegExp (Real fValue)
{
	Real fResult = (Real)0.0000006906;
	fResult *= fValue;
	fResult += (Real)0.0000054302;
	fResult *= fValue;
	fResult += (Real)0.0001715620;
	fResult *= fValue;
	fResult += (Real)0.0025913712;
	fResult *= fValue;
	fResult += (Real)0.0312575832;
	fResult *= fValue;
	fResult += (Real)0.2499986842;
	fResult *= fValue;
	fResult += (Real)1.0;
	fResult *= fResult;
	fResult *= fResult;
	fResult = ((Real)1.0)/fResult;
	return fResult;
}
