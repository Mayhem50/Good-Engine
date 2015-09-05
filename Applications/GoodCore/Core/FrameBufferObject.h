#pragma once

#include "GoodFoundation.h"

#include <GL\glew.h>

#include <memory>

namespace Good
{
	class GOOD_DLL FrameBufferObject
	{
	public:
		FrameBufferObject(unsigned int colorBufferCount);
		FrameBufferObject(unsigned int colorBufferCount, int width, int height);
		~FrameBufferObject();

		GLuint id() const;
		GLuint colorBuffer(unsigned int index) const;
		GLuint depthBuffer() const;

		bool isValid() const;

		void bind();
		void unbind();

	private:
		bool _init();

		GLuint _frameBufferID;
		GLuint* _colorTex;
		GLuint _depthTex;

		GLuint* _drawBuffer;

		int _width;
		int _height;

		bool _isValid;
		unsigned int _colorBufferCount;

		static const int DEFAULT_WIDTH;
		static const int DEFAULT_HEIGHT;
	};

	typedef std::shared_ptr<FrameBufferObject> FrameBufferObjectPtr;
}