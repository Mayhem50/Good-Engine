#pragma once

#include "GoodFoundation.h"
#include "ShaderProgram.h"

#include <memory>

namespace Good
{
	class ShaderPipeline;
	typedef std::shared_ptr<ShaderPipeline> ShaderPipelinePtr;

	class ShaderProgram;
	typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;

	class Mesh;
	typedef std::shared_ptr<Mesh> MeshPtr;

	class Camera;
	typedef std::shared_ptr<Camera> CameraPtr;

	class GOOD_DLL MaterialPipeline
	{
	public:
		MaterialPipeline();
		void update(MeshPtr mesh, CameraPtr camera);

	private:
		void _updateWorldTransform(MeshPtr mesh, CameraPtr camera);
		void _updateMaterialData(MeshPtr mesh);

		struct WorldTransform
		{
			glm::mat4 modelMatrix;
			glm::mat4 viewMatrix;
			glm::mat4 projectionMatrix;
			glm::mat4 normalMatrix;
		};

		ShaderPipelinePtr _pipeline;
		ShaderProgramPtr _vertexShader;
		ShaderProgramPtr _geometryShader;
		ShaderProgramPtr _framgentShader;

		GLuint _worldTransformBuffer;
		GLuint _materialDataBuffer;
	};

	typedef std::shared_ptr<MaterialPipeline> MaterialPipelinePtr;
}