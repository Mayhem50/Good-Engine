#include "Mesh.h"

#include <algorithm>
#include <time.h>

using namespace Good;

#pragma region Constructors / Destructor
Mesh::Mesh(const std::string& name, const ISceneNodePtr& parent):
ISceneNode(parent, name),
_isIndiced(false),
_cull(true)
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

	//if(_material)
	//	_material->use();

	if(!_cull)
		glDisable(GL_CULL_FACE);

	glBindVertexArray(_vaoID);

	size_t offset = 0;
	
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offset);

	offset += sizeof(_vertices[0].position);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offset);

	offset += sizeof(_vertices[0].color);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offset);

	offset += sizeof(_vertices[0].normal);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offset);

	offset += sizeof(_vertices[0].tangent);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offset);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesBufferID);
	glDrawElements(GL_TRIANGLES, (GLsizei)_indices.size(), GL_UNSIGNED_INT, (void*)0);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	//if(_material)
	//	_material->unuse();

	glEnable(GL_CULL_FACE);

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

MaterialPtr Mesh::material() const
{
	return _material;
}

void Mesh::inverseNormals()
{
	VerticesList::iterator it = _vertices.begin();

	for(; it != _vertices.end(); ++it)
		it->normal = -(it->normal);
}

void Mesh::cullface(bool cull)
{
	_cull = cull;
}

void Mesh::createIndicesBufferData()
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

void Mesh::orienteTriangles()
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
		glm::vec3 edge2 = v3.position - v1.position;

		glm::vec3 normal = glm::cross(edge1, edge2);
		
		TrianglePtr triangle(new Triangle);
		triangle->normal = normal;
		glm::vec3 tangent = glm::cross(glm::normalize(normal), glm::normalize(edge1));
		triangle->tangent = tangent;
		
		v1.triangles.push_back(triangle);
		v2.triangles.push_back(triangle);
		v3.triangles.push_back(triangle);
		
		glm::normalize(edge2);
		float cosT = glm::dot<float>(edge2, tangent);
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

void Mesh::computeNormals()
{
	VerticesList::iterator vtxIt = _vertices.begin();
	for (; vtxIt != _vertices.end(); ++vtxIt)
	{
		TrianglesList::const_iterator triIt = vtxIt->triangles.begin();
		TrianglesList::const_iterator triEnd = vtxIt->triangles.end();
		glm::vec3 normal;
		glm::vec3 tangent;

		for (; triIt != triEnd; ++triIt)
		{
			normal += (*triIt)->normal;
			tangent += (*triIt)->tangent;
		}

		if (normal != glm::vec3(0.0))
			vtxIt->normal = glm::normalize(normal);
		if (tangent != glm::vec3(0.0))
			vtxIt->tangent = glm::normalize(glm::vec3(0.0, 1.0, 1.0));
	}
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
#pragma endregion