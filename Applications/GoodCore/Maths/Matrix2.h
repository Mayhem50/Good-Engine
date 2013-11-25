#pragma once
#include "../Core/GoodFoundationLib.h"
#include "Vector2.h"

namespace Good
{
	struct GOOD_DLL Matrix2
	{
		Matrix2(void);

		Matrix2(const Matrix2& rMatrix);
		Matrix2(Real f00, Real f01, Real f10, Real f11);
		Matrix2(const Real rEntry[4], bool bRowMajor = true);
		Matrix2(const Vector2& rkU, const Vector2& rkV, bool bColumns = true);
		Matrix2(const Vector2* akV, bool bColumns = true);
		Matrix2(Real f00, Real f11);
		Matrix2(Real fAngle);

		void makeZero();
		void makeIdentity();
		void makeDiagonal(Real f00, Real f11);
		void fromAngle(Real fAngle);
		void makeTensorProduct(const Vector2& rkU, const Vector2& rkV);

		const Real* operator[] (int iRow) const;
		Real* operator[] (int iRow);
		Real operator() (int iRow, int iColumn) const;
		Matrix2& operator= (const Matrix2& rMatrix);

		bool operator== (const Matrix2& rMatrix) const;
		bool operator!= (const Matrix2& rMatrix) const;

		Matrix2 operator+ (const Matrix2& rMatrix) const;
		Matrix2 operator- (const Matrix2& rMatrix) const;
		Matrix2 operator* (const Matrix2& rMatrix) const;
		Matrix2 operator* (Real scalar) const;
		Matrix2 operator/ (Real scalar) const;
		Matrix2 operator- () const;
		Vector2 operator* (const Vector2& rkV) const;

		Matrix2& operator+= (const Matrix2& rMatrix);
		Matrix2& operator-= (const Matrix2& rMatrix);
		Matrix2& operator*= (const Real scalar);
		Matrix2& operator/= (const Real scalar);

		void setRow(int iRow, const Vector2& rkV);
		Vector2 getRow(int iRow) const;
		void setColumn(int iColumn, const Vector2& rkV);
		Vector2 getColumn(int iColumn) const;

		Matrix2 transpose() const;
		Matrix2 transposeTimes(const Matrix2& rMatrix) const;
		Matrix2 timeTranspose(const Matrix2& rMatrix) const;
		Matrix2 inverse() const;
		Matrix2 adjoint() const;
		Real determinant() const;
		Real qForm(const Vector2& rkU, const Vector2& rkV) const;
		void toAngle(Real& fAngle) const;
		void orthoNormalize();
		
		inline friend ::std::ostream& operator<<(std::ostream& out, const Matrix2& rMatrix)
		{
			out << rMatrix.matrix[0][0] << "|" << rMatrix.matrix[0][1] << std::endl;
			out << rMatrix.matrix[1][0] << "|" << rMatrix.matrix[1][1] << std::endl;
		}

		inline std::string Matrix2::toString()
		{
			char buffer[MAX_CHAR];
			sprintf_s(buffer, "\n\t%.3lf | %.3lf\n\t%.3lf | %.3lf", matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1]);
			return std::string("\n") + typeid(*this).name() + std::string(buffer);
		}

		static const Matrix2 ZERO;
		static const Matrix2 IDENTITY;

		Real matrix[2][2];
	};
}
