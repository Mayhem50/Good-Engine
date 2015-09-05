#include "MaterialPipeline.h"

#include "ShaderPipeline.h"
#include "Material.h"
#include "Mesh.h"
#include "Camera.h"

namespace Good
{
	MaterialPipeline::MaterialPipeline()
	{
		_pipeline = ShaderPipelinePtr(new ShaderPipeline);
		_vertexShader = ShaderProgram::CreateShaderProgramFromFile("../../Assets/Shaders/Passthrough.vert", GL_VERTEX_SHADER, "passthroughVS");
		_framgentShader = ShaderProgram::CreateShaderProgramFromFile("../../Assets/Shaders/ColorFragmentShader.frag", GL_FRAGMENT_SHADER, "colorFragment");
		_geometryShader = ShaderProgram::CreateShaderProgramFromFile("../../Assets/Shaders/Passthrough.geom", GL_GEOMETRY_SHADER, "passthroughGS");
		
		_pipeline->addProgram(_vertexShader);
		_pipeline->addProgram(_geometryShader);
		_pipeline->addProgram(_framgentShader);
		
		glGenBuffers(1, &_worldTransformBuffer);
		glBindBuffer(GL_UNIFORM_BUFFER, _worldTransformBuffer);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(WorldTransform), NULL, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glGenBuffers(1, &_materialDataBuffer);
		glBindBuffer(GL_UNIFORM_BUFFER, _materialDataBuffer);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(Material::Parameters), NULL, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void MaterialPipeline::update(MeshPtr mesh, CameraPtr camera)
	{
		_pipeline->use();
		_updateWorldTransform(mesh, camera);
		_updateMaterialData(mesh);
	}

	void MaterialPipeline::_updateMaterialData(MeshPtr mesh)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 10, _materialDataBuffer);
		Material::Parameters *parameters = (Material::Parameters*)glMapBufferRange(GL_UNIFORM_BUFFER, 0, sizeof(Material::Parameters), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
		auto material = mesh->material();
		*parameters = material->parameters;
		glUnmapBuffer(GL_UNIFORM_BUFFER);
	}

	void MaterialPipeline::_updateWorldTransform(MeshPtr mesh, CameraPtr camera)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, _worldTransformBuffer);
		WorldTransform *transform = (WorldTransform*)glMapBufferRange(GL_UNIFORM_BUFFER, 0, sizeof(WorldTransform), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

		transform->modelMatrix = mesh->localMatrix();
		transform->viewMatrix = camera->viewMatrix();
		transform->projectionMatrix = camera->projectionMatrix();
		glm::mat4 modelView = camera->viewMatrix() * mesh->localMatrix();
		transform->normalMatrix = glm::transpose(glm::inverse(modelView));

		glUnmapBuffer(GL_UNIFORM_BUFFER);
	}
}