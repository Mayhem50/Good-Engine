#pragma once
#include "ILight.h"

namespace Good
{
	class DirectionnalLight :
		public ILight
	{
	public:
		DirectionnalLight(const ISceneNodePtr& parent, const std::string& name);
		~DirectionnalLight();

		glm::vec3 direction() const;
	private:
		glm::vec3 _direction;
	};
}

