#pragma once

#pragma pack(push, 0)

#include "GoodFoundation.h"
#include "IRenderable.h"

#include <memory>
#include <vector>

namespace Good{
	struct GOOD_DLL Vertex
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

	struct Edge
	{
		VertexPtr v1;
		VertexPtr v2;
	};

	typedef std::shared_ptr<Edge> EdgePtr;
	typedef std::vector<Edge> EdgesList;

	struct Triangle
	{
		VertexPtr v1;
		VertexPtr v2;
		VertexPtr v3;

		EdgePtr e1;
		EdgePtr e2;
		EdgePtr e3;
	};

	typedef std::shared_ptr<Triangle> TrianglePtr;
	typedef std::vector<Triangle> TrianglesList;
}

