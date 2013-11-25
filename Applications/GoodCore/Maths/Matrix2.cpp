#include "Matrix2.h"

using namespace Good;

const Matrix2 Matrix2::ZERO(0.0, 0.0, 
														0.0, 0.0);
const Matrix2 Matrix2::IDENTITY(1.0, 0.0, 
																0.0, 1.0);

inline Matrix2::Matrix2(void)
{
	makeZero();
}

inline Matrix2::Matrix2(const Matrix2& rMatrix)
{
	matrix[0][0] = rMatrix[0][0];	matrix[0][1] = rMatrix[0][1];
	matrix[1][0] = rMatrix[1][0];	matrix[1][1] = rMatrix[1][1];
}

inline Matrix2::Matrix2(Real f00, Real f01, Real f10, Real f11)
{
	matrix[0][0] = f00;	matrix[0][1] = f01;
	matrix[1][0] = f10;	matrix[1][1] = f11;
}

inline Matrix2::Matrix2(const Real rEntry[4], bool bRowMajor)
{
	if(bRowMajor)
	{
		matrix[0][0] = rEntry[0];	matrix[0][1] = rEntry[1];
		matrix[1][0] = rEntry[2];	matrix[1][1] = rEntry[3];
	}

	else
	{
		matrix[0][0] = rEntry[0];	matrix[0][1] = rEntry[2];
		matrix[1][0] = rEntry[1];	matrix[1][1] = rEntry[3];
	}
}

inline Matrix2::Matrix2(const Vector2& rkU, const Vector2& rkV, bool bColumns)
{
	if(bColumns)
	{
		matrix[0][0] = rkU.x;	matrix[0][1] = rkV.x;
		matrix[1][0] = rkU.y;	matrix[1][1] = rkV.y;
	}

	else
	{
		matrix[0][0] = rkU.x;	matrix[0][1] = rkU.y;
		matrix[1][0] = rkV.x;	matrix[1][1] = rkV.y;
	}
}

inline Matrix2::Matrix2(const Vector2* akV, bool bColumns)
{
	if(bColumns)
	{
		matrix[0][0] = akV[0].x;  matrix[0][1] = akV[1].x;
		matrix[1][0] = akV[0].y;  matrix[1][1] = akV[1].y;
	}

	else
	{
		matrix[0][0] = akV[0].x;	matrix[0][1] = akV[0].y;
		matrix[1][0] = akV[0].x;	matrix[1][1] = akV[0].y;
	}
}

inline Matrix2::Matrix2(Real f00, Real f11)
{
	makeDiagonal(f00, f11);
}

inline Matrix2::Matrix2(Real fAngle)
{
	fromAngle(fAngle);
}

inline void Matrix2::makeZero()
{
	matrix[0][0] = 0.0;	matrix[0][1] = 0.0;
	matrix[1][0] = 0.0;	matrix[1][1] = 0.0;
}

inline void Matrix2::makeIdentity()
{
	matrix[0][0] = 1.0;	matrix[0][1] = 0.0;
	matrix[1][0] = 0.0;	matrix[1][1] = 1.0;
}

inline void Matrix2::makeDiagonal(Real f00, Real f11)
{
	matrix[0][0] = f00;	matrix[0][1] = 0.0;
	matrix[1][0] = 0.0;	matrix[1][1] = f11;
}

inline void Matrix2::fromAngle(Real fAngle)
{
	matrix[0][0] = Math::Cos(fAngle);	
	matrix[1][0] = Math::Sin(fAngle);
	matrix[0][1] = -matrix[1][0];
	matrix[1][1] = -matrix[0][0];
}

inline void Matrix2::makeTensorProduct(const Vector2& rkU, const Vector2& rkV)
{
	matrix[0][0] = rkU.x * rkV.x;	matrix[0][1] = rkU.x * rkV.y;
	matrix[1][0] = rkU.y * rkV.x;	matrix[1][1] = rkU.y * rkV.y;
}

inline const Real* Matrix2::operator[] (int iRow) const
{
	assert(iRow < 2);
	return matrix[iRow];
}

inline Real* Matrix2::operator[] (int iRow)
{
	assert(iRow < 2);
	return matrix[iRow];
}

inline Real Matrix2::operator() (int iRow, int iColumn) const
{
	assert(iRow < 2);
	assert(iColumn < 2);
	return matrix[iRow][iColumn];
}

inline void Matrix2::setRow(int iRow, const Vector2& rkV)
{
	assert(iRow < 2);
	matrix[iRow][0] = rkV.x;
	matrix[iRow][1] = rkV.y;
}

inline Vector2 Matrix2::getRow(int iRow) const
{
	assert(iRow < 2);
	return Vector2(matrix[iRow][0], matrix[iRow][1]);
}	

inline void Matrix2::setColumn(int iColumn, const Vector2& rkV)
{
	assert(iColumn < 2);
	matrix[0][iColumn] = rkV.x;
	matrix[1][iColumn] = rkV.y;
}

inline Vector2 Matrix2::getColumn(int iColumn) const
{
	assert(iColumn < 2);
	return Vector2(matrix[0][iColumn], matrix[1][iColumn]);
}

inline Matrix2& Matrix2::operator= (const Matrix2& rMatrix)
{
	matrix[0][0] = rMatrix[0][0];	matrix[0][1] = rMatrix[0][1];
	matrix[1][0] = rMatrix[1][0];	matrix[1][1] = rMatrix[1][1];

	return *this;
}

inline bool Matrix2::operator== (const Matrix2& rMatrix) const
{
	return (
		matrix[0][0] == rMatrix[0][0] &&	matrix[0][1] == rMatrix[0][1] &&
		matrix[1][0] == rMatrix[1][0] &&	matrix[1][1] == rMatrix[1][1]);
}

inline bool Matrix2::operator!= (const Matrix2& rMatrix) const
{
	return (
		matrix[0][0] != rMatrix[0][0] ||	matrix[0][1] != rMatrix[0][1] ||
		matrix[1][0] != rMatrix[1][0] ||	matrix[1][1] != rMatrix[1][1]);
}

inline Matrix2 Matrix2::operator+ (const Matrix2& rMatrix) const
{
	return Matrix2(
		matrix[0][0] + rMatrix[0][0],	matrix[0][1] + rMatrix[0][1],
		matrix[1][0] + rMatrix[1][0],	matrix[1][1] + rMatrix[1][1]
	);
}

inline Matrix2 Matrix2::operator- (const Matrix2& rMatrix) const
{
	return Matrix2(
		matrix[0][0] - rMatrix[0][0],	matrix[0][1] - rMatrix[0][1],
		matrix[1][0] - rMatrix[1][0],	matrix[1][1] - rMatrix[1][1]
	);
}

inline Matrix2 Matrix2::operator* (const Matrix2& rMatrix) const
{
	return Matrix2(
		matrix[0][0] * rMatrix[0][0] + matrix[0][1] * rMatrix[1][0],
		matrix[0][0] * rMatrix[0][1] + matrix[0][1] * rMatrix[1][1],
		matrix[1][0] * rMatrix[0][0] + matrix[1][1] * rMatrix[1][0],
		matrix[1][0] * rMatrix[0][1] + matrix[1][1] * rMatrix[1][1]
	);
}

inline Matrix2 Matrix2::operator* (Real scalar) const
{
	return Matrix2(
		matrix[0][0] * scalar,	matrix[0][1] * scalar,
		matrix[1][0] * scalar,	matrix[1][1] * scalar
		);
}

inline Matrix2 Matrix2::operator/ (Real scalar) const
{
	Real invScalar = 1/scalar;

	return Matrix2(
		matrix[0][0] * invScalar,	matrix[0][1] * invScalar,
		matrix[1][0] * invScalar,	matrix[1][1] * invScalar
		);
}

inline Matrix2 Matrix2::operator- () const
{
	return Matrix2(
		-matrix[0][0],	-matrix[0][1],
		-matrix[1][0],	-matrix[1][1]
	);
}

inline Matrix2& Matrix2::operator+= (const Matrix2& rMatrix)
{
	matrix[0][0] += rMatrix[0][0];	matrix[0][1] += rMatrix[0][1];
	matrix[1][0] += rMatrix[1][0];	matrix[1][1] += rMatrix[1][1];

	return *this;
}

inline Matrix2& Matrix2::operator-= (const Matrix2& rMatrix)
{
	matrix[0][0] -= rMatrix[0][0];	matrix[0][1] -= rMatrix[0][1];
	matrix[1][0] -= rMatrix[1][0];	matrix[1][1] -= rMatrix[1][1];

	return *this;
}

inline Matrix2& Matrix2::operator*= (const Real scalar)
{
	matrix[0][0] *= scalar;	matrix[0][1] *= scalar;
	matrix[1][0] *= scalar;	matrix[1][1] *= scalar;

	return *this;
}

inline Matrix2& Matrix2::operator/= (const Real scalar)
{
	matrix[0][0] /= scalar;	matrix[0][1] /= scalar;
	matrix[1][0] /= scalar;	matrix[1][1] /= scalar;

	return *this;
}

inline Vector2 Matrix2::operator* (const Vector2& rkV) const
{
	return Vector2(
		matrix[0][0]*rkV.x + matrix[0][1]*rkV.y,
		matrix[1][0]*rkV.x + matrix[1][1]*rkV.y);
}

inline Matrix2 Matrix2::transpose() const
{
	return Matrix2(
		matrix[0][0], matrix[1][0],
		matrix[0][1], matrix[1][1]);
}

inline Matrix2 Matrix2::transposeTimes(const Matrix2& rMatrix) const
{
	return Matrix2(
		matrix[0][0]*rMatrix.matrix[0][0] + matrix[1][0]*rMatrix.matrix[1][0],
		matrix[0][0]*rMatrix.matrix[0][1] + matrix[1][0]*rMatrix.matrix[1][1],
		matrix[0][1]*rMatrix.matrix[0][0] + matrix[1][1]*rMatrix.matrix[1][0],
		matrix[0][1]*rMatrix.matrix[0][1] + matrix[1][1]*rMatrix.matrix[1][1]);
}

inline Matrix2 Matrix2::timeTranspose(const Matrix2& rMatrix) const
{
	return Matrix2(
		matrix[0][0]*rMatrix.matrix[0][0] + matrix[0][1]*rMatrix.matrix[0][1],
		matrix[0][0]*rMatrix.matrix[1][0] + matrix[0][1]*rMatrix.matrix[1][1],
		matrix[1][0]*rMatrix.matrix[0][0] + matrix[1][1]*rMatrix.matrix[0][1],
		matrix[1][0]*rMatrix.matrix[1][0] + matrix[1][1]*rMatrix.matrix[1][1]);
}

inline Matrix2 Matrix2::inverse() const
{
	Matrix2 inverse;

	Real determinant = this->determinant();

	if(Math::FAbs(determinant) > Math::ZERO_TOLERANCE)
	{
		inverse[0][0] = matrix[1][0] / determinant;
		inverse[0][1] = -matrix[0][1] / determinant;
		inverse[1][0] = -matrix[1][0] / determinant;
		inverse[1][1] = matrix[0][0] / determinant;
	}

	return inverse;
}

inline Matrix2 Matrix2::adjoint() const
{
	return Matrix2(
		matrix[1][1],
		-matrix[0][1],
		-matrix[1][0],
		matrix[0][0]);
}

inline Real Matrix2::determinant() const
{
	return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

inline Real Matrix2::qForm(const Vector2& rkU, const Vector2& rkV) const
{
	return rkU.dotProduct((*this) * rkV);
}

inline void Matrix2::toAngle(Real& fAngle) const
{
	fAngle = Math::ATan(matrix[1][0], matrix[0][0]);
}

void Matrix2::orthoNormalize()
{
	Real invLenght = Math::InvSqrt(matrix[0][0] * matrix[0][0] + matrix[1][0] * matrix[1][0]);

	matrix[0][0] *= invLenght;
	matrix[1][0] *= invLenght;

	Real dot0 = (matrix[0][0] * matrix[0][1] + matrix[1][0] * matrix[1][1]);

	matrix[0][1] -= dot0 * matrix[0][0];
	matrix[1][1] -= dot0 * matrix[1][0];

	invLenght = Math::InvSqrt(matrix[0][1] * matrix[0][1] + matrix[1][1] * matrix[1][1]);

	matrix[0][1] *= invLenght;
	matrix[1][1] *= invLenght;
}

