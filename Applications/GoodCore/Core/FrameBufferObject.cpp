#include "FrameBufferObject.h"

using namespace Good;

const int FrameBufferObject::DEFAULT_WIDTH = 2048;
const int FrameBufferObject::DEFAULT_HEIGHT = 2048;

FrameBufferObject::FrameBufferObject(unsigned int colorBufferCount) :
_width(DEFAULT_WIDTH),
_height(DEFAULT_HEIGHT), 
_colorBufferCount(colorBufferCount)
{
	_isValid = _init();
}

FrameBufferObject::FrameBufferObject(unsigned int colorBufferCount, int width, int height) :
_width(width),
_height(height), 
_colorBufferCount(colorBufferCount)
{
	if (_width < 0)
		_width = DEFAULT_WIDTH;
	if (_height < 0)
		_height = DEFAULT_HEIGHT;

	_isValid = _init();
}

FrameBufferObject::~FrameBufferObject()
{
	glDeleteTextures(_colorBufferCount, _colorTex);
	glDeleteTextures(1, &_depthTex);
	glDeleteFramebuffers(1, &_frameBufferID);
	delete[] _colorTex;
	delete[] _drawBuffer;
}

bool FrameBufferObject::_init()
{
	glGenFramebuffers(1, &_frameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferID);

	_colorTex = new GLuint[_colorBufferCount];
	glGenTextures(_colorBufferCount, _colorTex);

	for (unsigned int idx = 0; idx < _colorBufferCount; ++idx)
	{
		glBindTexture(GL_TEXTURE_2D, _colorTex[idx]);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, _width, _height);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	//glGenRenderbuffers(1, &_depthBufferID);
	//glBindRenderbuffer(GL_RENDERBUFFER, _depthBufferID);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _width, _height);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthBufferID);

	glGenTextures(1, &_depthTex);
	glBindTexture(GL_TEXTURE_2D, _depthTex);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32F, _width, _height);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	for (unsigned int idx = 0; idx < _colorBufferCount; ++idx)
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + idx, _colorTex[idx], 0);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _depthTex, 0);

	_drawBuffer = new GLuint[_colorBufferCount];

	for (unsigned int idx = 0; idx < _colorBufferCount; ++idx)
		_drawBuffer[idx] = GL_COLOR_ATTACHMENT0 + idx;

	glDrawBuffers(_colorBufferCount, _drawBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
		return true;
	else
		return false;
}

bool FrameBufferObject::isValid() const
{
	return _isValid;
}

GLuint FrameBufferObject::id() const
{
	return _frameBufferID;
}

GLuint FrameBufferObject::colorBuffer(unsigned int index) const
{
	if (index >= _colorBufferCount)
		return 0;

	return _colorTex[index];
}

GLuint FrameBufferObject::depthBuffer() const
{
	return _depthTex;
}

void FrameBufferObject::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferID);
	glViewport(0, 0, _width, _height);
}

void FrameBufferObject::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}