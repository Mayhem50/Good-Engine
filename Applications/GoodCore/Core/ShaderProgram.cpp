#include "ShaderProgram.h"

#include "ShaderTools.h"
#include "GLSLPipeline.h"

#ifdef _DEBUG

#endif

#include <fstream>

using namespace Good;

const ShaderProgramPtr ShaderProgram::EMPY_PROGRAM = ShaderProgramPtr(nullptr);

ShaderProgram::ShaderProgram(GLSLPipelinePtr pipeline, const char* sourceFile, GLenum type, const char* name):
_pipeline(pipeline),
_isValid(false), 
_name(name), 
_type(type)
{
#ifdef _DEBUG
	
#endif

	_pipeline->addShaderProgram(this);

	if (!sourceFile || !pipeline)
		return;

	std::ifstream stream(sourceFile, std::ios::in);

	if (stream.is_open())
	{
		std::string line = "";
		while (getline(stream, line))
			_code += "\n" + line;

		stream.close();
	}
	switch (type)
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

	GLuint shaderId = glCreateShader(type);

	if (!shaderId || _code.empty())
		return;

	const char* sourcePointer = _code.c_str();
	glShaderSource(shaderId, 1, &sourcePointer, NULL);
	glCompileShader(shaderId);

	std::string infos = ShaderTools::compilerInfos(shaderId);

#ifdef _DEBUG

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
	
#endif

	_log += infos;
	if (!ShaderTools::linkStatus(_id))
		return;
	
	glDetachShader(_id, shaderId);
	glDeleteShader(shaderId);
	_isValid = true;
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(_id);
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

void ShaderProgram::use() const
{
	glUseProgramStages(_pipeline->id(), _bitField, _id);
	_pipeline->bind();
}

void ShaderProgram::unsuse() const
{
	glUseProgramStages(_pipeline->id(), _bitField, 0);
	_pipeline->bind();
}