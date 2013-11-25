#include "Matrix3.h"

using namespace Good;

const Matrix3 Matrix3::ZERO(0.0, 0.0, 0.0,
														0.0, 0.0, 0.0,
														0.0, 0.0, 0.0);
const Matrix3 Matrix3::IDENTITY(1.0, 0.0, 0.0,
																0.0, 1.0, 0.0,
																0.0, 0.0, 1.0);

inline Matrix3::Matrix3(void)
{
	makeZero();
}

inline Matrix3::Matrix3(const Matrix3& rMatrix)
{
	matrix[0][0] = rMatrix.matrix[0][0];	matrix[0][1] = rMatrix.matrix[0][1];	matrix[0][2] = rMatrix.matrix[0][2];
	matrix[1][0] = rMatrix.matrix[1][0];	matrix[1][1] = rMatrix.matrix[1][1];	matrix[1][2] = rMatrix.matrix[1][2];
	matrix[2][0] = rMatrix.matrix[2][0];	matrix[2][1] = rMatrix.matrix[2][1];	matrix[2][2] = rMatrix.matrix[2][2];
}

inline Matrix3::Matrix3(
	Real f00, Real f01, Real f02, 
	Real f10, Real f11, Real f12,
	Real f20, Real f21, Real f22)
{
	matrix[0][0] = f00;	matrix[0][1] = f01;	matrix[0][2] = f02;
	matrix[1][0] = f10;	matrix[1][1] = f11;	matrix[1][2] = f12;
	matrix[2][0] = f20;	matrix[2][1] = f21;	matrix[2][2] = f22;
}

inline Matrix3::Matrix3(const Real rEntry[9], bool bRowMajor)
{
	if(bRowMajor)
	{
		matrix[0][0] = rEntry[0];	matrix[0][1] = rEntry[1];	matrix[0][2] = rEntry[2];
		matrix[1][0] = rEntry[3];	matrix[1][1] = rEntry[4];	matrix[1][2] = rEntry[5];
		matrix[2][0] = rEntry[6];	matrix[2][1] = rEntry[7];	matrix[2][2] = rEntry[8];
	}
	else
	{
		matrix[0][0] = rEntry[0];	matrix[0][1] = rEntry[3];	matrix[0][2] = rEntry[6];
		matrix[1][0] = rEntry[1];	matrix[1][1] = rEntry[4];	matrix[1][2] = rEntry[7];
		matrix[2][0] = rEntry[2];	matrix[2][1] = rEntry[5];	matrix[2][2] = rEntry[8];
	}
}

inline Matrix3::Matrix3(const Vector3& rkU, const Vector3& rkV, const Vector3& rkW, bool bColumns)
{
	if(bColumns)
	{
		matrix[0][0] = rkU.x;	matrix[0][1] = rkV.x;	matrix[0][2] = rkW.x;
		matrix[1][0] = rkU.y;	matrix[1][1] = rkV.y;	matrix[1][2] = rkW.y;
		matrix[2][0] = rkU.z;	matrix[2][1] = rkV.z;	matrix[2][2] = rkW.z;
	}
	else
	{
		matrix[0][0] = rkU.x;	matrix[0][1] = rkU.y;	matrix[0][2] = rkU.z;
		matrix[1][0] = rkV.x;	matrix[1][1] = rkV.y;	matrix[1][2] = rkV.z;
		matrix[2][0] = rkW.x;	matrix[2][1] = rkW.y;	matrix[2][2] = rkW.z;
	}
}

inline Matrix3::Matrix3(const Vector3* akV, bool bColumns)
{
	if(bColumns)
	{
		matrix[0][0] = akV[0].x;	matrix[0][1] = akV[1].x;	matrix[0][2] = akV[2].x;
		matrix[1][0] = akV[0].y;	matrix[1][1] = akV[1].y;	matrix[1][2] = akV[2].y;
		matrix[2][0] = akV[0].z;	matrix[2][1] = akV[1].z;	matrix[2][2] = akV[2].z;
	}
	else
	{
		matrix[0][0] = akV[0].x;	matrix[0][1] = akV[0].y;	matrix[0][2] = akV[0].z;
		matrix[1][0] = akV[1].x;	matrix[1][1] = akV[1].y;	matrix[1][2] = akV[1].z;
		matrix[2][0] = akV[2].x;	matrix[2][1] = akV[2].y;	matrix[2][2] = akV[2].z;
	}
}

inline Matrix3::Matrix3(Real f00, Real f11, Real f22)
{
	makeDiagonal(f00, f11, f22);
}

inline Matrix3::Matrix3(Real fAngle, AXIS axe)
{
	if(axe == AXIS::X_AXIS)
		fromAngleOnX(fAngle);
	else if(axe == AXIS::Y_AXIS)
		fromAngleOnY(fAngle);
	else if(axe == AXIS::Z_AXIS)
		fromAngleOnZ(fAngle);
}

inline Matrix3::Matrix3(const Matrix2& rMatrix)
{
	matrix[0][0] = rMatrix.matrix[0][0];	matrix[0][1] = rMatrix.matrix[0][1];	matrix[0][2] = 0.0;
	matrix[1][0] = rMatrix.matrix[1][0];	matrix[1][1] = rMatrix.matrix[1][1];	matrix[1][2] = 0.0;
	matrix[2][0] = 0.0;										matrix[2][1] = 0.0;										matrix[2][2] = 1.0;
}

void Matrix3::makeZero()
{
	matrix[0][0] = 0.0;	matrix[0][1] = 0.0;	matrix[0][2] = 0.0;
	matrix[1][0] = 0.0;	matrix[1][1] = 0.0;	matrix[1][2] = 0.0;
	matrix[2][0] = 0.0;	matrix[2][1] = 0.0;	matrix[2][2] = 0.0;
}

void Matrix3::makeIdentity()
{
	matrix[0][0] = 1.0;	matrix[0][1] = 0.0;	matrix[0][2] = 0.0;
	matrix[1][0] = 0.0;	matrix[1][1] = 1.0;	matrix[1][2] = 0.0;
	matrix[2][0] = 0.0;	matrix[2][1] = 0.0;	matrix[2][2] = 1.0;
}

void Matrix3::makeDiagonal(Real f00, Real f11, Real f22)
{
	matrix[0][0] = f00;	matrix[0][1] = 0.0;	matrix[0][2] = 0.0;
	matrix[1][0] = 0.0;	matrix[1][1] = f11;	matrix[1][2] = 0.0;
	matrix[2][0] = 0.0;	matrix[2][1] = 0.0;	matrix[2][2] = f22;
}

void Matrix3::fromAngleOnX(Real fAngle)
{
	matrix[0][0] = 1.0;	matrix[0][1] = 0.0;								matrix[0][2] = 0.0;
	matrix[1][0] = 0.0;	matrix[1][1] = Math::Cos(fAngle);	
	matrix[2][0] = 0.0;	matrix[2][1] = Math::Sin(fAngle); matrix[2][2] = matrix[1][1];

	matrix[1][2] = -matrix[2][1];
}

void Matrix3::fromAngleOnY(Real fAngle)
{
	matrix[0][0] = Math::Cos(fAngle);	matrix[0][1] = 0.0;						matrix[0][2] = Math::Sin(fAngle);
	matrix[1][0] = 0.0;								matrix[1][1] = 1.0;						matrix[1][2] = 0.0;
	matrix[2][0] = -matrix[0][2];			matrix[2][2] = matrix[1][1];	matrix[2][1] = matrix[0][0];
}

void Matrix3::fromAngleOnZ(Real fAngle)
{
	matrix[0][0] =  Math::Cos(fAngle);																matrix[0][2] = 0.0;
	matrix[1][0] =  Math::Sin(fAngle);	matrix[1][1] = matrix[0][0];	matrix[1][2] = 0.0;
	matrix[2][0] = 0.0;									matrix[2][1] = 0.0;						matrix[2][2] = 1.0;

	matrix[0][1] = -matrix[1][0];			
}

void Matrix3::makeTensorProduct(const Vector3& rkU, const Vector3& rkV)
{
	matrix[0][0] = rkU.x * rkV.x;	matrix[0][1] = rkU.x * rkV.y; matrix[0][2] = rkU.x * rkV.z;
	matrix[1][0] = rkU.y * rkV.x;	matrix[1][1] = rkU.y * rkV.y; matrix[1][2] = rkU.y * rkV.z;
	matrix[2][0] = rkU.z * rkV.x;	matrix[2][1] = rkU.z * rkV.y; matrix[2][2] = rkU.z * rkV.z;
}

inline const Real* Matrix3::operator[] (int iRow) const
{
	assert(iRow < 3);
	return matrix[iRow];
}

inline Real* Matrix3::operator[] (int iRow)
{
	assert(iRow < 3);
	return matrix[iRow];
}

inline Real& Matrix3::operator() (int iRow, int iColumn)
{
	assert(iRow < 3);
	assert(iColumn < 3);
	return matrix[iRow][iColumn];
}

inline Real Matrix3::operator() (int iRow, int iColumn) const
{
	assert(iRow < 3);
	assert(iColumn < 3);
	return matrix[iRow][iColumn];
}

void Matrix3::setRow(int iRow, const Vector3& rkV)
{
	assert(iRow < 3);
	matrix[iRow][0] = rkV.x; matrix[iRow][1] = rkV.y;	matrix[iRow][2] = rkV.z;
}

inline Vector3 Matrix3::getRow(int iRow) const
{
	assert(iRow < 3);
	return Vector3(matrix[iRow][0], matrix[iRow][1], matrix[iRow][2]);
}	

void Matrix3::setColumn(int iColumn, const Vector3& rkV)
{
	assert(iColumn < 3);
	matrix[0][iColumn] = rkV.x;
	matrix[1][iColumn] = rkV.y;
	matrix[2][iColumn] = rkV.z;
}

inline Vector3 Matrix3::getColumn(int iColumn) const
{
	assert(iColumn < 3);
	return Vector3(matrix[0][iColumn], matrix[1][iColumn], matrix[2][iColumn]);
}

inline Matrix3& Matrix3::operator= (const Matrix3& rMatrix)
{
	matrix[0][0] = rMatrix[0][0];	matrix[0][1] = rMatrix[0][1]; matrix[0][2] = rMatrix[0][2];
	matrix[1][0] = rMatrix[1][0];	matrix[1][1] = rMatrix[1][1]; matrix[1][2] = rMatrix[1][2];
	matrix[2][0] = rMatrix[2][0];	matrix[2][1] = rMatrix[2][1]; matrix[2][2] = rMatrix[2][2];

	return *this;
}

inline Matrix3& Matrix3::operator= (const Matrix2& rMatrix)
{
	matrix[0][0] = rMatrix[0][0];	matrix[0][1] = rMatrix[0][1]; matrix[0][2] = rMatrix[0][2];
	matrix[1][0] = rMatrix[1][0];	matrix[1][1] = rMatrix[1][1]; matrix[1][2] = rMatrix[1][2];
	matrix[2][0] = 0.0;						matrix[2][1] = 0.0;						matrix[2][2] = 1.0;

	return *this;
}

inline bool Matrix3::operator== (const Matrix3& rMatrix) const
{
	return (
		matrix[0][0] == rMatrix[0][0] &&	matrix[0][1] == rMatrix[0][1] && matrix[0][2] == rMatrix[0][2] &&
		matrix[1][0] == rMatrix[1][0] &&	matrix[1][1] == rMatrix[1][1] && matrix[1][2] == rMatrix[1][2] &&
		matrix[2][0] == rMatrix[2][0] &&	matrix[2][1] == rMatrix[2][1] && matrix[2][2] == rMatrix[2][2]
	);
}

inline bool Matrix3::operator!= (const Matrix3& rMatrix) const
{
	return (*this == rMatrix);
}

inline Matrix3 Matrix3::operator+ (const Matrix3& rMatrix) const
{
	return Matrix3(
		matrix[0][0] + rMatrix[0][0],	matrix[0][1] + rMatrix[0][1], matrix[0][2] + rMatrix[0][2],
		matrix[1][0] + rMatrix[1][0],	matrix[1][1] + rMatrix[1][1], matrix[1][2] + rMatrix[1][2],
		matrix[2][0] + rMatrix[2][0],	matrix[2][1] + rMatrix[2][1], matrix[2][2] + rMatrix[2][2]
	);
}

inline Matrix3 Matrix3::operator- (const Matrix3& rMatrix) const
{
	return Matrix3(
		matrix[0][0] - rMatrix[0][0],	matrix[0][1] - rMatrix[0][1], matrix[0][2] - rMatrix[0][2],
		matrix[1][0] - rMatrix[1][0],	matrix[1][1] - rMatrix[1][1], matrix[1][2] - rMatrix[1][2],
		matrix[2][0] - rMatrix[2][0],	matrix[2][1] - rMatrix[2][1], matrix[2][2] - rMatrix[2][2]
	);
}

inline Matrix3 Matrix3::operator* (const Matrix3& rMatrix) const
{
	Real a11 = matrix[0][0], a12 = matrix[0][1], a13 = matrix[0][2];
	Real a21 = matrix[1][0], a22 = matrix[1][1], a23 = matrix[1][2];
	Real a31 = matrix[2][0], a32 = matrix[2][1], a33 = matrix[2][2];

	Real b11 = rMatrix.matrix[0][0], b12 = rMatrix.matrix[0][1], b13 = rMatrix.matrix[0][2];
	Real b21 = rMatrix.matrix[1][0], b22 = rMatrix.matrix[1][1], b23 = rMatrix.matrix[1][2];
	Real b31 = rMatrix.matrix[2][0], b32 = rMatrix.matrix[2][1], b33 = rMatrix.matrix[2][2];

	Real c11 = a11*b11 + a12*b21 + a13*b31;
	Real c12 = a11*b12 + a12*b22 + a13*b32;
	Real c13 = a11*b13 + a12*b23 + a13*b33;

	Real c21 = a21*b11 + a22*b21 + a23*b31;
	Real c22 = a21*b12 + a22*b22 + a23*b32;
	Real c23 = a21*b13 + a22*b23 + a23*b33;

	Real c31 = a31*b11 + a32*b21 + a33*b31;
	Real c32 = a31*b12 + a32*b22 + a33*b32;
	Real c33 = a31*b13 + a32*b23 + a33*b33;

	return Matrix3(
		c11, c12, c13,
		c21, c22, c23,
		c31, c32, c33
		);
}

inline Matrix3 Matrix3::operator* (Real scalar) const
{
	return Matrix3(
		matrix[0][0] * scalar,	matrix[0][1] * scalar, matrix[0][2] * scalar,
		matrix[1][0] * scalar,	matrix[1][1] * scalar, matrix[1][2] * scalar,
		matrix[2][0] * scalar,	matrix[2][1] * scalar, matrix[2][2] * scalar
		);
}

inline Matrix3& Matrix3::operator*= (const Matrix3& rMatrix)
{
	*this = this->operator*(rMatrix);
	return *this;
}

inline Matrix3 Matrix3::operator/ (Real scalar) const
{
	Real invScalar = 1/scalar;
	return this->operator*(invScalar);
}

inline Matrix3 Matrix3::operator- () const
{
	return Matrix3(
		-matrix[0][0],	-matrix[0][1], -matrix[0][2],
		-matrix[1][0],	-matrix[1][1], -matrix[1][2],
		-matrix[2][0],	-matrix[2][1], -matrix[2][2]
	);
}

inline Matrix3& Matrix3::operator+= (const Matrix3& rMatrix)
{
	matrix[0][0] += rMatrix[0][0];	matrix[0][1] += rMatrix[0][1]; matrix[0][2] += rMatrix[0][2];
	matrix[1][0] += rMatrix[1][0];	matrix[1][1] += rMatrix[1][1]; matrix[1][2] += rMatrix[1][2];
	matrix[2][0] += rMatrix[2][0];	matrix[2][1] += rMatrix[2][1]; matrix[2][2] += rMatrix[2][2];

	return *this;
}

inline Matrix3& Matrix3::operator-= (const Matrix3& rMatrix)
{
	matrix[0][0] -= rMatrix[0][0];	matrix[0][1] -= rMatrix[0][1]; matrix[0][2] -= rMatrix[0][2];
	matrix[1][0] -= rMatrix[1][0];	matrix[1][1] -= rMatrix[1][1]; matrix[1][2] -= rMatrix[1][2];
	matrix[2][0] -= rMatrix[2][0];	matrix[2][1] -= rMatrix[2][1]; matrix[2][2] -= rMatrix[2][2];

	return *this;
}

inline Matrix3& Matrix3::operator*= (const Real scalar)
{
	matrix[0][0] *= scalar;	matrix[0][1] *= scalar; matrix[0][2] *= scalar;
	matrix[1][0] *= scalar;	matrix[1][1] *= scalar; matrix[1][2] *= scalar;
	matrix[2][0] *= scalar;	matrix[2][1] *= scalar; matrix[2][2] *= scalar;

	return *this;
}

inline Matrix3& Matrix3::operator/= (const Real scalar)
{
	matrix[0][0] /= scalar;	matrix[0][1] /= scalar;	matrix[0][2] /= scalar;
	matrix[1][0] /= scalar;	matrix[1][1] /= scalar;	matrix[1][2] /= scalar;
	matrix[2][0] /= scalar;	matrix[2][1] /= scalar;	matrix[2][2] /= scalar;

	return *this;
}

inline Vector3 Matrix3::operator* (const Vector3& rkV) const
{
	return Vector3(
		matrix[0][0]*rkV.x + matrix[0][1]*rkV.y + matrix[0][2] * rkV.z,
		matrix[1][0]*rkV.x + matrix[1][1]*rkV.y + matrix[1][2] * rkV.z,
		matrix[2][0]*rkV.x + matrix[2][1]*rkV.y + matrix[2][2] * rkV.z
		);
}

Matrix3 Matrix3::transpose() const
{
	return Matrix3(
		matrix[0][0], matrix[1][0], matrix[2][0],
		matrix[0][1], matrix[1][1], matrix[2][1],
		matrix[0][2], matrix[1][2], matrix[2][2]
	);
}

Matrix3 Matrix3::inverse() const
{
	Real determinant = this->determinant();

	if(Math::FAbs(determinant) > Math::ZERO_TOLERANCE)
	{
		Real a11 = matrix[0][0], a12 = matrix[0][1], a13 = matrix[0][2];
		Real a21 = matrix[1][0], a22 = matrix[1][1], a23 = matrix[1][2];
		Real a31 = matrix[2][0], a32 = matrix[2][1], a33 = matrix[2][2];

		Real b11 = a22*a33 - a23*a32;
		Real b12 = a13*a32 - a12*a33;
		Real b13 = a12*a23 - a13*a22;

		Real b21 = a23*a31 - a21*a33;
		Real b22 = a11*a33 - a13*a31;
		Real b23 = a13*a21 - a11*a23;

		Real b31 = a21*a32 - a22*a31;
		Real b32 = a12*a31 - a11*a32;
		Real b33 =  a11*a22 - a12*a21;

		Matrix3 invMat(	b11, b12, b13,
			b21, b22, b23,
			b31, b32, b33);

		invMat /= determinant;

		return invMat;
	}

	return Matrix3();
}

Matrix3 Matrix3::adjoint() const
{
	Matrix3 adjointMatrix;
	Matrix2 reductedMatrix;

	reductedMatrix[0][0] = matrix[1][1]; reductedMatrix[0][1] = matrix[1][2]; 
	reductedMatrix[1][0] = matrix[2][1]; reductedMatrix[1][1] = matrix[2][2]; 
	adjointMatrix.matrix[0][0] =  reductedMatrix.determinant();
	reductedMatrix[0][0] = matrix[1][0]; reductedMatrix[0][1] = matrix[1][2]; 
	reductedMatrix[1][0] = matrix[2][0]; reductedMatrix[1][1] = matrix[2][2]; 
	adjointMatrix.matrix[0][1] = -reductedMatrix.determinant();
	reductedMatrix[0][0] = matrix[1][0]; reductedMatrix[0][1] = matrix[1][1]; 
	reductedMatrix[1][0] = matrix[2][0]; reductedMatrix[1][1] = matrix[2][1]; 
	adjointMatrix.matrix[0][2] =  reductedMatrix.determinant();


	reductedMatrix[0][0] = matrix[0][1]; reductedMatrix[0][1] = matrix[0][2]; 
	reductedMatrix[1][0] = matrix[2][1]; reductedMatrix[1][1] = matrix[2][2];
	adjointMatrix.matrix[1][0] = -reductedMatrix.determinant();
	reductedMatrix[0][0] = matrix[0][0]; reductedMatrix[0][1] = matrix[0][1]; 
	reductedMatrix[1][0] = matrix[2][0]; reductedMatrix[1][1] = matrix[2][2];
	adjointMatrix.matrix[1][1] =  reductedMatrix.determinant();
	reductedMatrix[0][0] = matrix[0][0]; reductedMatrix[0][1] = matrix[0][1]; 
	reductedMatrix[1][0] = matrix[2][0]; reductedMatrix[1][1] = matrix[2][1];
	adjointMatrix.matrix[1][2] = -reductedMatrix.determinant();


	reductedMatrix[0][0] = matrix[0][1]; reductedMatrix[0][1] = matrix[0][2]; 
	reductedMatrix[1][0] = matrix[1][1]; reductedMatrix[1][1] = matrix[1][2];
	adjointMatrix.matrix[2][0] =  reductedMatrix.determinant();			
	reductedMatrix[0][0] = matrix[0][0]; reductedMatrix[0][1] = matrix[0][2]; 
	reductedMatrix[1][0] = matrix[2][0]; reductedMatrix[1][1] = matrix[2][1];
	adjointMatrix.matrix[2][1] = -reductedMatrix.determinant();			
	reductedMatrix[0][0] = matrix[0][0]; reductedMatrix[0][1] = matrix[0][1]; 
	reductedMatrix[1][0] = matrix[1][0]; reductedMatrix[1][1] = matrix[1][1];
	adjointMatrix.matrix[2][2] =  reductedMatrix.determinant();

	return adjointMatrix;
}

Real Matrix3::determinant() const
{
	return 
		((matrix[0][0] * matrix[1][1] * matrix[2][2]) + 
		( matrix[0][1] * matrix[1][2] * matrix[2][0]) + 
		( matrix[0][2] * matrix[1][0] * matrix[2][1])) -
		((matrix[0][2] * matrix[1][1] * matrix[2][0]) + 
		( matrix[0][0] * matrix[1][2] * matrix[2][1]) + 
		( matrix[0][1] * matrix[1][0] * matrix[2][2]));
}

Real Matrix3::qForm(const Vector3& rkU, const Vector3& rkV) const
{
	return rkU.dotProduct((*this) * rkV);
}

Matrix3 Matrix3::scale(const Vector3& rkV)
{
	return Matrix3(
		rkV.x,	0.0,		0.0,
		0.0,		rkV.y,	0.0,
		0.0,		0.0,		rkV.z
		);
}
