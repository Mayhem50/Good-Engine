#include "GLSLProgram.h"

#ifdef _DEBUG

#endif

#include <fstream>

using namespace Good;

GLSLProgram::GLSLProgram(const char* vertexFile, const char* fragmentFile, const char* geometryFile)
{
#ifdef _DEBUG
	
#endif
	_programID = 0;
	_vertexShaderID = 0;
	_fragmentShaderID = 0;
	_geometryShaderID = 0;
	_isValid = false;

	if (vertexFile == NULL || fragmentFile == NULL)
	{
		_log = "Missing VertexShader File and/or fragmentShader File";
		return;
	}

	std::string vertexCode, fragmentCode, geometryCode;

	_vertexShaderID = _createShader(vertexFile, vertexCode, GL_VERTEX_SHADER);
	_fragmentShaderID = _createShader(fragmentFile, fragmentCode, GL_FRAGMENT_SHADER);

	if (_compileShader(_vertexShaderID, vertexCode) && _compileShader(_fragmentShaderID, fragmentCode))
	{
		_programID = glCreateProgram();
		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);

	}

	if (geometryFile != NULL)
	{
		_geometryShaderID = _createShader(geometryFile, geometryCode, GL_GEOMETRY_SHADER);

		if (_compileShader(_geometryShaderID, geometryCode))
			glAttachShader(_programID, _geometryShaderID);
	}

	glLinkProgram(_programID);

	if (_checkProgramStatus(_programID))
		_isValid = true;
	
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
	if (geometryFile != NULL)
		glDeleteShader(_geometryShaderID);
}

GLSLProgram::~GLSLProgram()
{
	glDeleteProgram(_programID);
}

GLuint GLSLProgram::programID() const
{
	return _programID;
}

GLuint GLSLProgram::vertexShaderID() const
{
	return _vertexShaderID;
}

GLuint GLSLProgram::fragmentShaderID() const
{
	return _fragmentShaderID;
}

GLuint GLSLProgram::geometryShaderID() const
{
	return _geometryShaderID;
}

ShaderVariablesList GLSLProgram::uniforms() const
{
	return _getVariables(GL_ACTIVE_UNIFORMS);
}

ShaderVariablesList GLSLProgram::attributes() const
{
	return _getVariables(GL_ACTIVE_ATTRIBUTES);
}

std::string GLSLProgram::log() const
{
	return _log;
}

bool GLSLProgram::isValid() const
{
	return _isValid;
}

GLuint GLSLProgram::_createShader(const char* file, std::string& code, GLenum shaderType)
{
#ifdef _DEBUG
	
#endif

	if (file == NULL)
		return 0;

	GLuint shaderID = glCreateShader(shaderType);

	std::ifstream stream(file, std::ios::in);

	if (stream.is_open())
	{
		std::string line = "";
		while (getline(stream, line))
			code += "\n" + line;

		stream.close();
	}

	return shaderID;
}

bool GLSLProgram::_compileShader(GLuint shaderID, std::string& code)
{
#ifdef _DEBUG
	
#endif

	char const * sourcePointer = code.c_str();
	glShaderSource(shaderID, 1, &sourcePointer, NULL);
	glCompileShader(shaderID);

	return _checkShaderStatus(shaderID);
}

bool GLSLProgram::_checkShaderStatus(GLuint ID)
{
	GLint result = GL_FALSE;
	int infoLogLenght;

	glGetShaderiv(ID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &infoLogLenght);

	if (infoLogLenght > 0)
	{
		char* shaderMessage = new char[infoLogLenght + 1];
		glGetShaderInfoLog(ID, infoLogLenght, NULL, shaderMessage);

#ifdef _DEBUG
		
#endif

		_log += shaderMessage + '\n';
	}

	return (bool)result;
}

bool GLSLProgram::_checkProgramStatus(GLuint ID)
{
	GLint result = GL_FALSE;
	int infoLogLenght;

	glGetProgramiv(ID, GL_COMPILE_STATUS, &result);
	glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &infoLogLenght);

	if (infoLogLenght > 0)
	{
		char* shaderMessage = new char[infoLogLenght + 1];
		glGetProgramInfoLog(ID, infoLogLenght, NULL, shaderMessage);

#ifdef _DEBUG
		
#endif

		_log += shaderMessage + '\n';
	}

	return (bool)result;
}

ShaderVariablesList GLSLProgram::_getVariables(GLenum type) const
{
#ifdef _DEBUG
	
#endif

	ShaderVariablesList list;
	int count = 0;
	glGetProgramiv(_programID, type, &count);

	for (int idx = 0; idx < count; ++idx)
	{
		GLenum varType;
		GLint size;
		GLsizei lenght;
		char name[MAX_CHAR];
		switch (type)
		{
		case GL_ACTIVE_UNIFORMS:
			glGetActiveUniform(_programID, idx, MAX_CHAR, &lenght, &size, &varType, name);
			break;
		case GL_ACTIVE_ATTRIBUTES:
			glGetActiveAttrib(_programID, idx, MAX_CHAR, &lenght, &size, &varType, name);
		}

		ShaderVariable variable(std::string(name), varType);
		list.push_back(variable);
	}

	return list;
}