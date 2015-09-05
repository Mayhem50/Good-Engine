#pragma once

#include "ILight.h"

namespace Good
{
	class PointLight : public ILight
	{
	public:
		PointLight(const ISceneNodePtr& parent, const std::string& name);
		~PointLight();
	};

	typedef std::shared_ptr<PointLight> PointLightPtr;
}