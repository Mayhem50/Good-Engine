#pragma once

#include "../Core/GoodObject.h"

#include "../../Tools/Logger/ILogger.h"

#include <GL/glew.h>

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <tuple>

namespace Good
{
	typedef std::tuple<std::string, GLenum> ShaderVariable;
	typedef std::vector<ShaderVariable> ShaderVariablesList;

	class ShaderPipeline;
	typedef std::shared_ptr<ShaderPipeline> ShaderPipelinePtr;

	class ShaderProgram;
	typedef std::vector<ShaderProgram*> ShaderProgramsList;
	typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;
	typedef std::vector<ShaderProgramPtr> ShaderProgramsPtrList;
	typedef std::map<ShaderProgramPtr, std::string> ShaderProgramsMap;

	class GOOD_DLL ShaderProgram : public GoodObject
	{
	public:
		ShaderProgram(ShaderPipelinePtr pipeline, const char* file, GLenum type, const char* name = nullptr);
		~ShaderProgram();

		GLenum type() const;
		GLbitfield bitField() const;
		GLuint id() const;

		bool isValid() const;

		ShaderVariablesList inputs() const;
		ShaderVariablesList outputs() const;

		void activate();
		
		static const ShaderProgramPtr EMPY_PROGRAM;

	private:
		void _initialize();

		GLuint _id;
		GLenum _type;
		GLbitfield _bitField;

		ShaderPipelinePtr _pipeline;

		bool _isValid;

		std::string _code;
		std::string _log;
	};
}