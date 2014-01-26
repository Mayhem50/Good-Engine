#pragma once

#include "GoodFoundation.h"

#include <vector>
#include <tuple>
#include <string>

#include <memory>

#include <GL\glew.h>

namespace Good
{
	typedef std::tuple<std::string, GLenum> GLShaderVariable;
	class GOOD_DLL GLSLProgram
	{
	public:
		GLSLProgram(const char* vertexFile, const char* fragmentFile, const char* geometryFile = NULL);
		~GLSLProgram();
		
		GLuint programID() const;
		GLuint vertexShaderID() const;
		GLuint fragmentShaderID() const;
		GLuint geometryShaderID() const;

		std::vector<GLShaderVariable> uniforms() const;
		std::vector<GLShaderVariable> attributes() const;

		std::string error() const;

		bool isValid() const;

	private:
		GLuint _createShader(const char* file, std::string& code, GLenum shaderType);
		bool _compileShader(GLuint shaderID, std::string& code);
		bool _checkShaderStatus(GLuint ID);
		bool _checkProgramStatus(GLuint ID);
		std::vector<GLShaderVariable> _getVariables(GLenum type) const;

		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
		GLuint _geometryShaderID;

		bool _isValid;

		std::string _error;
	};

	typedef std::shared_ptr<GLSLProgram> GLSLProgramPtr;
}