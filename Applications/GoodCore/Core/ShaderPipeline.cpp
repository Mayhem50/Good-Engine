#include "ShaderPipeline.h"

#include <algorithm>

namespace Good
{

	ShaderPipeline::ShaderPipeline()
	{
		glGenProgramPipelines(1, &_id);
	}
	
	ShaderPipeline::ShaderPipeline(const ShaderProgramsList& programs)
	{
		glGenProgramPipelines(1, &_id);
		addPrograms(programs);
	}

	ShaderPipeline::ShaderPipeline(ShaderProgramPtr vertexShader, ShaderProgramPtr geometryShader, ShaderProgramPtr fragmentShader)
	{
		glGenProgramPipelines(1, &_id);
		addProgram(vertexShader);
		addProgram(geometryShader);
		addProgram(fragmentShader);
	}

	ShaderPipeline::~ShaderPipeline()
	{
		glDeleteProgramPipelines(1, &_id);
	}

	bool ShaderPipeline::addProgram(ShaderProgramPtr program)
	{
		bool ret = false;

		if (program)
		{
			switch (program->type())
			{
			case GL_VERTEX_SHADER:
				if (!_vertexShader)
				{
					_vertexShader = program;
					glUseProgramStages(_id, _vertexShader->bitField(), _vertexShader->id());
					ret = true;
				}
				break;
			case GL_GEOMETRY_SHADER:
				if (!_geometryShader)
				{
					_geometryShader = program;
					glUseProgramStages(_id, _geometryShader->bitField(), _geometryShader->id());
					ret = true;
				}
				break;
			case GL_TESS_CONTROL_SHADER:
				if (!_tessCtrlShader)
				{
					_tessCtrlShader = program;
					glUseProgramStages(_id, _tessCtrlShader->bitField(), _tessCtrlShader->id());
					ret = true;
				}
				break;
			case GL_TESS_EVALUATION_SHADER:
				if (!_tessEvalShader)
				{
					_tessEvalShader = program;
					glUseProgramStages(_id, _tessEvalShader->bitField(), _tessEvalShader->id());
					ret = true;
				}
				break;
			case GL_FRAGMENT_SHADER:
				if (!_fragmentShader)
				{
					_fragmentShader = program;
					glUseProgramStages(_id, _fragmentShader->bitField(), _fragmentShader->id());
					ret = true;
				}
				break;
			default:
				break;
			}

			_pipelineValidation();
		}

		return ret;
	}

	bool ShaderPipeline::replaceProgram(ShaderProgramPtr program)
	{
		bool ret = false;

		if (program)
		{
			switch (program->type())
			{
			case GL_VERTEX_SHADER:
				if (_vertexShader)
				{
					_vertexShader = program;
					glUseProgramStages(_id, _vertexShader->bitField(), _vertexShader->id());
					ret = true;
				}
				break;
			case GL_GEOMETRY_SHADER:
				if (_geometryShader)
				{
					_geometryShader = program;
					glUseProgramStages(_id, _geometryShader->bitField(), _geometryShader->id());
					ret = true;
				}
				break;
			case GL_TESS_CONTROL_SHADER:
				if (_tessCtrlShader)
				{
					_tessCtrlShader = program;
					glUseProgramStages(_id, _tessCtrlShader->bitField(), _tessCtrlShader->id());
					ret = true;
				}
				break;
			case GL_TESS_EVALUATION_SHADER:
				if (_tessEvalShader)
				{
					_tessEvalShader = program;
					glUseProgramStages(_id, _tessEvalShader->bitField(), _tessEvalShader->id());
					ret = true;
				}
				break;
			case GL_FRAGMENT_SHADER:
				if (_fragmentShader)
				{
					_fragmentShader = program;
					glUseProgramStages(_id, _fragmentShader->bitField(), _fragmentShader->id());
					ret = true;
				}
				break;
			default:
				break;
			}

			_pipelineValidation();
		}

		return ret;
	}

	bool ShaderPipeline::addPrograms(const ShaderProgramsList& programs)
	{
		bool ret = true;

		for (auto program : programs)
		{
			ret &= addProgram(program);
		}

		return ret;
	}

	bool ShaderPipeline::replacePrograms(const ShaderProgramsList& programs)
	{
		bool ret = true;

		for (auto program : programs)
		{
			ret &= replaceProgram(program);
		}

		return ret;
	}

	GLuint ShaderPipeline::id() const
	{
		return _id;
	}

	bool ShaderPipeline::isValid() const
	{
		return _isValid;
	}

	void ShaderPipeline::use()
	{
		glUseProgram(0);
		glBindProgramPipeline(_id);
	}

	void ShaderPipeline::_pipelineValidation()
	{
		_isValid = true;

		if (_vertexShader && _fragmentShader)
		{
			_isValid &= _vertexShader->isValid();
			_isValid &= _fragmentShader->isValid();

			if (_geometryShader)
				_isValid &= _geometryShader->isValid();
			if (_tessCtrlShader && _tessEvalShader)
			{
				_isValid &= _tessCtrlShader->isValid();
				_isValid &= _tessEvalShader->isValid();
			}
		}
		else
			_isValid = false;
	}

	ShaderProgramPtr ShaderPipeline::vertexShader()
	{
		return _vertexShader;
	}

	ShaderProgramPtr ShaderPipeline::geometryShader()
	{
		return _geometryShader;
	}

	ShaderProgramPtr ShaderPipeline::fragmentShader()
	{
		return _fragmentShader;
	}

	ShaderProgramPtr ShaderPipeline::tesselationControlShader()
	{
		return _tessCtrlShader;
	}

	ShaderProgramPtr ShaderPipeline::tesselationEvaluationShader()
	{
		return _tessEvalShader;
	}
}
