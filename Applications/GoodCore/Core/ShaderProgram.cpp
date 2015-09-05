#include "ShaderProgram.h"

#include "ShaderTools.h"
#include "ShaderPipeline.h"

#ifdef _DEBUG

#endif

#include <fstream>

namespace Good
{	
	const ShaderProgramPtr ShaderProgram::EMPTY_SHADER_PROGRAM = ShaderProgramPtr(nullptr);
	ShaderProgramPtr ShaderProgram::CreateShaderProgramFromFile(const char* fileName, GLenum type, const char* name)
	{
		return ShaderProgramPtr(new ShaderProgram(fileName, type, name));
	}

	ShaderProgramPtr ShaderProgram::CreateShaderProgramFromSource(const char* source, GLenum type, const char* name)
	{
		return ShaderProgramPtr(new ShaderProgram(type, source, name));
	}

	ShaderProgram::ShaderProgram(const char* fileName, GLenum type, const char* name) :
		_isValid(false),
		_type(type),
		_name(name),
		_bitField(0)
	{	
		if (!_readSourceFromFile(fileName))
			return;

		_setBitField();
		_isValid = _build();
	}

	ShaderProgram::ShaderProgram(GLenum type, const char* source, const char* name = nullptr) :
		_isValid(false),
		_type(type),
		_name(name),
		_bitField(0)
	{
		if (source == nullptr)
			return;

		_setBitField();
		_isValid = _build();
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(_id);
	}

	GLenum ShaderProgram::type() const
	{
		return _type;
	}

	/*std::string ShaderProgram::type() const
	{
		switch (_glType)
		{
		case GL_VERTEX_SHADER:
			return ShaderType::VERTEX_SHADER;
		case GL_GEOMETRY_SHADER:
			return ShaderType::GEOMETRY_SHADER;
		case GL_TESS_CONTROL_SHADER:
			return ShaderType::TESSELATION_CONTROL_SHADER;
		case GL_TESS_EVALUATION_SHADER:
			return ShaderType::TESSELATION_EVALUATION_SHADER;
		case GL_FRAGMENT_SHADER:
			return ShaderType::FRAGMENT_SHADER;
		case GL_COMPUTE_SHADER:
			return ShaderType::COMPUTE_SHADER;
		default:
			return ShaderType::NOT_A_SHADER;
		}
	}*/

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
			GLchar name[MAX_CHAR];
			glGetProgramResourceName(_id, GL_PROGRAM_INPUT, idx, 256, NULL, (GLchar*)name);
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
			GLchar name[MAX_CHAR];
			glGetProgramResourceName(_id, GL_PROGRAM_OUTPUT, idx, 256, NULL, (GLchar*)name);
			glGetProgramResourceiv(_id, GL_PROGRAM_OUTPUT, idx, 1, props, 1, NULL, params);
			list.push_back(ShaderVariable(name, params[0]));
		}

		return list;
	}

	bool ShaderProgram::_readSourceFromFile(const char* fileName)
	{
		if (!fileName)
			return false;

		std::ifstream stream(fileName, std::ios::in);

		if (stream.is_open())
		{
			std::string line = "";
			while (getline(stream, line))
				_code += "\n" + line;

			stream.close();

			return true;
		}

		return false;
	}

	void ShaderProgram::_setBitField()
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
		default:
			break;
		}
	}

	bool ShaderProgram::_build()
	{
		GLuint shaderId = glCreateShader(_type);

		if (!shaderId || _code.empty())
			return false;

		const char* sourcePointer = _code.c_str();
		glShaderSource(shaderId, 1, &sourcePointer, NULL);
		glCompileShader(shaderId);

		std::string infos = ShaderTools::compilerInfos(shaderId);
		_log += infos;

		if (!ShaderTools::compileStatus(shaderId))
			return false;

		_id = glCreateProgram();

		glProgramParameteri(_id, GL_PROGRAM_SEPARABLE, GL_TRUE);
		glAttachShader(_id, shaderId);
		glLinkProgram(_id);

		infos = ShaderTools::linkerInfos(_id);

		_log += infos;
		if (!ShaderTools::linkStatus(_id))
			return false;

		glDetachShader(_id, shaderId);
		glDeleteShader(shaderId);
		return true;
	}
}