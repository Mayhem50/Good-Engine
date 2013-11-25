#pragma once

#include "../Math/Vectors.h"

namespace Good{
	struct Vertex
	{
		Vertex(void):
			position(Vector3::ZERO),
			texture(Vector2::ZERO),
			normal(Vector3::ZERO),
			indice(0)
		{}

		Vertex(const Vector3& position_, const Vector2& texture_, const Vector3& normal_, double indice_):
			position(position_),
			texture(texture_),
			normal(normal_),
			indice(indice_)
		{}

		~Vertex(void){}

		Vector3 position;
		Vector2 texture;
		Vector3 normal;
		Real indice;
	};
}

