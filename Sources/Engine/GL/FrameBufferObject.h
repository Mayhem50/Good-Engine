#pragma once

#include "../Core/GoodFoundation.h"

#include <GL\glew.h>

#include <memory>

namespace Good
{
	class GOOD_DLL FrameBufferObject
	{
	public:
		FrameBufferObject(GLenum tartget, int colorAttachementCount, int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT, int layer = DEFAULT_LAYER, int mipmap = 0, bool shadowMap = false);
		~FrameBufferObject();

		GLuint id() const;
		GLuint buffer(int index = 0) const;
		GLuint depthBuffer() const;

		bool isValid() const;

		void bind();
		void unbind();

	private:
		bool _init();

		GLuint _frameBufferID;
		GLuint* _colorTex;
		GLuint _depthTex;

		GLenum _drawBuffer;
		GLenum _target;

		int _width;
		int _height;
		int _layers;

		int _mipmap;
		int _colorAttachementCount;

		bool _shadowmap;

		bool _isValid;

		static const int DEFAULT_WIDTH;
		static const int DEFAULT_HEIGHT;
		static const int DEFAULT_LAYER;
	};

	typedef std::shared_ptr<FrameBufferObject> FrameBufferObjectPtr;
}