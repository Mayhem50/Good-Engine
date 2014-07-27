#pragma once

#include "../Core/GoodObject.h"

#include "ShaderProgram.h"

#include <memory>

namespace Good
{
	class GOOD_DLL ShaderPipeline : public GoodObject
	{
	public:
		ShaderPipeline(const char* name = nullptr);
		~ShaderPipeline();

		bool addProgram(ShaderProgramPtr program, bool force = false);
		bool removeProgram(ShaderProgramPtr program);
		
		GLuint id() const;

		void bind() const;
		void unbind() const;

		bool isValid() const;

		ShaderProgramsPtrList currentPrograms() const;
		bool containsTypeOfProgram(GLenum type);

	private:

		GLuint _id;
		ShaderProgramsPtrList _programsList;
	};
}