#pragma once

#include "../GraphScene/ISceneNode.h"
#include "../Material/Material.h"

#include "Vertex.h"

#include <GL\glew.h>

#include <vector>
#include <memory>

namespace Good
{
	class GOOD_DLL SubMesh : public ISceneNode
	{
	public:
		SubMesh(const ISceneNodePtr parent, const std::string& name);
		~SubMesh();

		VerticesList vertices() const;
		unsigned int addVertex(Vertex& vertex);
		unsigned int addVertex(const glm::vec3& postion);
		unsigned int addVertex(float x, float y, float z);

		void createTriangles(unsigned int tri1, unsigned int tri2, unsigned int tri3);
		void createTriangles(const Vertex& v1, const Vertex& v2, const Vertex& v3);

		void setMaterial(MaterialPtr material);

	protected:
		void _createVertexBufferData();
		void _createIndicesBufferData();
		void _orienteTriangles();
		void _computeNormals();

		VerticesList::const_iterator _findVertex(const Vertex& vertex);

		VerticesList _vertices;
		EdgesList _edges;
		TrianglesList _triangles;
		std::vector<unsigned int> _indices;
		bool _isIndiced;

		MaterialPtr _material;
	};

	typedef std::shared_ptr<SubMesh> SubMeshPtr;
	typedef std::vector<SubMeshPtr> SubMeshesList;
}
