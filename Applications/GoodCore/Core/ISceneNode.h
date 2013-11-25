#pragma once

#include <map>
#include <string>
#include <memory>

#include "../Math/Vectors.h"

namespace Good
{	
	class ISceneNode;	
	typedef std::shared_ptr<ISceneNode> ISceneNodePtr;
	typedef std::map<std::string, ISceneNodePtr> ISceneNodeList;

	class ISceneNode
	{
	public:
		ISceneNode(const std::string& name, const ISceneNodePtr& parent);

		bool addChild(const ISceneNodePtr& child);
		bool removeChild(const ISceneNodePtr& child);
		bool removeAllChilds();
		ISceneNodePtr getChild(const std::string& name);
		unsigned int childsCount() const;
		ISceneNodePtr getParent() const;

		 std::string getName();

	protected:
		std::string _name;
		ISceneNodePtr _parent;
		ISceneNodeList _childs;

	private:
			ISceneNode();
			ISceneNode& operator=(const ISceneNode& copy);
	};	
}