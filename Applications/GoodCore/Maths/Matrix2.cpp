#include "Matrix2.h"

using namespace Good;

const Matrix2 Matrix2::ZERO(0.0, 0.0, 0.0, 0.0);
const Matrix2 Matrix2::IDENTITY(1.0, 0.0, 0.0, 1.0);

void Matrix2::orthoNormalize()
{
	Real invLenght = Math::InvSqrt(m_matrix[0][0] * m_matrix[0][0] + m_matrix[1][0] * m_matrix[1][0]);

	m_matrix[0][0] *= invLenght;
	m_matrix[1][0] *= invLenght;

	Real dot0 = (m_matrix[0][0] * m_matrix[0][1] + m_matrix[1][0] * m_matrix[1][1]);

	m_matrix[0][1] -= dot0 * m_matrix[0][0];
	m_matrix[1][1] -= dot0 * m_matrix[1][0];

	invLenght = Math::InvSqrt(m_matrix[0][1] * m_matrix[0][1] + m_matrix[1][1] * m_matrix[1][1]);

	m_matrix[0][1] *= invLenght;
	m_matrix[1][1] *= invLenght;
}

