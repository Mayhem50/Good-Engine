#include "PointLight.h"

using namespace Good;

PointLight::PointLight(const ISceneNodePtr& parent, const std::string& name) :
ILight(parent, name, POINT)
{

}

PointLight::~PointLight()
{

}

