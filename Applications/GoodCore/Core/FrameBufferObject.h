#pragma once

#include <GL\glew.h>

#include <memory>

namespace Good
{
	class FrameBufferObject
	{
	public:
		FrameBufferObject();
		FrameBufferObject(int width, int height);
		~FrameBufferObject();

		GLuint fboID() const;
		GLuint textureID() const;

		bool isValid() const;

		void bind();
		void unbind();

	private:
		bool _init();

		GLuint _frameBufferID;
		GLuint _depthBufferID;
		GLuint _texID;

		GLenum _drawBuffer;

		int _width;
		int _height;

		bool _isValid;

		static const int DEFAULT_WIDTH;
		static const int DEFAULT_HEIGHT;
	};

	typedef std::shared_ptr<FrameBufferObject> FrameBufferObjectPtr;
}