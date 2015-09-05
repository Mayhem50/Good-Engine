#pragma once

#include "GoodObject.h"
#include "GoodFoundation.h"

#include "ShaderProgram.h"

#ifdef _DEBUG

#endif

#include <memory>

namespace Good
{
	class GOOD_DLL ShaderPipeline : public GoodObject
	{
	public:
		ShaderPipeline();
		ShaderPipeline(const ShaderProgramsList& programs); 
		ShaderPipeline(ShaderProgramPtr vertexShader, ShaderProgramPtr geometryShader, ShaderProgramPtr fragmentShader);
		~ShaderPipeline();

		bool addProgram(ShaderProgramPtr program);
		bool replaceProgram(ShaderProgramPtr program);
		bool addPrograms(const ShaderProgramsList& programs);
		bool replacePrograms(const ShaderProgramsList& programs);

		GLuint id() const;
		void use();

		bool isValid() const;

		ShaderProgramPtr vertexShader();
		ShaderProgramPtr geometryShader();
		ShaderProgramPtr fragmentShader();
		ShaderProgramPtr tesselationControlShader();
		ShaderProgramPtr tesselationEvaluationShader();
		
	private:
		void _pipelineValidation();

		GLuint _id;

		ShaderProgramPtr _vertexShader;
		ShaderProgramPtr _geometryShader;
		ShaderProgramPtr _fragmentShader;
		ShaderProgramPtr _tessEvalShader;
		ShaderProgramPtr _tessCtrlShader;

		bool _isValid;

#ifdef _DEBUG
		
#endif
	};

	typedef std::shared_ptr<ShaderPipeline> ShaderPipelinePtr;
}