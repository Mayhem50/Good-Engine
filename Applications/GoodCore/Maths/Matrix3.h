#pragma once
#include "Vector3.h"
#include "Matrix2.h"

namespace Good
{
	struct GOOD_DLL Matrix3
	{
		Matrix3(void);
		Matrix3(const Matrix3& rMatrix);
		Matrix3(
			Real f00, Real f01, Real f02, 
			Real f10, Real f11, Real f12,
			Real f20, Real f21, Real f22);
		Matrix3(const Real rEntry[9], bool bRowMajor = true);
		Matrix3(const Vector3& rkU, const Vector3& rkV, const Vector3& rkW, bool bColumns = true);
		Matrix3(const Vector3* akV, bool bColumns = true);
		Matrix3(Real f00, Real f11, Real f22);
		Matrix3(Real fAngle, AXIS axe = AXIS::X_AXIS);
		Matrix3(const Matrix2& rMatrix);

		void makeZero();
		void makeIdentity();
		void makeDiagonal(Real f00, Real f11, Real f22);
		void fromAngleOnX(Real fAngle);
		void fromAngleOnY(Real fAngle);
		void fromAngleOnZ(Real fAngle);
		void makeTensorProduct(const Vector3& rkU, const Vector3& rkV);
		void setRow(int iRow, const Vector3& rkV);
		Vector3 getRow(int iRow) const;	
		void setColumn(int iColumn, const Vector3& rkV);
		Vector3 getColumn(int iColumn) const;

		const Real* operator[] (int iRow) const;
		Real* operator[] (int iRow);
		Real& operator() (int iRow, int iColumn);
		Real operator() (int iRow, int iColumn) const;		

		Matrix3& operator= (const Matrix3& rMatrix);
		Matrix3& operator= (const Matrix2& rMatrix);

		bool operator== (const Matrix3& rMatrix) const;
		bool operator!= (const Matrix3& rMatrix) const;
		Matrix3 operator+ (const Matrix3& rMatrix) const;
		Matrix3 operator- (const Matrix3& rMatrix) const;
		Matrix3 operator* (const Matrix3& rMatrix) const;
		Matrix3 operator* (Real scalar) const;
		Matrix3& operator*= (const Matrix3& rMatrix);
		Matrix3 operator/ (Real scalar) const;
		Matrix3 operator- () const;
		Matrix3& operator+= (const Matrix3& rMatrix);
		Matrix3& operator-= (const Matrix3& rMatrix);
		Matrix3& operator*= (const Real scalar);
		Matrix3& operator/= (const Real scalar);
		Vector3 operator* (const Vector3& rkV) const;

		Matrix3 transpose() const;
		Matrix3 inverse() const;
		Matrix3 adjoint() const;
		Real determinant() const;
		Real qForm(const Vector3& rkU, const Vector3& rkV) const;
		static Matrix3 scale(const Vector3& rkV);

		static const Matrix3 ZERO;
		static const Matrix3 IDENTITY;

		~Matrix3(void){}

		friend ::std::ostream& operator<<(std::ostream& out, const Matrix3& rMatrix)
		{
			out << rMatrix.matrix[0][0] << "|" << rMatrix.matrix[0][1] << "|" << rMatrix.matrix[0][2] << std::endl;
			out << rMatrix.matrix[1][0] << "|" << rMatrix.matrix[1][1] << "|" << rMatrix.matrix[1][2] << std::endl;
			out << rMatrix.matrix[2][0] << "|" << rMatrix.matrix[2][1] << "|" << rMatrix.matrix[2][2] << std::endl;
		}

		std::string toString()
		{
			char buffer[MAX_CHAR];
			sprintf_s(buffer, "\n\t%.3lf | %.3lf | %.3lf \n\t%.3lf | %.3lf | %.3lf \n\t%.3lf | %.3lf | %.3lf", 
				matrix[0][0], matrix[0][1], matrix[0][2], 
				matrix[1][0], matrix[1][1], matrix[1][2],																												 
				matrix[2][0], matrix[2][1], matrix[2][2]);
			return std::string("\n") + typeid(*this).name() + std::string(buffer);
		}

		Real matrix[3][3];
	};
}

