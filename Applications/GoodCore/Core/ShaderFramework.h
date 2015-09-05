#pragma once

#include <string>

namespace Good
{
	namespace ShaderFramework
	{
		const unsigned int MATERIAL_BLOCK_BINDING_POINT = 10;
		const std::string MATERIAL_DATA_BLOCK = \
			"layout (std140, binding = " + std::to_string(MATERIAL_BLOCK_BINDING_POINT) + ") uniform MaterialDataBlock" \
			"{" \
				"vec4 diffuseColor;" \
				"vec4 specularColor;" \
				"vec4 emissiveColor;" \
				"float metalic;" \
				"float shinyness;" \
				"float roughness;" \
				"float opacity;" \
			"}materialData; ";		
	}
}