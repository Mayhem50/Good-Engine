#pragma once

#include "GoodFoundation.h"
#include "IRenderable.h"

#include <memory>
#include <vector>

namespace Good{
	struct Vertex
	{
		Vertex(void);
		~Vertex(void);

		glm::vec3 position;
		glm::vec3 color;
		glm::vec3 normal;
		glm::vec2 uv;

		unsigned int indice;

		bool operator==(const Vertex& vertex) const;
		bool operator!=(const Vertex& vertex) const;

		/*
		glm::vec3 secondaryColor;
		glm::vec3 fogCoord;
		GLBool edgeFlag;*/

	private:
		void _randomColor();
	};

	typedef std::shared_ptr<Vertex> VertexPtr;
	typedef std::vector<Vertex> VerticesList;
}

