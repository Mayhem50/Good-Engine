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
	
	class ShaderProgram;
	typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;
	typedef std::vector<ShaderProgramPtr> ShaderProgramsList;
	typedef std::map<ShaderProgramPtr, std::string> ShaderProgramsMap;

	class GOOD_DLL ShaderProgram : public GoodObject
	{
	public:
		static const ShaderProgramPtr EMPTY_SHADER_PROGRAM;
		static ShaderProgramPtr CreateShaderProgramFromFile(const char* fileName, GLenum type, const char* name = nullptr);
		static ShaderProgramPtr CreateShaderProgramFromSource(const char* source, GLenum type, const char* name = nullptr);
		~ShaderProgram();

		GLenum type() const;
		GLbitfield bitField() const;
		GLuint id() const;

		bool isValid() const;

		ShaderVariablesList inputs() const;
		ShaderVariablesList outputs() const;

		void use() const;
		void unsuse() const;

	private:
		ShaderProgram(const char* fileName, GLenum type, const char* name);
		ShaderProgram(GLenum type, const char* fileName, const char* name);

		bool _readSourceFromFile(const char* fileName);
		void _setBitField();
		bool _build();

		GLuint _id;
		GLenum _type;
		GLbitfield _bitField;

		bool _isValid;

		std::string _name;
		std::string _code;
		std::string _log;
	};

}