#include "GLSLPipeline.h"

#ifdef _DEBUG
#include "LogConsole.h"
#endif

#include <algorithm>

using namespace Good;

GLSLPipeline::GLSLPipeline()
{
	glGenProgramPipelines(1, &_id);
}

GLSLPipeline::~GLSLPipeline()
{
	glDeleteProgramPipelines(1, &_id);
}

bool GLSLPipeline::addShaderProgram(ShaderProgram* program)
{
	ShaderProgramsList::iterator it = std::find(_programsList.begin(), _programsList.end(), program);
	
	if (it == _programsList.end())
	{
		_programsList.push_back(program);
		return true;
	}

	return false;
}

GLuint GLSLPipeline::id() const
{
	return _id;
}

bool GLSLPipeline::isValid() const
{
	bool ret = true;

	ShaderProgramsList::const_iterator it = _programsList.begin();
	for (; it != _programsList.end(); ++it)
		ret &= (*it)->isValid();

	return ret;
}

void GLSLPipeline::bind()
{
	glUseProgram(0);
	glBindProgramPipeline(_id);
}
