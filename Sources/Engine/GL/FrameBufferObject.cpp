#include "FrameBufferObject.h"

using namespace Good;

const int FrameBufferObject::DEFAULT_WIDTH = 2048;
const int FrameBufferObject::DEFAULT_HEIGHT = 2048;
const int FrameBufferObject::DEFAULT_LAYER = 1;

FrameBufferObject::FrameBufferObject(GLenum tartget, int colorAttachementCount, int width, int height, int layers, int mipmap, bool shadowMap) :
_width(width),
_height(height),
_layers(layers),
_mipmap(mipmap),
_target(tartget),
_shadowmap(shadowMap),
_colorAttachementCount(colorAttachementCount)
{
	if (_width < 0)
		_width = DEFAULT_WIDTH;
	if (_height < 0)
		_height = DEFAULT_HEIGHT;

	_isValid = _init();
}

FrameBufferObject::~FrameBufferObject()
{
	glDeleteTextures(_colorAttachementCount, _colorTex);
	glDeleteTextures(1, &_depthTex);
	glDeleteFramebuffers(1, &_frameBufferID);
}

bool FrameBufferObject::_init()
{
	if (_colorAttachementCount > GL_MAX_COLOR_ATTACHMENTS)
		return false;

	_colorTex = new GLuint[_colorAttachementCount];
	GLuint *drawBuffers = new GLuint[_colorAttachementCount];

	glGenFramebuffers(1, &_frameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferID);
	
	for (int idx = 0; idx < _colorAttachementCount; ++idx)
	{
		glGenTextures(1, &_colorTex[idx]);
		glBindTexture(_target, _colorTex[idx]);
		
		if (_target == GL_TEXTURE_1D)
			glTexStorage1D(_target, _mipmap + 1, GL_RGBA32F, _width);
		else if (_target == GL_TEXTURE_2D)
			glTexStorage2D(_target, _mipmap + 1, GL_RGBA32F, _width, _height);
		else if (_target == GL_TEXTURE_3D)
			glTexStorage3D(_target, _mipmap + 1, GL_RGBA32F, _width, _height, _layers);

		glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glBindTexture(_target, 0);

		drawBuffers[idx] = GL_COLOR_ATTACHMENT0 + idx;

		if(_target == GL_TEXTURE_1D)
			glFramebufferTexture1D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + idx, GL_TEXTURE_2D, _colorTex[idx], _mipmap);
		else if(_target == GL_TEXTURE_2D)
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + idx, GL_TEXTURE_2D, _colorTex[idx], _mipmap);
		else if (_target == GL_TEXTURE_3D)
			glFramebufferTexture3D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + idx, GL_TEXTURE_3D, _colorTex[idx], _mipmap, _layers);
	}

	glGenTextures(1, &_depthTex);
	glBindTexture(_target, _depthTex);

	if (_target == GL_TEXTURE_1D)
		glTexStorage1D(_target, _mipmap + 1, GL_DEPTH_COMPONENT32F, _width);
	else if (_target == GL_TEXTURE_2D)
		glTexStorage2D(_target, _mipmap + 1, GL_DEPTH_COMPONENT32F, _width, _height);
	else if (_target == GL_TEXTURE_3D)
		glTexStorage3D(_target, _mipmap + 1, GL_DEPTH_COMPONENT32F, _width, _height, _layers);

	if(_shadowmap)
	{
		glTexParameteri(_target, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
		glTexParameteri(_target, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	}

	glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(_target, 0);
	
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _depthTex, _mipmap);
	glDrawBuffers(_colorAttachementCount, drawBuffers);

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

GLuint FrameBufferObject::buffer(int index) const
{
	if (index >= _colorAttachementCount)
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