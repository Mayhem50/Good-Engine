#pragma once
#include "Matrix3.h"
#include "Vector4.h"

namespace Good
{
	struct GOOD_DLL Matrix4
	{
		Matrix4(void);
		Matrix4(const Matrix4& rMatrix);
		Matrix4(
			Real f00, Real f01, Real f02, Real f03,
			Real f10, Real f11, Real f12, Real f13,
			Real f20, Real f21, Real f22, Real f23,
			Real f30, Real f31, Real f32, Real f33);
		Matrix4(const Real rEntry[16], bool bRowMajor = true);
		Matrix4(const Vector4& rkU, const Vector4& rkV, const Vector4& rkW, const Vector4& rkT, bool bColumns = true);
		Matrix4(const Vector4* akV, bool bColumns = true);
		Matrix4(Real f00, Real f11, Real f22, Real f33);
		Matrix4(Real fAngle, AXIS axe = AXIS::X_AXIS);
		Matrix4(const Matrix3& rMatrix);

		~Matrix4(void);

		void makeZero();
		void makeIdentity();
		void makeDiagonal(Real f00, Real f11, Real f22, Real f33);
		void fromAngleOnX(Real fAngle);
		void fromAngleOnY(Real fAngle);
		void fromAngleOnZ(Real fAngle);
		void setRow(int iRow, const Vector4& rkV);
		Vector4 getRow(int iRow) const;	
		void setColumn(int iColumn, const Vector4& rkV);
		Vector4 getColumn(int iColumn) const;

		const Real* operator[] (int iRow) const;
		Real* operator[] (int iRow);
		Real& operator() (int iRow, int iColumn);
		Real operator() (int iRow, int iColumn) const;		
		Matrix4& operator= (const Matrix4& rMatrix);
		Matrix4& operator= (const Matrix3& rMatrix);

		bool operator== (const Matrix4& rMatrix) const;
		bool operator!= (const Matrix4& rMatrix) const;

		Matrix4 operator+ (const Matrix4& rMatrix) const;
		Matrix4 operator- (const Matrix3& rMatrix) const;
		Matrix4 operator* (const Matrix4& rMatrix) const;
		Matrix4& operator*=(const Matrix4& rMatrix);
		Matrix4 operator* (Real scalar) const;
		Matrix4 operator/ (Real scalar) const;
		Matrix4 operator- () const;
		Matrix4& operator+= (const Matrix3& rMatrix);
		Matrix4& operator-= (const Matrix3& rMatrix);
		Matrix4& operator*= (const Real scalar);
		Matrix4& operator/= (const Real scalar);
		Vector4 operator* (const Vector4& rkV) const;

		Matrix4 inverse() const;
		Matrix4 Matrix4::adjoint() const;
		Real Matrix4::determinant() const;
		static Matrix4 scale(const Vector3& rkV);
		static Real MINOR(	const Matrix4& m, const size_t r0, const size_t r1, const size_t r2, 
			const size_t c0, const size_t c1, const size_t c2);

		friend ::std::ostream& operator<<(std::ostream& out, const Matrix4& rMatrix)
		{
			out << rMatrix.matrix[0][0] << "|" << rMatrix.matrix[0][1] << "|" << rMatrix.matrix[0][2] << "|" << rMatrix.matrix[0][3] << std::endl;
			out << rMatrix.matrix[1][0] << "|" << rMatrix.matrix[1][1] << "|" << rMatrix.matrix[1][2] << "|" << rMatrix.matrix[1][3] << std::endl;
			out << rMatrix.matrix[2][0] << "|" << rMatrix.matrix[2][1] << "|" << rMatrix.matrix[2][2] << "|" << rMatrix.matrix[2][3] << std::endl;
			out << rMatrix.matrix[3][0] << "|" << rMatrix.matrix[3][1] << "|" << rMatrix.matrix[3][2] << "|" << rMatrix.matrix[3][3] << std::endl;
		}

		std::string toString()
		{
			char buffer[MAX_CHAR];
			sprintf_s(buffer, "\n\t%.3lf | %.3lf | %.3lf | %.3lf\n\t%.3lf | %.3lf | %.3lf | %.3lf\n\t%.3lf | %.3lf | %.3lf | %.3lf\n\t%.3lf | %.3lf | %.3lf | %.3lf", 
				matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3],
				matrix[1][0], matrix[1][1], matrix[1][2],	matrix[1][3],																											 
				matrix[2][0], matrix[2][1], matrix[2][2], matrix[1][3],																											 
				matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3]);
			return std::string("\n") + typeid(*this).name() + std::string(buffer);
		}

		static const Matrix4 ZERO;
		static const Matrix4 IDENTITY;

		Real matrix[4][4];
	};
}

