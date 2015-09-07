#pragma once

#include "IRenderable.h"
#include "ISceneNode.h"

#include "Material.h"

#include <GL\glew.h>

#include <vector>
#include <memory>

namespace Good
{
	class GOOD_DLL Surface : public ISceneNode, public IRenderable
	{
	public:
		Surface(const std::string& name, const ISceneNodePtr& parent);
		Surface(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::vector<unsigned int>& indices, const std::string& name, const ISceneNodePtr& parent);
		~Surface();

		virtual bool init();
		virtual float draw();
		virtual bool shutdown();

		const std::vector<glm::vec3>&  vertices() const;
		const std::vector<glm::vec3>&  normals() const;
		const std::vector<glm::vec2>&  uvs() const;
		const std::vector<unsigned int>&  indices() const;
		std::vector<glm::vec3>&  vertices();
		std::vector<glm::vec3>&  normals();
		std::vector<glm::vec2>&  uvs();
		std::vector<unsigned int>&  indices();

		void addVertex(const glm::vec3& postion);
		void addNormal(const glm::vec3& normal);
		void addUV(const glm::vec2& uv);
		void addIndice(const unsigned int indice);

		void addVertices(const glm::vec3* vertices, unsigned int size);
		void addVertices(const std::vector<glm::vec3>& vertices);
		void addNormals(const glm::vec3* normals, unsigned int size);
		void addNormals(const std::vector<glm::vec3>& normals);
		void addUVs(const glm::vec2* uvs, unsigned int size);
		void addUVs(const std::vector<glm::vec2>& uvs);

		void addIndices(const unsigned int* indices, unsigned int size);
		void addIndices(const std::vector<unsigned int>& indices);

		void setMaterial(MaterialPtr material);
		MaterialPtr material() const;

	private:		
		std::vector<unsigned int> _indices;
		std::vector<glm::vec3> _vertices;
		std::vector<glm::vec3> _normals;
		std::vector<glm::vec2> _uvs;
		
		GLuint _vaoID;
		GLuint _vertexBufferID;
		GLuint _normalBufferID;
		GLuint _uvBufferID;
		GLuint _indicesBufferID;

		bool _isIndiced;

		MaterialPtr _material;
	};

	typedef std::shared_ptr<Surface> SurfacePtr;
}
