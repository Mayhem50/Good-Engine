#pragma once

#include "GoodFoundation.h"
#include "GoodObject.h"

#ifdef _DEBUG
#include "Ilogger.h"
#endif

#include <vector>
#include <tuple>
#include <string>

#include <memory>

#include <GL\glew.h>

namespace Good
{
	typedef std::tuple<std::string, GLenum> ShaderVariable;
	typedef std::vector<ShaderVariable> ShaderVariablesList;

	class GOOD_DLL GLSLProgram : public GoodObject
	{
	public:
		GLSLProgram(const char* vertexFile, const char* fragmentFile, const char* geometryFile = NULL);
		~GLSLProgram();
		
		GLuint programID() const;
		GLuint vertexShaderID() const;
		GLuint fragmentShaderID() const;
		GLuint geometryShaderID() const;

		ShaderVariablesList uniforms() const;
		ShaderVariablesList attributes() const;

		std::string log() const;

		bool isValid() const;

	private:
		GLuint _createShader(const char* file, std::string& code, GLenum shaderType);
		bool _compileShader(GLuint shaderID, std::string& code);
		bool _checkShaderStatus(GLuint ID);
		bool _checkProgramStatus(GLuint ID);
		ShaderVariablesList _getVariables(GLenum type) const;

		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
		GLuint _geometryShaderID;

		bool _isValid;

		std::string _log;

#ifdef _DEBUG
		ILoggerPtr _logger;
#endif
	};

	typedef std::shared_ptr<GLSLProgram> GLSLProgramPtr;
}