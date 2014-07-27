#include "MaterialsManager.h"

#include <exception>

using namespace Good;

bool MaterialsManager::addMaterial(MaterialPtr material)
{
	auto it = _materialMap.find(material->name());

	if (it == _materialMap.end())
	{
		std::pair<std::string, MaterialPtr> pair(material->name(), material);
		_materialMap.insert(pair);
		return true;
	}

	return false;
}

bool MaterialsManager::removeMaterial(MaterialPtr material)
{
	return removeMaterial(material->name());
}

bool MaterialsManager::removeMaterial(const std::string& uuid)
{
	return (bool)_materialMap.erase(uuid);
}

MaterialPtr MaterialsManager::getMaterial(const std::string& name)
{
	auto it = _materialMap.find(name);

	if (it != _materialMap.end())
		return it->second;
	else
		throw new std::exception("No material found");
}