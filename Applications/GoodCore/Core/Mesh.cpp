#include "Mesh.h"

#include <algorithm>
#include <time.h>

using namespace Good;

#pragma region Constructors / Destructor
Mesh::Mesh(const std::string& name, const ISceneNodePtr& parent):
ISceneNode(name, parent)
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

	_createIndicesBufferData();

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
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offset);
	offset += sizeof(_vertices[0].position);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offset);
	offset += sizeof(_vertices[0].color);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offset);
	offset += sizeof(_vertices[0].normal);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offset);


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

void Mesh::createTriangles(unsigned int tri1, unsigned int tri2, unsigned int tri3)
{
	_indices.push_back(tri1);
	_indices.push_back(tri2);
	_indices.push_back(tri3);
}

void Mesh::createTriangles(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{	
	_indices.push_back(v1.indice);
	_indices.push_back(v2.indice);
	_indices.push_back(v3.indice);
}

void Mesh::setMaterial(MaterialPtr material)
{
	_material = material;
}
#pragma endregion

#pragma region Private Methods
VerticesList::const_iterator Mesh::_findVertex(const Vertex& vertex)
{
	VerticesList::const_iterator it = _vertices.begin();

	for (; it != _vertices.end(); ++it)
		if ((*it) == vertex)
			break;

	return it;
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
	_orienteTriangles();
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

		Vertex v1 = _vertices[id1];
		Vertex v2 = _vertices[id2];
		Vertex v3 = _vertices[id3];

		glm::vec3 edge1 = v2.position - v1.position;
		glm::normalize(edge1);
		glm::vec3 edge2 = v3.position - v1.position;
		glm::normalize(edge2);

		glm::vec3 normal = glm::cross(edge1, edge2);
		normal = glm::normalize(normal);
		glm::vec3 tan = glm::cross(normal, edge1);
		tan = glm::normalize(tan);
		float cosT = glm::dot<float>(edge2, tan);

		if (cosT > 0)
		{
			newList.push_back(id1);
			newList.push_back(id2);
			newList.push_back(id3);
		}
		else
		{
			newList.push_back(id1);
			newList.push_back(id3);
			newList.push_back(id2);
		}
	}

	_indices = newList;
}
#pragma endregion