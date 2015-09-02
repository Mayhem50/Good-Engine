#include "Mesh.h"

#include <algorithm>
#include <time.h>

using namespace Good;

#pragma region Constructors / Destructor
Mesh::Mesh(const std::string& name, const ISceneNodePtr& parent):
ISceneNode(name, parent),
_isIndiced(false)
{
	glGenVertexArrays(1, &_vaoID);
}

Mesh::Mesh(const VerticesList& vertices, const std::vector<unsigned int>& indices, const std::string& name, const ISceneNodePtr& parent) :
_vertices(vertices), _indices(indices),
ISceneNode(name, parent),
_isIndiced(false)
{
	glGenVertexArrays(1, &_vaoID);
}

Mesh::~Mesh()
{
	shutdown();
}
#pragma endregion

#pragma region IRenderable Interface
bool Mesh::init()
{
	if (_vertices.empty())
		return false;

	glBindVertexArray(_vaoID);

	if (!_isIndiced)
		_createIndicesBufferData();

	//_orienteTriangles();
	//_computeNormals();

	glGenBuffers(1, &_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_indicesBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

	return true;
}

float Mesh::draw()
{
	clock_t time = clock();

	if (_material)
		_material->use();

	glBindVertexArray(_vaoID);

	size_t offset = 0;
	
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offset);
	glEnableVertexAttribArray(0);

	offset += sizeof(_vertices[0].position);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offset);
	glEnableVertexAttribArray(1);

	offset += sizeof(_vertices[0].color);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offset);
	glEnableVertexAttribArray(2);

	offset += sizeof(_vertices[0].normal);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offset);
	glEnableVertexAttribArray(3);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesBufferID);
	glDrawElements(GL_TRIANGLES, (GLsizei)_indices.size(), GL_UNSIGNED_INT, (void*)0);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	time = clock() - time;
	return ((float)time) / CLOCKS_PER_SEC; 
}

bool Mesh::shutdown()
{
	glDeleteBuffers(1, &_indicesBufferID);
	glDeleteBuffers(1, &_vaoID);
	return true;
}
#pragma endregion

#pragma region Public Methods
VerticesList Mesh::vertices() const
{
	return _vertices;
}

unsigned int Mesh::addVertex(Vertex& vertex)
{
	vertex.indice = (unsigned int)_vertices.size();
	_vertices.push_back(vertex);

	return vertex.indice;
}

unsigned int Mesh::addVertex(const glm::vec3& position)
{
	Vertex vertex;
	vertex.position = position;
	return addVertex(vertex);
}

void Mesh::addVertices(const VerticesList& vertices)
{
	for (auto vertex : vertices)
		_vertices.push_back(vertex);
}

void Mesh::addIndices(const std::vector<unsigned int>& indexes)
{
	for (auto index : indexes)
		_indices.push_back(index);
}

void Mesh::setVertices(const VerticesList& vertices)
{
	_vertices = vertices;
}

void Mesh::setIndices(const std::vector<unsigned int> indices)
{
	_indices = indices;
}

void Mesh::createTriangles(unsigned int tri1, unsigned int tri2, unsigned int tri3)
{
	_indices.push_back(tri1);
	_indices.push_back(tri2);
	_indices.push_back(tri3);

	_isIndiced = true;
}

void Mesh::createTriangles(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{	
 	_vertices.push_back(v1);
	_vertices.push_back(v2);
	_vertices.push_back(v3);
	createTriangles(v1.indice, v2.indice, v3.indice);
}

void Mesh::setMaterial(MaterialPtr material)
{
	_material = material;
}
#pragma endregion

#pragma region Private Methods
bool Mesh::_vertexExist(const Vertex& vertex) const
{
	return std::find(_vertices.begin(), _vertices.end(), vertex) != _vertices.end() ? true : false;
}

void Mesh::_createIndicesBufferData()
{
	VerticesList vertices;

	VerticesList::iterator it = _vertices.begin();
	for (; it != _vertices.end(); ++it)
	{
		Vertex vertex;
		VerticesList::const_iterator newIt = vertices.begin();

		for (; newIt != vertices.end(); ++newIt)
		{
			if ((*it) == (*newIt))
			{
				vertex = (*newIt);
				break;
			}
		}

		if (newIt == vertices.end())
		{
			vertex = (*it);
			vertex.indice = (unsigned int)vertices.size();
			vertices.push_back(vertex);
		}

		_indices.push_back(vertex.indice);
	}

	_vertices = vertices;
}

void Mesh::_orienteTriangles()
{
	std::vector<unsigned int>::const_iterator it = _indices.begin();
	std::vector<unsigned int> newList;

	for (; it != _indices.end(); ++it)
	{
		unsigned int id1 = *it;
		++it;
		unsigned int id2 = *it;
		++it;
		unsigned int id3 = *it;

		Vertex& v1 = _vertices[id1];
		Vertex& v2 = _vertices[id2];
		Vertex& v3 = _vertices[id3];

		glm::vec3 edge1 = v2.position - v1.position;
		glm::normalize(edge1);
		glm::vec3 edge2 = v3.position - v1.position;
		glm::normalize(edge2);

		glm::vec3 normal = glm::cross(edge1, edge2);
		if (normal != glm::vec3(0.0))
			glm::normalize(normal);
		glm::vec3 tan = glm::cross(normal, edge1);

		TrianglePtr triangle(new Triangle);
		triangle->normal = normal;
		triangle->tangente = tan;
		v1.triangles.push_back(triangle);
		v2.triangles.push_back(triangle);
		v3.triangles.push_back(triangle);

		float cosT = glm::dot<float>(edge2, tan);
		if (cosT >= 0.0)
		{
			triangle->v1 = (&v1);
			triangle->v2 = (&v2);
			triangle->v3 = (&v3);

			newList.push_back(id1);
			newList.push_back(id2);
			newList.push_back(id3);
		}
		else
		{
			triangle->v1 = (&v1);
			triangle->v2 = (&v3);
			triangle->v3 = (&v2);

			newList.push_back(id1);
			newList.push_back(id3);
			newList.push_back(id2);
		}

		_triangles.push_back(triangle);
	}

	_indices = newList;
}

void Mesh::_computeNormals()
{
	VerticesList::iterator vtxIt = _vertices.begin();
	for (; vtxIt != _vertices.end(); ++vtxIt)
	{
		TrianglesList::const_iterator triIt = vtxIt->triangles.begin();
		TrianglesList::const_iterator triEnd = vtxIt->triangles.end();
		glm::vec3 normal;

		for (; triIt != triEnd; ++triIt)
			normal += (*triIt)->normal;
		if (normal != glm::vec3(0.0))
			vtxIt->normal = glm::normalize(normal);
	}
}
#pragma endregion