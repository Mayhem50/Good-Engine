#include "DirectionnalLight.h"

using namespace Good;

DirectionnalLight::DirectionnalLight(const ISceneNodePtr& parent, const std::string& name) :
ILight(parent, name, DIRECTIONNAL)
{
	_direction = glm::vec3(1.0, -1.0, -1.0);
}


DirectionnalLight::~DirectionnalLight()
{
}

glm::vec3 DirectionnalLight::direction() const
{
	return glm::normalize(_direction);
}
