#include "UniformBuffer.h"

namespace Good
{
	UniformBuffer::UniformBuffer(GLuint index, GLsizeiptr size, const char* name):
		GoodObject(name),
		_index(index),
		_id(0),
		_size(size)
	{
		glGenBuffers(1, &_id);

		glBindBuffer(GL_UNIFORM_BUFFER, _id);
		glBufferData(GL_UNIFORM_BUFFER, _size, NULL, GL_DYNAMIC_DRAW);
	}

	UniformBuffer::~UniformBuffer()
	{
		glDeleteBuffers(1, &_id);
	}

	bool UniformBuffer::updateData(void* data)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, _index, _id);
		void* cgData = glMapBufferRange(GL_UNIFORM_BUFFER, 0, _size, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
		*(unsigned char*)cgData = *(unsigned char*)data;

		return glUnmapBuffer(GL_UNIFORM_BUFFER);
	}
}