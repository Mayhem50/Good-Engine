#pragma once

#include "GoodObject.h"
#include "GoodFoundation.h"

#include <GL\glew.h>

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <tuple>

namespace Good
{
	typedef std::tuple<std::string, GLenum> ShaderVariable;
	typedef std::vector<ShaderVariable> ShaderVariablesList;

	class GLSLPipeline;
	typedef std::shared_ptr<GLSLPipeline> GLSLPipelinePtr;

	class ShaderProgram;
	typedef std::vector<ShaderProgram*> ShaderProgramsList;
	typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;
	typedef std::vector<ShaderProgramPtr> ShaderProgramsPtrList;
	typedef std::map<ShaderProgramPtr, std::string> ShaderProgramsMap;

	class GOOD_DLL ShaderProgram : public GoodObject
	{
	public:
		ShaderProgram(GLSLPipelinePtr pipeline, const char* sourceFile, GLenum type, const char* name = nullptr);
		~ShaderProgram();

		GLenum type() const;
		GLbitfield bitField() const;
		GLuint id() const;

		bool isValid() const;

		ShaderVariablesList inputs() const;
		ShaderVariablesList outputs() const;

		void use() const;
		void unsuse() const;

		static const ShaderProgramPtr EMPY_PROGRAM;

	private:
		GLuint _id;
		GLenum _type;
		GLbitfield _bitField;

		bool _isValid;

		std::string _name;
		std::string _code;
		std::string _log;

		GLSLPipelinePtr _pipeline;


#ifdef _DEBUG
		
#endif
	};
}