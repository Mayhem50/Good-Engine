#include "SubMesh.h"

using namespace Good;

SubMesh::SubMesh(const ISceneNodePtr parent, const std::string& name) :
ISceneNode(parent, name),
_isIndiced(false)
{

}

SubMesh::~SubMesh()
{

}

#pragma region Public Methods
VerticesList SubMesh::vertices() const
{
	return _vertices;
}

unsigned int SubMesh::addVertex(Vertex& vertex)
{
	vertex.indice = (unsigned int)_vertices.size();
	_vertices.push_back(vertex);

	return vertex.indice;
}

unsigned int SubMesh::addVertex(const glm::vec3& position)
{
	Vertex vertex;
	vertex.position = position;
	return addVertex(vertex);
}

unsigned int SubMesh::addVertex(float x, float y, float z)
{
	return addVertex(glm::vec3(x, y, z));
}

void SubMesh::createTriangles(unsigned int tri1, unsigned int tri2, unsigned int tri3)
{
	_indices.push_back(tri1);
	_indices.push_back(tri2);
	_indices.push_back(tri3);

	_isIndiced = true;
}

void SubMesh::createTriangles(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
	_vertices.push_back(v1);
	_vertices.push_back(v2);
	_vertices.push_back(v3);
	createTriangles(v1.indice, v2.indice, v3.indice);
}

void SubMesh::setMaterial(MaterialPtr material)
{
	_material = material;
}
#pragma endregion

#pragma region Private Methods
VerticesList::const_iterator SubMesh::_findVertex(const Vertex& vertex)
{
	VerticesList::const_iterator it = _vertices.begin();

	for (; it != _vertices.end(); ++it)
		if ((*it) == vertex)
			break;

	return it;
}

void SubMesh::_createIndicesBufferData()
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

void SubMesh::_orienteTriangles()
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
		triangle->tangent = tan;/*
		v1.triangles.push_back(triangle);
		v2.triangles.push_back(triangle);
		v3.triangles.push_back(triangle);*/

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

void SubMesh::_computeNormals()
{
	VerticesList::iterator vtxIt = _vertices.begin();
	for (; vtxIt != _vertices.end(); ++vtxIt)
	{
		/*TrianglesList::const_iterator triIt = vtxIt->triangles.begin();
		TrianglesList::const_iterator triEnd = vtxIt->triangles.end();
		glm::vec3 normal;

		for (; triIt != triEnd; ++triIt)
			normal += (*triIt)->normal;
		if (normal != glm::vec3(0.0))
			vtxIt->normal = glm::normalize(normal);*/
	}
}
#pragma endregion