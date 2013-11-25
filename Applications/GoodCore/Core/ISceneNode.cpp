#include "ISceneNode.h"
#include <utility>

using namespace Good;

ISceneNode::ISceneNode(const std::string& name, const ISceneNodePtr& parent):
	_name(name), _parent(parent)
{
}

bool ISceneNode::addChild(const ISceneNodePtr& child)
{
	std::pair<std::string, ISceneNodePtr> pair(child->getName(), child);
	std::pair<ISceneNodeList::iterator, bool> ret = _childs.insert(pair);

	return ret.second;
}

bool ISceneNode::removeChild(const ISceneNodePtr& child)
{
	if(_childs.erase(child->getName()) == 1)
		return true;
	else
		return false;
}

bool ISceneNode::removeAllChilds()
{
	std::map<std::string, ISceneNodePtr>::iterator it = _childs.begin();
	bool ret = true;

	for(; it != _childs.end(); ++it)
	{
		it->second->removeAllChilds();
		ret &= (bool)_childs.erase(it->first);
	}

	return ret;
}

unsigned int ISceneNode::childsCount() const
{
	return _childs.size();
}

ISceneNodePtr ISceneNode::getChild(const std::string& name)
{
	ISceneNodeList::iterator it = _childs.find(name);

	if(it != _childs.end())
		return it->second;
	else
		return nullptr;
}

ISceneNodePtr ISceneNode::getParent() const
{
	return _parent;
}

std::string ISceneNode::getName()
{
	return _name;
}