#pragma once

#include <GL\glew.h>

#include <string>

namespace Good
{
	namespace ShaderTools
	{
		std::string compilerInfos(GLuint id);
		bool compileStatus(GLuint id);
		std::string linkerInfos(GLuint id);
		bool linkStatus(GLuint id);
		bool deleteStatus(GLuint id);

		int activeAttributes(GLuint id);
		int activeUniforms(GLuint id);
		int activeUniformsBlocks(GLuint id);

		int attachedShaders(GLuint id);

		std::string vertexShaderHeader();
		std::string fragmentShaderHeader();
	}
}