#include "SceneManager.h"

using namespace Good;

SceneManager::SceneManager()
{
	_root = ISceneNodePtr(new ISceneNode(nullptr, "root"));
}

void SceneManager::addObject(const std::string& name, ISceneNodePtr& parent)
{
	if(parent == nullptr)
		parent = _root;

	ISceneNodePtr child(new ISceneNode(parent, name));
	parent->addChild(child);
}

void SceneManager::addObject(const std::string& name, const std::string& parent)
{
	ISceneNodePtr parentNode;

	if(parent == "root")
		parentNode = _root;
	else
		parentNode =  _root->getChild(parent);

	ISceneNodePtr childNode(new ISceneNode(parentNode, name));

	parentNode->addChild(childNode);
}

void SceneManager::addLight(const std::string& name, ISceneNodePtr& parent, ILight::Type type)
{
	if(parent == nullptr)
		parent = _root;

	std::shared_ptr<ILight> light(new ILight(parent, name, type));
	parent->addChild(light);
}
