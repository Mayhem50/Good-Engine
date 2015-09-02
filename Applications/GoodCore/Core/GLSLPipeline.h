#pragma once

#include "GoodObject.h"
#include "GoodFoundation.h"

#include "ShaderProgram.h"

#ifdef _DEBUG

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

		bool isValid() const;

		ShaderProgramsList currentPrograms() const;

	private:
		GLuint _id;
		ShaderProgramsList _programsList;

#ifdef _DEBUG
		
#endif
	};
}