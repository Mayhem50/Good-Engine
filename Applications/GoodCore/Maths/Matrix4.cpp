#include "Matrix4.h"

using namespace Good;

const Matrix4 Matrix4::ZERO(0.0, 0.0, 0.0, 0.0,
														0.0, 0.0, 0.0, 0.0,
														0.0, 0.0, 0.0, 0.0,
														0.0, 0.0, 0.0, 0.0);
const Matrix4 Matrix4::IDENTITY(1.0, 0.0, 0.0, 0.0,
																0.0, 1.0, 0.0, 0.0,
																0.0, 0.0, 1.0, 0.0,
																0.0, 0.0, 0.0, 1.0);

inline Matrix4::Matrix4(void)
{
	makeZero();
}

inline Matrix4::Matrix4(const Matrix4& rMatrix)
{
	matrix[0][0] = rMatrix.matrix[0][0];	matrix[0][1] = rMatrix.matrix[0][1];	matrix[0][2] = rMatrix.matrix[0][2]; matrix[0][3] = rMatrix.matrix[0][3];
	matrix[1][0] = rMatrix.matrix[1][0];	matrix[1][1] = rMatrix.matrix[1][1];	matrix[1][2] = rMatrix.matrix[1][2]; matrix[1][3] = rMatrix.matrix[1][3];
	matrix[2][0] = rMatrix.matrix[2][0];	matrix[2][1] = rMatrix.matrix[2][1];	matrix[2][2] = rMatrix.matrix[2][2]; matrix[2][3] = rMatrix.matrix[2][3];
	matrix[3][0] = rMatrix.matrix[3][0];	matrix[3][1] = rMatrix.matrix[3][1];	matrix[3][2] = rMatrix.matrix[3][2]; matrix[3][3] = rMatrix.matrix[3][3];
}

inline Matrix4::Matrix4(
	Real f00, Real f01, Real f02, Real f03,
	Real f10, Real f11, Real f12, Real f13,
	Real f20, Real f21, Real f22, Real f23,
	Real f30, Real f31, Real f32, Real f33)
{
	matrix[0][0] = f00;	matrix[0][1] = f01;	matrix[0][2] = f02;	matrix[0][3] = f03;
	matrix[1][0] = f10;	matrix[1][1] = f11;	matrix[1][2] = f12;	matrix[1][3] = f13;
	matrix[2][0] = f20;	matrix[2][1] = f21;	matrix[2][2] = f22;	matrix[2][3] = f23;
	matrix[3][0] = f30;	matrix[3][1] = f31;	matrix[3][2] = f32;	matrix[3][3] = f33;
}

inline Matrix4::Matrix4(const Real rEntry[16], bool bRowMajor)
{
	if(bRowMajor)
	{
		matrix[0][0] = rEntry[0];		matrix[0][1] = rEntry[1];		matrix[0][2] = rEntry[2];	 matrix[0][3] = rEntry[3];
		matrix[1][0] = rEntry[4];		matrix[1][1] = rEntry[5];		matrix[1][2] = rEntry[6];	 matrix[1][3] = rEntry[7];
		matrix[2][0] = rEntry[8];		matrix[2][1] = rEntry[9];		matrix[2][2] = rEntry[10]; matrix[2][3] = rEntry[11];
		matrix[3][0] = rEntry[12];	matrix[3][1] = rEntry[13];	matrix[3][2] = rEntry[14]; matrix[3][3] = rEntry[15];
	}
	else
	{
		matrix[0][0] = rEntry[0];		matrix[0][1] = rEntry[4];		matrix[0][2] = rEntry[8];	 matrix[0][3] = rEntry[12];
		matrix[1][0] = rEntry[1];		matrix[1][1] = rEntry[5];		matrix[1][2] = rEntry[9];	 matrix[1][3] = rEntry[13];
		matrix[2][0] = rEntry[2];		matrix[2][1] = rEntry[6];		matrix[2][2] = rEntry[10]; matrix[2][3] = rEntry[14];
		matrix[3][0] = rEntry[3];		matrix[3][1] = rEntry[7];		matrix[3][2] = rEntry[11]; matrix[3][3] = rEntry[15];
	}
}

inline Matrix4::Matrix4(const Vector4& rkU, const Vector4& rkV, const Vector4& rkW, const Vector4& rkT, bool bColumns)
{
	if(bColumns)
	{
		matrix[0][0] = rkU.x;	matrix[0][1] = rkV.x;	matrix[0][2] = rkW.x;	matrix[0][3] = rkT.x;
		matrix[1][0] = rkU.y;	matrix[1][1] = rkV.y;	matrix[1][2] = rkW.y;	matrix[1][3] = rkT.y;
		matrix[2][0] = rkU.z;	matrix[2][1] = rkV.z;	matrix[2][2] = rkW.z;	matrix[2][3] = rkT.z;
		matrix[2][0] = rkU.w;	matrix[2][1] = rkV.w;	matrix[2][2] = rkW.w;	matrix[2][3] = rkT.w;
	}
	else
	{
		matrix[0][0] = rkU.x;	matrix[0][1] = rkU.y;	matrix[0][2] = rkU.z; matrix[0][3] = rkU.w;
		matrix[1][0] = rkV.x;	matrix[1][1] = rkV.y;	matrix[1][2] = rkV.z; matrix[1][3] = rkV.w;
		matrix[2][0] = rkW.x;	matrix[2][1] = rkW.y;	matrix[2][2] = rkW.z; matrix[2][3] = rkW.w;
		matrix[3][0] = rkT.x;	matrix[3][1] = rkT.y;	matrix[3][2] = rkT.z; matrix[3][3] = rkT.w;
	}
}

inline Matrix4::Matrix4(const Vector4* akV, bool bColumns)
{
	if(bColumns)
	{
		matrix[0][0] = akV[0].x;	matrix[0][1] = akV[1].x;	matrix[0][2] = akV[2].x;	matrix[0][3] = akV[3].x;
		matrix[1][0] = akV[0].y;	matrix[1][1] = akV[1].y;	matrix[1][2] = akV[2].y;	matrix[1][3] = akV[3].y;
		matrix[2][0] = akV[0].z;	matrix[2][1] = akV[1].z;	matrix[2][2] = akV[2].z;	matrix[2][3] = akV[3].z;
		matrix[3][0] = akV[0].w;	matrix[3][1] = akV[1].w;	matrix[3][2] = akV[2].w;	matrix[3][3] = akV[3].w;
	}
	else
	{
		matrix[0][0] = akV[0].x;	matrix[0][1] = akV[0].y;	matrix[0][2] = akV[0].z;	matrix[0][3] = akV[0].w;
		matrix[1][0] = akV[1].x;	matrix[1][1] = akV[1].y;	matrix[1][2] = akV[1].z;	matrix[1][3] = akV[1].w;
		matrix[2][0] = akV[2].x;	matrix[2][1] = akV[2].y;	matrix[2][2] = akV[2].z;	matrix[2][3] = akV[2].w;
		matrix[3][0] = akV[3].x;	matrix[2][1] = akV[3].y;	matrix[2][2] = akV[3].z;	matrix[3][3] = akV[3].w;
	}
}

inline Matrix4::Matrix4(Real f00, Real f11, Real f22, Real f33)
{
	makeDiagonal(f00, f11, f22, f33);
}

inline Matrix4::Matrix4(Real fAngle, AXIS axe)
{
	if(axe == AXIS::X_AXIS)
		fromAngleOnX(fAngle);
	else if(axe == AXIS::Y_AXIS)
		fromAngleOnY(fAngle);
	else if(axe == AXIS::Z_AXIS)
		fromAngleOnZ(fAngle);
}

inline Matrix4::Matrix4(const Matrix3& rMatrix)
{
	matrix[0][0] = rMatrix.matrix[0][0];	matrix[0][1] = rMatrix.matrix[0][1];	matrix[0][2] = rMatrix.matrix[0][2];  matrix[0][3] = 0.0;
	matrix[1][0] = rMatrix.matrix[1][0];	matrix[1][1] = rMatrix.matrix[1][1];	matrix[1][2] = rMatrix.matrix[1][2];  matrix[1][3] = 0.0;
	matrix[2][0] = rMatrix.matrix[2][0];	matrix[2][1] = rMatrix.matrix[2][1];	matrix[2][2] = rMatrix.matrix[2][2];  matrix[2][3] = 0.0;
	matrix[3][0] = 0.0;										matrix[3][1] = 0.0;										matrix[3][2] = 0.0;									  matrix[3][3] = 1.0;
}

void Matrix4::makeZero()
{
	matrix[0][0] = 0.0;	matrix[0][1] = 0.0;	matrix[0][2] = 0.0;	matrix[0][3] = 0.0;
	matrix[1][0] = 0.0;	matrix[1][1] = 0.0;	matrix[1][2] = 0.0;	matrix[1][3] = 0.0;
	matrix[2][0] = 0.0;	matrix[2][1] = 0.0;	matrix[2][2] = 0.0;	matrix[2][3] = 0.0;
	matrix[3][0] = 0.0;	matrix[3][1] = 0.0;	matrix[3][2] = 0.0;	matrix[3][3] = 0.0;
}

void Matrix4::makeIdentity()
{
	matrix[0][0] = 1.0;	matrix[0][1] = 0.0;	matrix[0][2] = 0.0;	matrix[0][3] = 0.0;
	matrix[1][0] = 0.0;	matrix[1][1] = 1.0;	matrix[1][2] = 0.0;	matrix[1][3] = 0.0;
	matrix[2][0] = 0.0;	matrix[2][1] = 0.0;	matrix[2][2] = 1.0;	matrix[2][3] = 0.0;
	matrix[3][0] = 0.0;	matrix[3][1] = 0.0;	matrix[3][2] = 0.0;	matrix[3][3] = 1.0;
}

void Matrix4::makeDiagonal(Real f00, Real f11, Real f22, Real f33)
{
	matrix[0][0] = f00;	matrix[0][1] = 0.0;	matrix[0][2] = 0.0;	matrix[0][3] = 0.0;
	matrix[1][0] = 0.0;	matrix[1][1] = f11;	matrix[1][2] = 0.0;	matrix[1][3] = 0.0;
	matrix[2][0] = 0.0;	matrix[2][1] = 0.0;	matrix[2][2] = f22;	matrix[2][3] = 0.0;
	matrix[3][0] = 0.0;	matrix[3][1] = 0.0;	matrix[3][2] = 0.0;	matrix[3][3] = f33;
}

Matrix4::~Matrix4(void){}

void Matrix4::fromAngleOnX(Real fAngle)
{
	matrix[0][0] = 1.0;	matrix[0][1] = 0.0;								matrix[0][2] = 0.0;						matrix[0][3] = 0.0;
	matrix[1][0] = 0.0;	matrix[1][1] = Math::Cos(fAngle);																matrix[1][3] = 0.0;
	matrix[2][0] = 0.0;	matrix[2][1] = Math::Sin(fAngle); matrix[2][2] = matrix[1][1];	matrix[2][3] = 0.0;
	matrix[3][0] = 0.0;	matrix[3][1] = 0.0;								matrix[3][2] = 0.0;						matrix[3][3] = 1.0;

	matrix[1][2] = -matrix[2][1];
}

void Matrix4::fromAngleOnY(Real fAngle)
{
	matrix[0][0] = Math::Cos(fAngle);	matrix[0][1] = 0.0;						matrix[0][2] = Math::Sin(fAngle); matrix[0][3] = 0.0;
	matrix[1][0] = 0.0;								matrix[1][1] = 1.0;						matrix[1][2] = 0.0;								matrix[1][3] = 0.0;
	matrix[2][0] = -matrix[0][2];			matrix[2][2] = matrix[1][1];	matrix[2][1] = matrix[0][0];			matrix[2][3] = 0.0;
	matrix[3][0] = 0.0;								matrix[3][1] = 0.0;						matrix[3][2] = 0.0;								matrix[3][3] = 1.0;
}

void Matrix4::fromAngleOnZ(Real fAngle)
{
	matrix[0][0] =  Math::Cos(fAngle);																matrix[0][2] = 0.0;	matrix[0][3] = 0.0;
	matrix[1][0] =  Math::Sin(fAngle);	matrix[1][1] = matrix[0][0];	matrix[1][2] = 0.0;	matrix[1][3] = 0.0;
	matrix[2][0] = 0.0;									matrix[2][1] = 0.0;						matrix[2][2] = 1.0; matrix[2][3] = 0.0;
	matrix[3][0] = 0.0;									matrix[3][1] = 0.0;						matrix[3][2] = 0.0;	matrix[3][3] = 1.0;

	matrix[0][1] = -matrix[1][0];			
}

inline const Real* Matrix4::operator[] (int iRow) const
{
	assert(iRow < 4);
	return matrix[iRow];
}

inline Real* Matrix4::operator[] (int iRow)
{
	assert(iRow < 4);
	return matrix[iRow];
}

inline Real& Matrix4::operator() (int iRow, int iColumn)
{
	assert(iRow < 4);
	assert(iColumn < 4);
	return matrix[iRow][iColumn];
}

inline Real Matrix4::operator() (int iRow, int iColumn) const
{
	assert(iRow < 4);
	assert(iColumn < 4);
	return matrix[iRow][iColumn];
}

void Matrix4::setRow(int iRow, const Vector4& rkV)
{
	assert(iRow < 4);
	matrix[iRow][0] = rkV.x; matrix[iRow][1] = rkV.y;	matrix[iRow][2] = rkV.z; matrix[iRow][3] = rkV.w;
}

inline Vector4 Matrix4::getRow(int iRow) const
{
	assert(iRow < 4);
	return Vector4(matrix[iRow][0], matrix[iRow][1], matrix[iRow][2], matrix[iRow][3]);
}	

void Matrix4::setColumn(int iColumn, const Vector4& rkV)
{
	assert(iColumn < 3);
	matrix[0][iColumn] = rkV.x;
	matrix[1][iColumn] = rkV.y;
	matrix[2][iColumn] = rkV.z;
	matrix[3][iColumn] = rkV.w;
}

inline Vector4 Matrix4::getColumn(int iColumn) const
{
	assert(iColumn < 4);
	return Vector4(matrix[0][iColumn], matrix[1][iColumn], matrix[2][iColumn], matrix[3][iColumn]);
}

inline Matrix4& Matrix4::operator= (const Matrix4& rMatrix)
{
	matrix[0][0] = rMatrix[0][0];	matrix[0][1] = rMatrix[0][1]; matrix[0][2] = rMatrix[0][2]; matrix[0][3] = rMatrix[0][3];
	matrix[1][0] = rMatrix[1][0];	matrix[1][1] = rMatrix[1][1]; matrix[1][2] = rMatrix[1][2]; matrix[1][3] = rMatrix[1][3];
	matrix[2][0] = rMatrix[2][0];	matrix[2][1] = rMatrix[2][1]; matrix[2][2] = rMatrix[2][2]; matrix[2][3] = rMatrix[2][3];
	matrix[3][0] = rMatrix[3][0];	matrix[3][1] = rMatrix[3][1]; matrix[3][2] = rMatrix[3][2]; matrix[3][3] = rMatrix[3][3];

	return *this;
}

inline Matrix4& Matrix4::operator= (const Matrix3& rMatrix)
{
	matrix[0][0] = rMatrix[0][0];	matrix[0][1] = rMatrix[0][1];	 matrix[0][2] = rMatrix[0][2];	matrix[0][3] = rMatrix[0][3];
	matrix[1][0] = rMatrix[1][0];	matrix[1][1] = rMatrix[1][1];	 matrix[1][2] = rMatrix[1][2];	matrix[1][3] = rMatrix[1][3];
	matrix[2][0] = rMatrix[2][0];	matrix[2][1] = rMatrix[2][1];	 matrix[2][2] = rMatrix[2][2];	matrix[2][3] = rMatrix[2][3];
	matrix[2][0] = 0.0;						matrix[2][1] = 0.0;						 matrix[2][2] = 0.0;						matrix[3][3] = 1.0;

	return *this;
}

inline bool Matrix4::operator== (const Matrix4& rMatrix) const
{
	return (
		matrix[0][0] == rMatrix[0][0] &&	matrix[0][1] == rMatrix[0][1] && matrix[0][2] == rMatrix[0][2] && matrix[0][3] == rMatrix[0][3] &&
		matrix[1][0] == rMatrix[1][0] &&	matrix[1][1] == rMatrix[1][1] && matrix[1][2] == rMatrix[1][2] && matrix[1][3] == rMatrix[1][3] &&
		matrix[2][0] == rMatrix[2][0] &&	matrix[2][1] == rMatrix[2][1] && matrix[2][2] == rMatrix[2][2] && matrix[2][3] == rMatrix[2][3] &&
		matrix[3][0] == rMatrix[3][0] &&	matrix[3][1] == rMatrix[3][1] && matrix[3][2] == rMatrix[3][2] && matrix[3][3] == rMatrix[3][3]
	);
}

inline bool Matrix4::operator!= (const Matrix4& rMatrix) const
{
	return (*this == rMatrix);
}

inline Matrix4 Matrix4::operator+ (const Matrix4& rMatrix) const
{
	return Matrix4(
		matrix[0][0] + rMatrix[0][0],	matrix[0][1] + rMatrix[0][1], matrix[0][2] + rMatrix[0][2], matrix[0][3] + rMatrix[0][3],
		matrix[1][0] + rMatrix[1][0],	matrix[1][1] + rMatrix[1][1], matrix[1][2] + rMatrix[1][2], matrix[1][3] + rMatrix[1][3],
		matrix[2][0] + rMatrix[2][0],	matrix[2][1] + rMatrix[2][1], matrix[2][2] + rMatrix[2][2], matrix[2][3] + rMatrix[2][3],
		matrix[3][0] + rMatrix[3][0],	matrix[3][1] + rMatrix[3][1], matrix[3][2] + rMatrix[3][2], matrix[3][3] + rMatrix[3][3]
	);
}

inline Matrix4 Matrix4::operator- (const Matrix3& rMatrix) const
{
	return Matrix4(
		matrix[0][0] - rMatrix[0][0],	matrix[0][1] - rMatrix[0][1], matrix[0][2] - rMatrix[0][2], matrix[0][3] - rMatrix[0][3],
		matrix[1][0] - rMatrix[1][0],	matrix[1][1] - rMatrix[1][1], matrix[1][2] - rMatrix[1][2], matrix[1][3] - rMatrix[1][3],
		matrix[2][0] - rMatrix[2][0],	matrix[2][1] - rMatrix[2][1], matrix[2][2] - rMatrix[2][2], matrix[2][3] - rMatrix[2][3],
		matrix[3][0] - rMatrix[3][0],	matrix[3][1] - rMatrix[3][1], matrix[3][2] - rMatrix[3][2], matrix[3][3] - rMatrix[3][3]
	);
}

inline Matrix4 Matrix4::operator* (const Matrix4& rMatrix) const
{
	Real a11 = matrix[0][0], a12 = matrix[0][1], a13 = matrix[0][2], a14 = matrix[0][3];
	Real a21 = matrix[1][0], a22 = matrix[1][1], a23 = matrix[1][2], a24 = matrix[1][3];
	Real a31 = matrix[2][0], a32 = matrix[2][1], a33 = matrix[2][2], a34 = matrix[2][3];
	Real a41 = matrix[3][0], a42 = matrix[3][1], a43 = matrix[3][2], a44 = matrix[3][3];

	Real b11 = rMatrix.matrix[0][0], b12 = rMatrix.matrix[0][1], b13 = rMatrix.matrix[0][2], b14 = rMatrix.matrix[0][3];
	Real b21 = rMatrix.matrix[1][0], b22 = rMatrix.matrix[1][1], b23 = rMatrix.matrix[1][2], b24 = rMatrix.matrix[1][3];
	Real b31 = rMatrix.matrix[2][0], b32 = rMatrix.matrix[2][1], b33 = rMatrix.matrix[2][2], b34 = rMatrix.matrix[2][3];
	Real b41 = rMatrix.matrix[3][0], b42 = rMatrix.matrix[3][1], b43 = rMatrix.matrix[3][2], b44 = rMatrix.matrix[3][3];

	Real c11 = a11*b11 + a12*b21 + a13*b31 + a14*b41;
	Real c12 = a11*b12 + a12*b22 + a13*b32 + a14*b42;
	Real c13 = a11*b13 + a12*b23 + a13*b33 + a14*b43;
	Real c14 = a11*b14 + a12*b24 + a13*b34 + a14*b44;

	Real c21 = a21*b11 + a22*b21 + a23*b31 + a24*b41;
	Real c22 = a21*b12 + a22*b22 + a23*b32 + a24*b42;
	Real c23 = a21*b13 + a22*b23 + a23*b33 + a24*b43;
	Real c24 = a21*b14 + a22*b24 + a23*b34 + a24*b44;

	Real c31 = a31*b11 + a32*b21 + a33*b31 + a34*b41;
	Real c32 = a31*b12 + a32*b22 + a33*b32 + a34*b42;
	Real c33 = a31*b13 + a32*b23 + a33*b33 + a34*b43;
	Real c34 = a31*b14 + a32*b24 + a33*b34 + a34*b44;

	Real c41 = a41*b11 + a42*b21 + a43*b31 + a44*b41;
	Real c42 = a41*b12 + a42*b22 + a43*b32 + a44*b42;
	Real c43 = a41*b13 + a42*b23 + a43*b33 + a44*b43;
	Real c44 = a41*b14 + a42*b24 + a43*b34 + a44*b44;

	return Matrix4(
		c11, c12, c13, c14,
		c21, c22, c23, c24,
		c31, c32, c33, c34,
		c41, c42, c43, c44
		);
}

inline Matrix4& Matrix4::operator*=(const Matrix4& rMatrix)
{
	*this = this->Matrix4::operator*(rMatrix);
	return *this;
}

inline Matrix4 Matrix4::operator* (Real scalar) const
{
	return Matrix4(
		matrix[0][0] * scalar,	matrix[0][1] * scalar, matrix[0][2] * scalar, matrix[0][3] * scalar,
		matrix[1][0] * scalar,	matrix[1][1] * scalar, matrix[1][2] * scalar, matrix[1][3] * scalar,
		matrix[2][0] * scalar,	matrix[2][1] * scalar, matrix[2][2] * scalar, matrix[2][3] * scalar,
		matrix[3][0] * scalar,	matrix[3][1] * scalar, matrix[3][2] * scalar, matrix[3][3] * scalar
		);
}

inline Matrix4 Matrix4::operator/ (Real scalar) const
{
	Real invScalar = 1/scalar;
	return this->Matrix4::operator*(invScalar);
}

inline Matrix4 Matrix4::operator- () const
{
	return Matrix4(
		-matrix[0][0],	-matrix[0][1], -matrix[0][2], -matrix[0][3],
		-matrix[1][0],	-matrix[1][1], -matrix[1][2], -matrix[1][3],
		-matrix[2][0],	-matrix[2][1], -matrix[2][2], -matrix[2][3],
		-matrix[3][0],	-matrix[3][1], -matrix[3][2], -matrix[3][3]
	);
}

inline Matrix4& Matrix4::operator+= (const Matrix3& rMatrix)
{
	matrix[0][0] += rMatrix[0][0];	matrix[0][1] += rMatrix[0][1]; matrix[0][2] += rMatrix[0][2]; matrix[0][3] += rMatrix[0][3];
	matrix[1][0] += rMatrix[1][0];	matrix[1][1] += rMatrix[1][1]; matrix[1][2] += rMatrix[1][2]; matrix[1][3] += rMatrix[1][3];
	matrix[2][0] += rMatrix[2][0];	matrix[2][1] += rMatrix[2][1]; matrix[2][2] += rMatrix[2][2]; matrix[2][3] += rMatrix[2][3];
	matrix[3][0] += rMatrix[3][0];	matrix[3][1] += rMatrix[3][1]; matrix[3][2] += rMatrix[3][2]; matrix[3][3] += rMatrix[3][3];

	return *this;
}

inline Matrix4& Matrix4::operator-= (const Matrix3& rMatrix)
{
	matrix[0][0] -= rMatrix[0][0];	matrix[0][1] -= rMatrix[0][1]; matrix[0][2] -= rMatrix[0][2]; matrix[0][3] -= rMatrix[0][3];
	matrix[1][0] -= rMatrix[1][0];	matrix[1][1] -= rMatrix[1][1]; matrix[1][2] -= rMatrix[1][2]; matrix[1][3] -= rMatrix[1][3];
	matrix[2][0] -= rMatrix[2][0];	matrix[2][1] -= rMatrix[2][1]; matrix[2][2] -= rMatrix[2][2]; matrix[2][3] -= rMatrix[2][3];
	matrix[3][0] -= rMatrix[3][0];	matrix[3][1] -= rMatrix[3][1]; matrix[3][2] -= rMatrix[3][2]; matrix[3][3] -= rMatrix[3][3];

	return *this;
}

inline Matrix4& Matrix4::operator*= (const Real scalar)
{
	matrix[0][0] *= scalar;	matrix[0][1] *= scalar; matrix[0][2] *= scalar; matrix[0][3] *= scalar;
	matrix[1][0] *= scalar;	matrix[1][1] *= scalar; matrix[1][2] *= scalar; matrix[1][3] *= scalar;
	matrix[2][0] *= scalar;	matrix[2][1] *= scalar; matrix[2][2] *= scalar; matrix[2][3] *= scalar;
	matrix[3][0] *= scalar;	matrix[3][1] *= scalar; matrix[3][2] *= scalar; matrix[3][3] *= scalar;

	return *this;
}

inline Matrix4& Matrix4::operator/= (const Real scalar)
{
	matrix[0][0] /= scalar;	matrix[0][1] /= scalar;	matrix[0][2] /= scalar;	matrix[0][3] /= scalar;
	matrix[1][0] /= scalar;	matrix[1][1] /= scalar;	matrix[1][2] /= scalar;	matrix[1][3] /= scalar;
	matrix[2][0] /= scalar;	matrix[2][1] /= scalar;	matrix[2][2] /= scalar;	matrix[2][3] /= scalar;
	matrix[3][0] /= scalar;	matrix[3][1] /= scalar;	matrix[3][2] /= scalar;	matrix[3][3] /= scalar;

	return *this;
}

inline Vector4 Matrix4::operator* (const Vector4& rkV) const
{
	return Vector4(
		matrix[0][0]*rkV.x + matrix[0][1]*rkV.y + matrix[0][2] * rkV.z + matrix[0][3] * rkV.w,
		matrix[1][0]*rkV.x + matrix[1][1]*rkV.y + matrix[1][2] * rkV.z + matrix[1][3] * rkV.w,
		matrix[2][0]*rkV.x + matrix[2][1]*rkV.y + matrix[2][2] * rkV.z + matrix[2][3] * rkV.w,
		matrix[3][0]*rkV.x + matrix[3][1]*rkV.y + matrix[3][2] * rkV.z + matrix[3][3] * rkV.w
		);
}

Matrix4 Matrix4::inverse() const
{
	Real determinant = this->determinant();

	if(Math::FAbs(determinant) > Math::ZERO_TOLERANCE)
	{
		Real a11 = matrix[0][0], a12 = matrix[0][1], a13 = matrix[0][2], a14 = matrix[0][3];
		Real a21 = matrix[1][0], a22 = matrix[1][1], a23 = matrix[1][2], a24 = matrix[1][3];
		Real a31 = matrix[2][0], a32 = matrix[2][1], a33 = matrix[2][2], a34 = matrix[2][3];
		Real a41 = matrix[3][0], a42 = matrix[3][1], a43 = matrix[3][2], a44 = matrix[3][3];

		Real b11 = a22*a33*a44 + a23*a34*a42 + a24*a32*a43 - a22*a34*a43 - a23*a32*a44 - a24*a33*a42;
		Real b12 = a12*a34*a43 + a13*a32*a44 + a14*a33*a42 - a12*a33*a44 - a13*a34*a42 - a14*a32*a43;
		Real b13 = a12*a23*a44 + a13*a24*a42 + a14*a22*a43 - a12*a24*a43 - a13*a22*a44 - a14*a23*a42;
		Real b14 = a12*a24*a33 + a13*a22*a34 + a14*a23*a32 - a12*a23*a34 - a13*a24*a32 - a14*a22*a33;
		Real b21 = a21*a34*a43 + a23*a31*a44 + a24*a33*a41 - a21*a33*a44 - a23*a34*a41 - a24*a31*a43;
		Real b22 = a11*a33*a44 + a13*a34*a41 + a14*a31*a43 - a11*a34*a43 - a13*a31*a44 - a14*a33*a41;
		Real b23 = a11*a24*a43 + a13*a21*a44 + a14*a23*a41 - a11*a23*a44 - a13*a24*a41 - a14*a21*a43;
		Real b24 = a11*a23*a34 + a13*a24*a31 + a14*a21*a33 - a11*a24*a33 - a13*a21*a34 - a14*a23*a31;
		Real b31 = a21*a32*a44 + a22*a34*a41 + a24*a31*a42 - a21*a34*a42 - a22*a31*a44 - a24*a32*a41;
		Real b32 = a11*a34*a42 + a12*a31*a44 + a14*a32*a41 - a11*a32*a44 - a12*a34*a41 - a14*a31*a42;
		Real b33 = a11*a22*a44 + a12*a24*a41 + a14*a21*a42 - a11*a24*a42 - a12*a21*a44 - a14*a22*a41;
		Real b34 = a11*a24*a32 + a12*a21*a34 + a14*a22*a31 - a11*a22*a34 - a12*a24*a31 - a14*a21*a32;
		Real b41 = a21*a33*a42 + a22*a31*a43 + a23*a32*a41 - a21*a32*a43 - a22*a33*a41 - a23*a31*a42;
		Real b42 = a11*a32*a43 + a12*a33*a41 + a13*a31*a42 - a11*a33*a42 - a12*a31*a43 - a13*a32*a41;
		Real b43 = a11*a23*a42 + a12*a21*a43 + a13*a22*a41 - a11*a22*a43 - a12*a23*a41 - a13*a21*a42;
		Real b44 = a11*a22*a33 + a12*a23*a31 + a13*a21*a32 - a11*a23*a32 - a12*a21*a33 - a13*a22*a31;

		Matrix4 invMat(	b11, b12, b13, b14,
			b21, b22, b23, b24,
			b31, b32, b33, b34,
			b41, b42, b43, b44);

		invMat /= determinant;

		return invMat;
	}

	return Matrix4();
}

Matrix4 Matrix4::adjoint() const
{
	return Matrix4( 
		MINOR(*this, 1, 2, 3, 1, 2, 3),
		-MINOR(*this, 0, 2, 3, 1, 2, 3),
		MINOR(*this, 0, 1, 3, 1, 2, 3),
		-MINOR(*this, 0, 1, 2, 1, 2, 3),

		-MINOR(*this, 1, 2, 3, 0, 2, 3),
		MINOR(*this, 0, 2, 3, 0, 2, 3),
		-MINOR(*this, 0, 1, 3, 0, 2, 3),
		MINOR(*this, 0, 1, 2, 0, 2, 3),

		MINOR(*this, 1, 2, 3, 0, 1, 3),
		-MINOR(*this, 0, 2, 3, 0, 1, 3),
		MINOR(*this, 0, 1, 3, 0, 1, 3),
		-MINOR(*this, 0, 1, 2, 0, 1, 3),

		-MINOR(*this, 1, 2, 3, 0, 1, 2),
		MINOR(*this, 0, 2, 3, 0, 1, 2),
		-MINOR(*this, 0, 1, 3, 0, 1, 2),
		MINOR(*this, 0, 1, 2, 0, 1, 2));
}

Real Matrix4::determinant() const
{
	return (
		matrix[0][0] * MINOR(*this, 1, 2, 3, 1, 2, 3) -
		matrix[0][1] * MINOR(*this, 1, 2, 3, 0, 2, 3) +
		matrix[0][2] * MINOR(*this, 1, 2, 3, 0, 1, 3) -
		matrix[0][3] * MINOR(*this, 1, 2, 3, 0, 1, 2)
		);
}

Matrix4 Matrix4::scale(const Vector3& rkV)
{
	return Matrix4(
		rkV.x,	0.0,		0.0,		0.0,
		0.0,		rkV.y,	0.0,		0.0,
		0.0,		0.0,		rkV.z,	0.0,
		0.0,		0.0,		0.0,		1.0
		);
}

Real Matrix4::MINOR(	const Matrix4& m, const size_t r0, const size_t r1, const size_t r2, 
					 const size_t c0, const size_t c1, const size_t c2)
{
	return m[r0][c0] * (m[r1][c1] * m[r2][c2] - m[r2][c1] * m[r1][c2]) -
		m[r0][c1] * (m[r1][c0] * m[r2][c2] - m[r2][c0] * m[r1][c2]) +
		m[r0][c2] * (m[r1][c0] * m[r2][c1] - m[r2][c0] * m[r1][c1]);
}

