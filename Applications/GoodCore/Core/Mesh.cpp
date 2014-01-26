#include "Mesh.h"

#include <algorithm>
#include <time.h>

#include <glm/gtc/matrix_transform.hpp>

using namespace Good;

Mesh::Mesh()
{
	glGenVertexArrays(1, &_vaoID);
}


Mesh::~Mesh()
{
	shutdown();
}

bool Mesh::init()
{
	if (_vertices.empty())
		return false;

	glBindVertexArray(_vaoID);

	_createIndicesBufferData();
	_matrixID = glGetUniformLocation(_glslProgram->programID(), "MVP");

	glGenBuffers(1, &_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_indicesBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

	return true;
}

float Mesh::render(const CameraPtr& camera)
{
	clock_t time = clock();

	glBindVertexArray(_vaoID);

	glm::mat4 MVP = camera->projectionMatrix() * camera->viewMatrix() * _modelMatrix;

	glUseProgram(_glslProgram->programID());
	glUniformMatrix4fv(_matrixID, 1, GL_FALSE, &MVP[0][0]);

	size_t offset = 0;
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offset);

	offset += sizeof(_vertices[0].position);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offset);

	offset += sizeof(_vertices[0].color);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)offset);

	offset += sizeof(_vertices[0].normal);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)offset);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesBufferID);
	glDrawElements(GL_TRIANGLES, (GLsizei)_indices.size(), GL_UNSIGNED_INT, (void*)0);

	glDisableVertexAttribArray(0);

	time = clock() - time;
	return ((float)time) / CLOCKS_PER_SEC; 
}

bool Mesh::shutdown()
{
	return true;
}

std::vector<Vertex> Mesh::vertices() const
{
	return _vertices;
}

unsigned int Mesh::addVertex(Vertex& vertex)
{
	vertex.indice = (unsigned int)_vertices.size();
	_vertices.push_back(vertex);
	//_indices.push_back(vertex->indice);	

	return vertex.indice;
}

void Mesh::setShaders(const char* vertexFile, const char* fragmentFile, const char* geometryFile /*= nullptr*/)
{
	glBindVertexArray(_vaoID);
	setShaders(GLSLProgramPtr(new GLSLProgram(vertexFile, fragmentFile, geometryFile)));
}

void Mesh::setShaders(GLSLProgramPtr program)
{
	_glslProgram = program;
	glBindVertexArray(0);
}

void Mesh::setPosition(const glm::vec3& position)
{
	_modelMatrix = glm::translate(glm::mat4(1.0), position);
}

void Mesh::setScale(const glm::vec3& scale)
{
	glm::vec3 position(_modelMatrix[3][0], _modelMatrix[3][1], _modelMatrix[3][2]);

	_modelMatrix = glm::translate(_modelMatrix, glm::vec3(0.0));
	_modelMatrix = glm::scale(_modelMatrix, scale);
	_modelMatrix = glm::translate(_modelMatrix, position);
}

void Mesh::createTriangles(unsigned int tri1, unsigned int tri2, unsigned int tri3)
{
	_indices.push_back(tri1);
	_indices.push_back(tri2);
	_indices.push_back(tri3);
}

void Mesh::createTriangles(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{	
	/*if (!v1 || !v2 || !v3)
		return;*/

	_indices.push_back(v1.indice);
	_indices.push_back(v2.indice);
	_indices.push_back(v3.indice);
}

std::vector<Vertex>::const_iterator Mesh::_findVertex(const Vertex& vertex)
{
	std::vector<Vertex>::const_iterator it = _vertices.begin();

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
}
