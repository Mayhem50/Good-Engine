#include "Material.h"

#include "ShaderPipeline.h"
#include "ShaderProgram.h"

#include <glm/gtc/type_ptr.hpp>

namespace Good
{		
	Material::Material()
	{
		parameters.diffuseColor = glm::vec4(1.0, 0.0, 0.0, 0.0);
		parameters.emissiveColor = glm::vec4(0.0);

		parameters.metalic = 0.0f;
		parameters.shinyness = 0.01f;
		parameters.roughness = 0.0f;
	}
}