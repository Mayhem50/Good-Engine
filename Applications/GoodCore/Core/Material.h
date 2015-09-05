#pragma once

#include "GoodFoundation.h"

#include <memory>
#include <GL\glew.h>

namespace Good
{
	struct GOOD_DLL Material
	{
		Material();

		struct Parameters
		{
			glm::vec4 diffuseColor;
			glm::vec4 specularColor;
			glm::vec4 emissiveColor;
			float metalic;
			float shinyness;
			float roughness;
			float shinyness2;
			float roughness2;
		};

		Parameters parameters;
	};

	typedef std::shared_ptr<Material> MaterialPtr;
}