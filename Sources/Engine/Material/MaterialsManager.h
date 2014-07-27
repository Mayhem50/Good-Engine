#pragma once

#include "../Core/Singleton.h"
#include "Material.h"

#include <map>

namespace Good
{
	class GOOD_DLL MaterialsManager : public Singleton<MaterialsManager>
	{
	public:
		bool addMaterial(MaterialPtr material);
		bool removeMaterial(MaterialPtr material);
		bool removeMaterial(const std::string& uuid);

		MaterialPtr getMaterial(const std::string& uuid);

	private:
		std::map<std::string, MaterialPtr> _materialMap;
	};
}