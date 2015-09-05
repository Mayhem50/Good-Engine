#include "ShaderPipeline.h"

#include <algorithm>

using namespace Good;

ShaderPipeline::ShaderPipeline(const char* name):
GoodObject(name)
{
	glGenProgramPipelines(1, &_id);
}

ShaderPipeline::~ShaderPipeline()
{
	glDeleteProgramPipelines(1, &_id);
}

bool ShaderPipeline::addProgram(ShaderProgramPtr program, bool force)
{	
	if (!this->containsTypeOfProgram(program->type()))
	{
		_programsList.push_back(program);
		return true;
	}
	
	if (force)
	{
		for (auto it = _programsList.begin(); it != _programsList.end(); ++it)
		{
			ShaderProgramPtr oldProgram = *it;

			if (oldProgram->type() == program->type())
			{
				_programsList.erase(it);
				_programsList.push_back(program);
				return true;
			}
		}
	}

	return false;
}

bool ShaderPipeline::removeProgram(ShaderProgramPtr program)
{
	for (auto& prog : _programsList)
	{
		if (prog == program)
		{
			auto it = std::find(_programsList.begin(), _programsList.end(), prog);
			_programsList.erase(it);
			return true;
		}
	}

	return false;
}

bool ShaderPipeline::containsTypeOfProgram(GLenum type)
{
	for (auto& program : _programsList)
	{
		if (program->type() == type)
			return true;
	}

	return false;
}

GLuint ShaderPipeline::id() const
{
	return _id;
}

bool ShaderPipeline::isValid() const
{
	bool ret = true;
	bool haveVertexShader = false;
	bool haveFragmentShader = false;

	for (const auto& program : _programsList)
	{
		if (program->isValid())
		{
			if (program->type() == GL_VERTEX_SHADER)
				haveVertexShader = true;
			else if (program->type() == GL_FRAGMENT_SHADER)
				haveFragmentShader = true;			
		}

		ret &= program->isValid();
	}

	return (ret && haveFragmentShader && haveVertexShader);
}

void ShaderPipeline::bind() const
{
	glUseProgram(0);

	for (const auto& program : _programsList)
	{
		glUseProgramStages(_id, program->bitField(), program->id());
		glActiveShaderProgram(_id, program->id());
	}

	glBindProgramPipeline(_id);
}

void ShaderPipeline::unbind() const
{
	glUseProgram(0);

	for (const auto& program : _programsList)
	{
		glUseProgramStages(_id, program->bitField(), 0);
		glActiveShaderProgram(_id, program->id());
	}
}
