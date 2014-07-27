#include "Material.h"

#include <glm/gtc/type_ptr.hpp>
using namespace Good;

Material::Material(const char* name):
GoodObject(name)
{
	diffuseColor = glm::vec4(1.0, 0.0, 0.0, 0.0);
	specularColor = glm::vec4(0.9);
	emissiveColor = glm::vec4(0.0);
	
	metallic = 0.0f;
	roughness = 0.20f;
	opacity = 1.0f;
	indice = 1.50f;
}
