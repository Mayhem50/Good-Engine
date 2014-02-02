#pragma once

#include "Vertex.h"
#include "GLSLProgram.h"
#include "IRenderable.h"

#include <GL\glew.h>

#include <vector>

namespace Good
{
	class Mesh : public IRenderable
	{
	public:
		Mesh();
		~Mesh();

		virtual bool init();
		virtual float draw();
		virtual bool shutdown();
#pragma endregion

		VerticesList vertices() const;
		unsigned int addVertex(Vertex& vertex);
				
		void setPosition(const glm::vec3& position);
		void setScale(const glm::vec3& scale);

		glm::mat4 modelMatrix() const;

		void createTriangles(unsigned int tri1, unsigned int tri2, unsigned int tri3);
		void createTriangles(const Vertex& v1, const Vertex& v2, const Vertex& v3);

	private:
		void _createVertexBufferData();
		void _createColorBufferData();
		void _createUVBufferData();
		void _createNormalBufferData();
		void _createIndicesBufferData();

		VerticesList::const_iterator _findVertex(const Vertex& vertex);

		std::vector<unsigned int> _indices;
		VerticesList _vertices;
		glm::mat4 _modelMatrix;

		GLuint _vaoID;
		GLuint _vertexBufferID;
		GLuint _indicesBufferID;

		GLSLProgramPtr _glslProgram;
	};
}
