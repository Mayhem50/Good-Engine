#include "ShaderProgram.h"

#include "ShaderTools.h"
#include "ShaderPipeline.h"

#include <fstream>

using namespace Good;

const ShaderProgramPtr ShaderProgram::EMPY_PROGRAM = ShaderProgramPtr(nullptr);

ShaderProgram::ShaderProgram(ShaderPipelinePtr pipeline, const char* file, GLenum type, const char* name) :
GoodObject(name),
_pipeline(pipeline),
_isValid(false), 
_type(type)
{
#ifdef _DEBUG
	_logger = ILoggerPtr(new LogConsole);
	_logger->write("Create", this);
#endif

	if (!file)
	{
#ifdef _DEBUG
	_logger->write("No file path", this);
#endif

		return;
	}

	std::ifstream fileStream;
	fileStream.open(file);

	if (fileStream.is_open())
	{
		std::string line = "";
		while (getline(fileStream, line))
			_code += "\n" + line;

		fileStream.close();
	}
	else
	{
#ifdef _DEBUG
		_logger = ILoggerPtr(new LogConsole);
		_logger->write("Empty stream", this);
#endif
		return;
	}

	_initialize();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(_id);
}

void ShaderProgram::_initialize()
{
	switch (_type)
	{
	case GL_VERTEX_SHADER:
		_bitField = GL_VERTEX_SHADER_BIT;
		break;
	case GL_GEOMETRY_SHADER:
		_bitField = GL_GEOMETRY_SHADER_BIT;
		break;
	case GL_TESS_CONTROL_SHADER:
		_bitField = GL_TESS_CONTROL_SHADER_BIT;
		break;
	case GL_TESS_EVALUATION_SHADER:
		_bitField = GL_TESS_EVALUATION_SHADER_BIT;
		break;
	case GL_FRAGMENT_SHADER:
		_bitField = GL_FRAGMENT_SHADER_BIT;
		break;
	case GL_COMPUTE_SHADER:
		_bitField = GL_COMPUTE_SHADER_BIT;
		break;
	}

	GLuint shaderId = glCreateShader(_type);

	if (!shaderId || _code.empty())
	{
#ifdef _DEBUG
		_logger = ILoggerPtr(new LogConsole);
		_logger->write("Empty binary", this);
#endif
		return;
	}

	const char* sourcePointer = _code.c_str();
	glShaderSource(shaderId, 1, &sourcePointer, NULL);
	glCompileShader(shaderId);

	std::string infos = ShaderTools::compilerInfos(shaderId);

#ifdef _DEBUG
	_logger->write(infos, this);
#endif

	_log += infos;
	if (!ShaderTools::compileStatus(shaderId))
		return;

	_id = glCreateProgram();
	glProgramParameteri(_id, GL_PROGRAM_SEPARABLE, GL_TRUE);
	glAttachShader(_id, shaderId);
	glLinkProgram(_id);

	infos = ShaderTools::linkerInfos(_id);

#ifdef _DEBUG
	_logger->write(infos, this);
#endif

	_log += infos;
	if (!ShaderTools::linkStatus(_id))
		return;

	glDetachShader(_id, shaderId);
	glDeleteShader(shaderId);
	_isValid = true;
}

GLenum ShaderProgram::type() const
{
	return _type;
}

GLbitfield ShaderProgram::bitField() const
{
	return _bitField;
}

GLuint ShaderProgram::id() const
{
	return _id;
}

bool ShaderProgram::isValid() const
{
	return _isValid;
}

ShaderVariablesList ShaderProgram::inputs() const
{
	ShaderVariablesList list;
	GLenum props[] = { GL_TYPE };
	GLint params[1];
	GLint inputs;
	glGetProgramInterfaceiv(_id, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &inputs);

	for (int idx = 0; idx < inputs; ++idx)
	{
		std::string name;
		name.reserve(256);
		glGetProgramResourceName(_id, GL_PROGRAM_INPUT, idx, 256, NULL, (GLchar*)name.c_str());
		glGetProgramResourceiv(_id, GL_PROGRAM_INPUT, idx, 1, props, 1, NULL, params);
		list.push_back(ShaderVariable(name, params[0]));
	}

	return list;
}

ShaderVariablesList ShaderProgram::outputs() const
{
	ShaderVariablesList list;
	GLenum props[] = { GL_TYPE };
	GLint params[1];
	GLint inputs;
	glGetProgramInterfaceiv(_id, GL_PROGRAM_OUTPUT, GL_ACTIVE_RESOURCES, &inputs);

	for (int idx = 0; idx < inputs; ++idx)
	{
		std::string name;
		name.reserve(256);
		glGetProgramResourceName(_id, GL_PROGRAM_OUTPUT, idx, 256, NULL, (GLchar*)name.c_str());
		glGetProgramResourceiv(_id, GL_PROGRAM_OUTPUT, idx, 1, props, 1, NULL, params);
		list.push_back(ShaderVariable(name, params[0]));
	}

	return list;
}

void ShaderProgram::activate()
{
	glUseProgram(0);
	glActiveShaderProgram(_pipeline->id(), _id);

}
