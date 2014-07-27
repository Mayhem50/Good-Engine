#include "Viewport.h"

#include <GL\glew.h>

using namespace Good;

Viewport::Viewport() :
_x(0), _y(0), _width(640), _height(480)
{
	_updateViewport();
}

Viewport::Viewport(int x, int y, int width, int height) :
_x(x), _y(y), _width(width), _height(height)
{
	_updateViewport();
}

Viewport::~Viewport()
{

}

void Viewport::set(int x, int y, int width, int height)
{
	_x = x; _y = y;
	_width = width; _height = height;
	_updateViewport();
}

float Viewport::aspect() const
{
	return (float)_width / (float)_height;
}

int Viewport::X() const
{
	return _x;
}

int Viewport::Y() const
{
	return _y;
}

int Viewport::width() const
{
	return _width;
}

int Viewport::height() const
{
	return _height;
}

void Viewport::_updateViewport()
{
	glViewport(_x, _y, (GLsizei)_width, (GLsizei)_height);
}
