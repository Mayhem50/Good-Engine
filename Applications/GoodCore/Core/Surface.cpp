#include "Surface.h"

#include "Material.h"

#include <algorithm>
#include <time.h>

namespace Good
{

	Surface::Surface(const std::string& name, const ISceneNodePtr& parent) :
		ISceneNode(name, parent),
		_isIndiced(false)
	{
		glGenVertexArrays(1, &_vaoID);
	}

	Surface::Surface(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::vector<unsigned int>& indices, const std::string& name, const ISceneNodePtr& parent) :
		_vertices(vertices), _indices(indices),
		ISceneNode(name, parent),
		_isIndiced(false)
	{
		glGenVertexArrays(1, &_vaoID);
	}

	Surface::~Surface()
	{
		shutdown();
	}

	bool Surface::init()
	{
		if (_vertices.empty())
			return false;

		glBindVertexArray(_vaoID);

		/*if (!_isIndiced)
			_createIndicesBufferData();*/

		//_orienteTriangles();
		//_computeNormals();

		glGenBuffers(1, &_vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);
		glGenBuffers(1, &_normalBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, _normalBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _normals.size(), &_normals[0], GL_STATIC_DRAW);
		glGenBuffers(1, &_uvBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, _uvBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * _uvs.size(), &_uvs[0], GL_STATIC_DRAW);

		glGenBuffers(1, &_indicesBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

		glBindVertexArray(0);

		return true;
	}

	float Surface::draw()
	{
		clock_t time = clock();

		glBindVertexArray(_vaoID);

		size_t offset = 0;

		glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)offset);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, _normalBufferID);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)offset);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, _uvBufferID);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)offset);
		glEnableVertexAttribArray(2);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesBufferID);
		glDrawElements(GL_TRIANGLES, (GLsizei)_indices.size(), GL_UNSIGNED_INT, (void*)0);

		glDisableVertexAttribArray(0);
		glBindVertexArray(0);

		time = clock() - time;
		return ((float)time) / CLOCKS_PER_SEC;
	}

	bool Surface::shutdown()
	{
		glDeleteBuffers(1, &_indicesBufferID);
		glDeleteBuffers(1, &_vertexBufferID);
		glDeleteBuffers(1, &_normalBufferID);
		glDeleteBuffers(1, &_uvBufferID);
		glDeleteBuffers(1, &_vaoID);
		return true;
	}

	const std::vector<glm::vec3>&  Surface::vertices() const
	{
		return _vertices;
	}

	const std::vector<glm::vec3>&  Surface::normals() const
	{
		return _normals;
	}

	const std::vector<glm::vec2>&  Surface::uvs() const
	{
		return _uvs;
	}

	const std::vector<unsigned int>&  Surface::indices() const
	{
		return _indices;
	}

	std::vector<glm::vec3>&  Surface::vertices()
	{
		return _vertices;
	}

	std::vector<glm::vec3>&  Surface::normals()
	{
		return _normals;
	}

	std::vector<glm::vec2>&  Surface::uvs()
	{
		return _uvs;
	}

	std::vector<unsigned int>&  Surface::indices()
	{
		return _indices;
	}
	
	void Surface::addVertex(const glm::vec3& vertex)
	{
		auto itVtx = std::find(_vertices.begin(), _vertices.end(), vertex);
		if (itVtx == _vertices.end())
			_vertices.push_back(vertex);
	}

	void Surface::addNormal(const glm::vec3& normal)
	{
		auto itNml = std::find(_normals.begin(), _normals.end(), normal);
		if (itNml == _normals.end())
			_normals.push_back(normal);
	}

	void Surface::addUV(const glm::vec2& uv)
	{
		auto itUV = std::find(_uvs.begin(), _uvs.end(), uv);
		if (itUV == _uvs.end())
			_uvs.push_back(uv);
	}

	void Surface::addIndice(const unsigned int indice)
	{
		_indices.push_back(indice);
	}

	void Surface::addVertices(const glm::vec3* vertices, unsigned int size)
	{
		for (unsigned int idx = 0; idx < size; ++idx)
			addVertex(vertices[idx]);
	}

	void Surface::addVertices(const std::vector<glm::vec3>& vertices)
	{
		for (auto vertex : vertices)
			addVertex(vertex);
	}

	void Surface::addNormals(const glm::vec3* normals, unsigned int size)
	{
		for (unsigned int idx = 0; idx < size; ++idx)
			addNormal(normals[idx]);
	}

	void Surface::addNormals(const std::vector<glm::vec3>& normals)
	{
		for (auto normal : normals)
			addNormal(normal);
	}

	void Surface::addUVs(const glm::vec2* uvs, unsigned int size)
	{
		for (unsigned int idx = 0; idx < size; ++idx)
			addUV(uvs[idx]);
	}

	void Surface::addUVs(const std::vector<glm::vec2>& uvs)
	{
		for (auto uv : uvs)
			addUV(uv);
	}

	void Surface::addIndices(const unsigned int* indices, unsigned int size)
	{
		for (unsigned int idx = 0; idx < size; ++idx)
			addIndice(indices[idx]);
	}

	void Surface::addIndices(const std::vector<unsigned int>& indices)
	{
		for (auto indice : indices)
			addIndice(indice);
	}

	void Surface::setMaterial(MaterialPtr material)
	{
		_material = material;
	}

	MaterialPtr Surface::material() const
	{
		return _material;
	}
}