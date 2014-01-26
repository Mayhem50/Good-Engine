#pragma once

#include "GoodFoundation.h"

#include <map>
#include <string>
#include <memory>

#include <glm\gtc\quaternion.hpp>
#include <glm\gtc\constants.hpp>

namespace Good
{	
	class ISceneNode;	
	typedef std::shared_ptr<ISceneNode> ISceneNodePtr;
	typedef std::map<std::string, ISceneNodePtr> ISceneNodeList;

	static const glm::vec3 nullVec3 = glm::vec3(0.0);
	static const glm::quat identityQuat = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

	enum TRANSFORM_RELATIVE
	{
		LOCAL,
		PARENT,
		WORLD
	};

	class GOOD_DLL ISceneNode
	{
	public:
		ISceneNode(const std::string& name, const ISceneNodePtr& parent);

		ISceneNode* createChild(const glm::vec3& translate = nullVec3, const glm::quat& rotate = identityQuat);
		bool addChild(const ISceneNodePtr& child);
		bool removeChild(const ISceneNodePtr& child);
		bool removeAllChilds();
		ISceneNodePtr getChild(const std::string& name);
		unsigned int childsCount() const;
		ISceneNodePtr getParent() const;

		void translate(const glm::vec3& direction, TRANSFORM_RELATIVE relativeTo = PARENT);
		void translate(double x, double y, double z, TRANSFORM_RELATIVE relativeTo = PARENT);
		void translate(const glm::mat3& axes, const glm::vec3& direction, TRANSFORM_RELATIVE relativeTo = PARENT);
		void translate(const glm::mat3& axes, double x, double y, double z, TRANSFORM_RELATIVE relativeTo = PARENT);

		void roll(double angle, TRANSFORM_RELATIVE relativeTo = LOCAL);
		void pitch(double angle, TRANSFORM_RELATIVE relativeTo = LOCAL);
		void yaw(double angle, TRANSFORM_RELATIVE relativeTo = LOCAL);

		void rotate(const glm::vec3& axis, double angle, TRANSFORM_RELATIVE relativeTo = LOCAL);
		void rotate(const glm::quat& quaternion, TRANSFORM_RELATIVE relativeTo = LOCAL);

		void setPosition(const glm::vec3& position);
		void setPosition(double x, double y, double z);
		glm::vec3 position() const;
		
		void setScale(const glm::vec3& scale);
		void setScale(double x, double y, double z);
		glm::vec3 scale() const;

		void setOrientation(const glm::quat& quaternion);
		void setOrientation(double w, double x, double y, double z);
		glm::quat orientation() const;

		glm::mat3 localMatrix() const;

		 std::string getName();

		 void updateFromParent();
		 glm::vec3 derivedPosition();
		 glm::vec3 derivedScale();
		 glm::quat derivedOrientation();


	protected:
		std::string _name;
		ISceneNodePtr _parent;
		ISceneNodeList _childs;

		glm::vec3 _position;
		glm::vec3 _scale;
		glm::quat _orientation;

		glm::vec3 _derivedPosition;
		glm::vec3 _derivedScale;
		glm::quat _derivedOrientation;

		bool _inherit;

	private:
			ISceneNode();
			ISceneNode& operator=(const ISceneNode& copy);
	};

	namespace NameTools
	{
		std::string nameGenerator();
	}
}