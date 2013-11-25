#pragma once
#include "ILight.h"
#include "Singleton.h"

namespace Good
{
	class GOOD_DLL SceneManager : public Singleton<SceneManager>
	{
	public:
		SceneManager();
		void addObject(const std::string& name, ISceneNodePtr& parent);
		void addObject(const std::string& name, const std::string& parent = "root");
		void addLight(const std::string& name, ISceneNodePtr& parent, ILight::Type type = ILight::Type::AMBIENT);


	private:
		ISceneNodePtr _root;
	};
}

