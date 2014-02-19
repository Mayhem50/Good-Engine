#pragma once

#include "GoodFoundation.h"

#include <GL\glew.h>

#include <memory>

namespace Good
{
	class GOOD_DLL FrameBufferObject
	{
	public:
		FrameBufferObject();
		FrameBufferObject(int width, int height);
		~FrameBufferObject();

		GLuint id() const;
		GLuint colorBuffer() const;
		GLuint normalBuffer() const;
		GLuint depthBuffer() const;

		bool isValid() const;

		void bind();
		void unbind();

	private:
		bool _init();

		GLuint _frameBufferID;
		GLuint _colorTex;
		GLuint _normalTex;
		GLuint _depthTex;

		GLenum _drawBuffer;

		int _width;
		int _height;

		bool _isValid;

		static const int DEFAULT_WIDTH;
		static const int DEFAULT_HEIGHT;
	};

	typedef std::shared_ptr<FrameBufferObject> FrameBufferObjectPtr;
}