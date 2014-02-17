#pragma once

#include "GoodObject.h"

#include "ShaderProgram.h"

#ifdef _DEBUG
#include "ILogger.h"
#endif

#include <memory>

namespace Good
{
	class GOOD_DLL GLSLPipeline : public GoodObject
	{
	public:
		GLSLPipeline();
		~GLSLPipeline();

		bool addShaderProgram(ShaderProgram* program);
		GLuint id() const;
		void bind();

		ShaderProgramsList currentPrograms() const;

	private:
		GLuint _id;
		ShaderProgramsList _programsList;

#ifdef _DEBUG
		ILoggerPtr _logger;
#endif
	};
}