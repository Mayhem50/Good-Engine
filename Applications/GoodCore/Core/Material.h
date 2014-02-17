#pragma once

#include "ShaderProgram.h"

#include <memory>

namespace Good
{
	class GOOD_DLL Material
	{
	public:
		Material(ShaderProgramPtr vertexShader, ShaderProgramPtr fragmentShader, ShaderProgramPtr geometryShader = ShaderProgram::EMPY_PROGRAM, ShaderProgramPtr tessControlShader = ShaderProgram::EMPY_PROGRAM, ShaderProgramPtr tessEvalShader = ShaderProgram::EMPY_PROGRAM);

		void use();

		ShaderProgramPtr vertexShader() const;
		ShaderProgramPtr fragmentShader() const;

	private:
		void _updateUniforms();

		ShaderProgramPtr _vertexShader;
		ShaderProgramPtr _fragmentShader;
		ShaderProgramPtr _geometryShader;
		ShaderProgramPtr _tessControlShader;
		ShaderProgramPtr _tessEvalShader;

		struct Data
		{
			glm::vec3 diffuseColor;
			glm::vec3 specularColor;
			glm::vec3 emissiveColor;

			float metalic;
			float roughness;
			float opacity;
			float refraction;
		};

		Data _data;
		GLuint _dataUniformBlockID;

		GLuint _alphaMap;
		GLuint _normalMap;

		static const GLchar* UNIFORM_BLOCK_NAMES;
	};

	typedef std::shared_ptr<Material> MaterialPtr;
}