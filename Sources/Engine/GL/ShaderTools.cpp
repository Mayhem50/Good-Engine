#include "ShaderTools.h"

using namespace Good;

std::string ShaderTools::compilerInfos(GLuint id)
{
	std::string log;
	GLint length;

	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
	log.reserve(length + 1);
	glGetShaderInfoLog(id, length, NULL, (GLchar*)log.c_str());

	return log;
}

bool ShaderTools::compileStatus(GLuint id)
{
	GLint ret;
	glGetShaderiv(id, GL_COMPILE_STATUS, &ret);

	if (ret == GL_TRUE)
		return true;

	return false;
}

std::string ShaderTools::linkerInfos(GLuint id)
{
	std::string log;
	GLint length;

	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
	log.reserve(length + 1);
	glGetProgramInfoLog(id, length, NULL, (GLchar*)log.c_str());

	return log;
}

bool ShaderTools::linkStatus(GLuint id)
{
	GLint ret;
	glGetProgramiv(id, GL_LINK_STATUS, &ret);

	if (ret == GL_TRUE)
		return true;

	return false;
}

bool ShaderTools::deleteStatus(GLuint id)
{
	GLint ret;
	glGetProgramiv(id, GL_DELETE_STATUS, &ret);

	if (ret == GL_TRUE)
		return true;

	return false;
}

int ShaderTools::activeAttributes(GLuint id)
{
	GLint ret;
	glGetProgramiv(id, GL_ACTIVE_ATTRIBUTES, &ret);

	return (int)ret;
}

int ShaderTools::activeUniforms(GLuint id)
{
	GLint ret;
	glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &ret);

	return (int)ret;
}

int ShaderTools::activeUniformsBlocks(GLuint id)
{
	GLint ret;
	glGetProgramiv(id, GL_ACTIVE_UNIFORM_BLOCKS, &ret);

	return (int)ret;
}

std::string ShaderTools::vertexShaderHeader()
{
	std::string header;
	header += \
		"#version 430 core\n"\
		"// Input vertex data, different for all executions of this shader.\n"\
		"layout(location = 0) in vec3 vertexPosition;\n"\
		"layout(location = 1) in vec3 vertexColor;\n"\
		"layout(location = 2) in vec3 vertexNormal;\n";
	header += \
		"out vec3 position;\n"
		"out vec3 color;\n"
		"out vec3 normal; \n";
	header +=
		"layout(location = 12) uniform mat4 MVP;\n";

	return header;
}