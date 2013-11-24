#pragma once
#include "Vector2.h"

namespace Good
{
	class Matrix2
	{
	public:
		inline Matrix2(void)
		{
			m_matrix[0][0] = 0.0;
			m_matrix[0][1] = 0.0;
			m_matrix[1][0] = 0.0;
			m_matrix[1][1] = 0.0;
		};

		inline Matrix2(const Matrix2& rMatrix)
		{
			m_matrix[0][0] = rMatrix[0][0];
			m_matrix[0][1] = rMatrix[0][1];
			m_matrix[1][0] = rMatrix[1][0];
			m_matrix[1][1] = rMatrix[1][1];
		};

		inline Matrix2(Real f00, Real f01, Real f10, Real f11)
		{
			m_matrix[0][0] = f00;
			m_matrix[0][1] = f01;
			m_matrix[1][0] = f10;
			m_matrix[1][1] = f11;
		};

		inline Matrix2(const Real rEntry[4], bool bRowMajor)
		{
			if(bRowMajor)
			{
				m_matrix[0][0] = rEntry[0];
				m_matrix[0][1] = rEntry[1];
				m_matrix[1][0] = rEntry[2];
				m_matrix[1][1] = rEntry[3];
			}

			else
			{
				m_matrix[0][0] = rEntry[0];
				m_matrix[1][0] = rEntry[1];
				m_matrix[0][1] = rEntry[2];
				m_matrix[1][1] = rEntry[3];
			}
		};

		inline Matrix2(const Vector2& rkU, const Vector2& rkV, bool bColumns)
		{
			if(bColumns)
			{
				m_matrix[0][0] = rkU.x;
				m_matrix[1][0] = rkU.y;
				m_matrix[0][1] = rkV.x;
				m_matrix[1][1] = rkV.y;
			}

			else
			{
				m_matrix[0][0] = rkU.x;
				m_matrix[0][1] = rkU.y;
				m_matrix[1][0] = rkV.x;
				m_matrix[1][1] = rkV.y;
			}
		};

		inline Matrix2(const Vector2* akV, bool bColumns)
		{
			if(bColumns)
			{
				m_matrix[0][0] = akV[0].x;
				m_matrix[1][0] = akV[0].y;
				m_matrix[0][1] = akV[1].x;
				m_matrix[1][1] = akV[1].y;
			}

			else
			{
				m_matrix[0][0] = akV[0].x;
				m_matrix[0][1] = akV[0].y;
				m_matrix[1][0] = akV[0].x;
				m_matrix[1][1] = akV[0].y;
			}
		};

		inline Matrix2(Real f00, Real f11)
		{
			makeDiagonal(f00, f11);
		};

		inline Matrix2(Real fAngle)
		{
			fromAngle(fAngle);
		};

		inline void makeZero()
		{
			m_matrix[0][0] = 0.0;
			m_matrix[0][1] = 0.0;
			m_matrix[1][0] = 0.0;
			m_matrix[1][1] = 0.0;
		};

		inline void makeIdentity()
		{
			m_matrix[0][0] = 1.0;
			m_matrix[0][1] = 0.0;
			m_matrix[1][0] = 0.0;
			m_matrix[1][1] = 1.0;
		};

		inline void makeDiagonal(Real f00, Real f11)
		{
			m_matrix[0][0] = f00;
			m_matrix[0][1] = 0.0;
			m_matrix[1][0] = 0.0;
			m_matrix[1][1] = f11;
		};

		inline void fromAngle(Real fAngle)
		{
			m_matrix[0][0] = Math::Cos(fAngle);
			m_matrix[1][0] = Math::Sin(fAngle);
			m_matrix[0][1] = -m_matrix[1][0];
			m_matrix[1][1] = -m_matrix[0][0];
		};

		inline void makeTensorProduct(const Vector2& rkU, const Vector2& rkV)
		{
			m_matrix[0][0] = rkU.x * rkV.x;
			m_matrix[0][1] = rkU.x * rkV.y;
			m_matrix[1][0] = rkU.y * rkV.x;
			m_matrix[1][1] = rkU.y * rkV.y;
		};

		inline operator const Real* () const
		{
			Real matx[4] = {
				m_matrix[0][0], m_matrix[0][1], 
				m_matrix[1][0], m_matrix[1][1]};;

				return matx; 
		};

		inline operator Real* ()
		{
			Real matx[4] = {
				m_matrix[0][0], m_matrix[0][1], 
				m_matrix[1][0], m_matrix[1][1]};;

				return matx;
		};

		inline const Real* operator[] (int iRow) const
		{
			assert(iRow < 4);

			return m_matrix[iRow];
		};

		inline Real* operator[] (int iRow)
		{
			assert(iRow < 4);

			return m_matrix[iRow];
		};

		inline Real& operator() (int iRow, int iColumn)
		{
			assert(iRow < 2);
			assert(iColumn < 2);

			return m_matrix[iRow][iColumn];
		};

		inline Real operator() (int iRow, int iColumn) const
		{
			assert(iRow < 2);
			assert(iColumn < 2);

			return m_matrix[iRow][iColumn];
		};

		inline void setRow(int iRow, const Vector2& rkV)
		{
			assert(iRow < 2);

			m_matrix[iRow][0] = rkV.x;
			m_matrix[iRow][1] = rkV.y;
		};

		inline Vector2 getRow(int iRow) const
		{
			assert(iRow < 2);

			return Vector2(m_matrix[iRow][0], m_matrix[iRow][1]);
		};	

		inline void setColumn(int iColumn, const Vector2& rkV)
		{
			assert(iColumn < 2);

			m_matrix[0][iColumn] = rkV.x;
			m_matrix[1][iColumn] = rkV.y;
		};

		inline Vector2 getColumn(int iColumn) const
		{
			assert(iColumn < 2);

			return Vector2(m_matrix[0][iColumn], m_matrix[1][iColumn]);
		};

		inline Matrix2& operator= (const Matrix2& rMatrix)
		{
			m_matrix[0][0] = rMatrix[0][0];
			m_matrix[0][1] = rMatrix[0][1];
			m_matrix[1][0] = rMatrix[1][0];
			m_matrix[1][1] = rMatrix[1][1];

			return *this;
		};

		inline bool operator== (const Matrix2& rMatrix) const
		{
			return (
				m_matrix[0][0] == rMatrix[0][0] &&
				m_matrix[0][1] == rMatrix[0][1] &&
				m_matrix[1][0] == rMatrix[1][0] &&
				m_matrix[1][1] == rMatrix[1][1]);
		};

		inline bool operator!= (const Matrix2& rMatrix) const
		{
			return (
				m_matrix[0][0] != rMatrix[0][0] ||
				m_matrix[0][1] != rMatrix[0][1] ||
				m_matrix[1][0] != rMatrix[1][0] ||
				m_matrix[1][1] != rMatrix[1][1]);
		};

		inline Matrix2 operator+ (const Matrix2& rMatrix) const
		{
			return Matrix2(
				m_matrix[0][0] + rMatrix[0][0],
				m_matrix[0][1] + rMatrix[0][1],
				m_matrix[1][0] + rMatrix[1][0],
				m_matrix[1][1] + rMatrix[1][1]
			);
		};

		inline Matrix2 operator- (const Matrix2& rMatrix) const
		{
			return Matrix2(
				m_matrix[0][0] - rMatrix[0][0],
				m_matrix[0][1] - rMatrix[0][1],
				m_matrix[1][0] - rMatrix[1][0],
				m_matrix[1][1] - rMatrix[1][1]
			);
		};

		inline Matrix2 operator* (const Matrix2& rMatrix) const
		{
			return Matrix2(
				m_matrix[0][0] * rMatrix[0][0] + m_matrix[0][1] * rMatrix[1][0],
				m_matrix[0][0] * rMatrix[0][1] + m_matrix[0][1] * rMatrix[1][1],
				m_matrix[1][0] * rMatrix[0][0] + m_matrix[1][1] * rMatrix[1][0],
				m_matrix[1][0] * rMatrix[0][1] + m_matrix[1][1] * rMatrix[1][1]
			);
		};

		inline Matrix2 operator* (Real scalar) const
		{
			return Matrix2(
				m_matrix[0][0] * scalar,
				m_matrix[0][1] * scalar,
				m_matrix[1][0] * scalar,
				m_matrix[1][1] * scalar
				);
		};

		inline Matrix2 operator/ (Real scalar) const
		{
			Real invScalar = 1/scalar;

			return Matrix2(
				m_matrix[0][0] * invScalar,
				m_matrix[0][1] * invScalar,
				m_matrix[1][0] * invScalar,
				m_matrix[1][1] * invScalar
				);
		};

		inline Matrix2 operator- () const
		{
			return Matrix2(
				-m_matrix[0][0],
				-m_matrix[0][1],
				-m_matrix[1][0],
				-m_matrix[1][1]
			);
		};

		inline Matrix2& operator+= (const Matrix2& rMatrix)
		{
			m_matrix[0][0] += rMatrix[0][0];
			m_matrix[0][1] += rMatrix[0][1];
			m_matrix[1][0] += rMatrix[1][0];
			m_matrix[1][1] += rMatrix[1][1];

			return *this;
		};

		inline Matrix2& operator-= (const Matrix2& rMatrix)
		{
			m_matrix[0][0] -= rMatrix[0][0];
			m_matrix[0][1] -= rMatrix[0][1];
			m_matrix[1][0] -= rMatrix[1][0];
			m_matrix[1][1] -= rMatrix[1][1];

			return *this;
		};

		inline Matrix2& operator*= (const Real scalar)
		{
			m_matrix[0][0] *= scalar;
			m_matrix[0][1] *= scalar;
			m_matrix[1][0] *= scalar;
			m_matrix[1][1] *= scalar;

			return *this;
		};

		inline Matrix2& operator/= (const Real scalar)
		{
			m_matrix[0][0] /= scalar;
			m_matrix[0][1] /= scalar;
			m_matrix[1][0] /= scalar;
			m_matrix[1][1] /= scalar;

			return *this;
		};

		inline Vector2 operator* (const Vector2& rkV) const
		{
			return Vector2(
				m_matrix[0][0]*rkV.x + m_matrix[0][1]*rkV.y,
				m_matrix[1][0]*rkV.x + m_matrix[1][1]*rkV.y);
		};

		inline Matrix2 transpose() const
		{
			return Matrix2(
				m_matrix[0][0], m_matrix[1][0],
				m_matrix[0][1], m_matrix[1][1]);
		};

		inline Matrix2 transposeTimes(const Matrix2& rMatrix) const
		{
			return Matrix2(
				m_matrix[0][0]*rMatrix.m_matrix[0][0] + m_matrix[1][0]*rMatrix.m_matrix[1][0],
				m_matrix[0][0]*rMatrix.m_matrix[0][1] + m_matrix[1][0]*rMatrix.m_matrix[1][1],
				m_matrix[0][1]*rMatrix.m_matrix[0][0] + m_matrix[1][1]*rMatrix.m_matrix[1][0],
				m_matrix[0][1]*rMatrix.m_matrix[0][1] + m_matrix[1][1]*rMatrix.m_matrix[1][1]);
		};

		inline Matrix2 timeTranspose(const Matrix2& rMatrix) const
		{
			return Matrix2(
				m_matrix[0][0]*rMatrix.m_matrix[0][0] + m_matrix[0][1]*rMatrix.m_matrix[0][1],
				m_matrix[0][0]*rMatrix.m_matrix[1][0] + m_matrix[0][1]*rMatrix.m_matrix[1][1],
				m_matrix[1][0]*rMatrix.m_matrix[0][0] + m_matrix[1][1]*rMatrix.m_matrix[0][1],
				m_matrix[1][0]*rMatrix.m_matrix[1][0] + m_matrix[1][1]*rMatrix.m_matrix[1][1]);
		};

		inline Matrix2 inverse() const
		{
			Matrix2 inverse;

			Real determinant = m_matrix[0][0] * m_matrix[1][0] - m_matrix[0][1] * m_matrix[1][1];

			if(Math::FAbs(determinant) > Math::ZERO_TOLERANCE)
			{
				inverse[0][0] = m_matrix[1][0] * determinant;
				inverse[0][1] = -m_matrix[0][1] * determinant;
				inverse[1][0] = -m_matrix[1][0] * determinant;
				inverse[1][1] = m_matrix[0][0] * determinant;
			}

			return inverse;
		};

		inline Matrix2 adjoint() const
		{
			return Matrix2(
				m_matrix[1][1],
				-m_matrix[0][1],
				-m_matrix[1][0],
				m_matrix[0][0]);
		};

		inline Real determinant() const
		{
			return m_matrix[0][0] * m_matrix[1][1] - m_matrix[0][1] * m_matrix[1][0];
		};

		inline Real qForm(const Vector2& rkU, const Vector2& rkV) const
		{
			return rkU.dotProduct((*this) * rkV);
		};

		inline void toAngle(Real& fAngle) const
		{
			fAngle = Math::ATan(m_matrix[1][0], m_matrix[0][0]);
		};

		void orthoNormalize();

		GOOD_DLL static const Matrix2 ZERO;
		GOOD_DLL static const Matrix2 IDENTITY;

	private:
		Real m_matrix[2][2];

	};
}
