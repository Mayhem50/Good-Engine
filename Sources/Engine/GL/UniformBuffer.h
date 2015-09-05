#pragma once

#include "../Core/GoodObject.h"

#include <GL/glew.h>

namespace Good
{
	class UniformBuffer : public GoodObject
	{
	public:
		UniformBuffer(GLuint index, GLsizeiptr size, const char* name = nullptr);
		~UniformBuffer();
		
		bool updateData(void* data);

	private:
		GLuint _index;
		GLuint _id;
		GLsizeiptr _size;
	};
}