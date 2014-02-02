#include "FrameBufferObject.h"

using namespace Good;

const int FrameBufferObject::DEFAULT_WIDTH = 2048;
const int FrameBufferObject::DEFAULT_HEIGHT = 2048;

FrameBufferObject::FrameBufferObject() :
_width(DEFAULT_WIDTH),
_height(DEFAULT_HEIGHT)
{
	_isValid = _init();
}

FrameBufferObject::FrameBufferObject(int width, int height):
_width(width),
_height(height)
{
	if (_width < 0)
		_width = DEFAULT_WIDTH;
	if (_height < 0)
		_height = DEFAULT_HEIGHT;

	_isValid = _init();
}

FrameBufferObject::~FrameBufferObject()
{
	glDeleteTextures(1, &_texID);
	glDeleteFramebuffers(1, &_depthBufferID);
	glDeleteFramebuffers(1, &_frameBufferID);
}

bool FrameBufferObject::_init()
{
	glGenFramebuffers(1, &_frameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferID);

	glGenTextures(1, &_texID);
	glBindTexture(GL_TEXTURE_2D, _texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glGenRenderbuffers(1, &_depthBufferID);
	glBindRenderbuffer(GL_RENDERBUFFER, _depthBufferID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _width, _height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthBufferID);
	
	_drawBuffer = GL_COLOR_ATTACHMENT0;
	glFramebufferTexture(GL_FRAMEBUFFER, _drawBuffer, _texID, 0);
	glDrawBuffers(1, &_drawBuffer);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
		return true;
	else
		return false;
}

bool FrameBufferObject::isValid() const
{
	return _isValid;
}

GLuint FrameBufferObject::fboID() const
{
	return _frameBufferID;
}

GLuint FrameBufferObject::textureID() const
{
	return _texID;
}

void FrameBufferObject::bind()
{
	glBindTexture(GL_TEXTURE_2D, _texID);
	glActiveTexture(GL_TEXTURE0);

	glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferID);
	glViewport(0, 0, _width, _height);
}

void FrameBufferObject::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}