#include "GLSLProgram.h"
 
#include <fstream>

using namespace Good;

GLSLProgram::GLSLProgram(const char* vertexFile, const char* fragmentFile, const char* geometryFile)
{
	_programID = 0;
	_vertexShaderID = 0;
	_fragmentShaderID = 0;
	_geometryShaderID = 0;
	_isValid = false;

	if (vertexFile == NULL || fragmentFile == NULL)
	{
		_error = "Missing VertexShader File and/or fragmentShader File";
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

	if (!_checkProgramStatus(_programID))
		_isValid = false;

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

std::vector<GLShaderVariable> GLSLProgram::uniforms() const
{
	return _getVariables(GL_ACTIVE_UNIFORMS);
}

std::vector<GLShaderVariable> GLSLProgram::attributes() const
{
	return _getVariables(GL_ACTIVE_ATTRIBUTES);
}

std::string GLSLProgram::error() const
{
	return _error;
}

bool GLSLProgram::isValid() const
{
	return _isValid;
}

GLuint GLSLProgram::_createShader(const char* file, std::string& code, GLenum shaderType)
{
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
	else
	{
		printf("Error openning %s\n", file);
	}

	return shaderID;
}

bool GLSLProgram::_compileShader(GLuint shaderID, std::string& code)
{
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
		char* shaderErrorMessage = new char[infoLogLenght + 1];
		glGetShaderInfoLog(ID, infoLogLenght, NULL, shaderErrorMessage);

		_error += shaderErrorMessage + '\n';
	}

	return result;
}

bool GLSLProgram::_checkProgramStatus(GLuint ID)
{
	GLint result = GL_FALSE;
	int infoLogLenght;

	glGetProgramiv(ID, GL_COMPILE_STATUS, &result);
	glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &infoLogLenght);

	if (infoLogLenght > 0)
	{
		char* shaderErrorMessage = new char[infoLogLenght + 1];
		glGetProgramInfoLog(ID, infoLogLenght, NULL, shaderErrorMessage);

		_error += shaderErrorMessage + '\n';
	}

	return result;
}

std::vector<GLShaderVariable> GLSLProgram::_getVariables(GLenum type) const
{
	std::vector<GLShaderVariable> list;
	int count = 0;
	glGetProgramiv(_programID, type, &count);

	for (int idx = 0; idx < count; ++idx)
	{
		GLenum type;
		GLint size;
		char name[MAX_CHAR];
		glGetActiveUniform(_programID, idx, MAX_CHAR, NULL, &size, &type, name);

		std::tuple<std::string, GLenum> tuple(std::string(name), type);
		list.push_back(tuple);
	}

	return list;
}