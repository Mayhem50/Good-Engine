#include "Vertex.h"

#include <random>

using namespace Good;

Vertex::Vertex():
position(0.0), normal(0.0),
uv(0.0)
{
	_randomColor();
}

Vertex::Vertex(const Vertex& vertex):
position(vertex.position), normal(vertex.normal),
uv(vertex.uv), color(vertex.color)
{
}

Vertex::Vertex(const Vertex&& vertex):
position(vertex.position), normal(vertex.normal),
uv(vertex.uv), color(vertex.color)
{
}

Vertex::~Vertex()
{}

bool Vertex::operator==(const Vertex& vertex) const
{
	return (position == vertex.position);
}

bool Vertex::operator!=(const Vertex& vertex) const
{
	return !((*this) == vertex);
}

Vertex& Vertex::operator=(const Vertex& vertex)
{
	this->position = vertex.position;
	this->normal = vertex.normal;
	this->uv = vertex.uv;
	this->color = vertex.color;

	return *this;
}

Vertex& Vertex::operator=(const Vertex&& vertex)
{
	this->position = vertex.position;
	this->normal = vertex.normal;
	this->uv = vertex.uv;
	this->color = vertex.color;

	return *this;
}

void Vertex::_randomColor()
{
	std::random_device generator;
	std::uniform_real_distribution<float> distribution(0.0, 1.0);

	color.r = distribution(generator);
	color.g = distribution(generator);
	color.b = distribution(generator);
}
