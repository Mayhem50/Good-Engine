#pragma once

#include "ISceneNode.h"

namespace Good
{
	class ILight: public ISceneNode
	{
	public:
		enum Type
		{
			AMBIENT,
			POINT,
			SPOT
		};		

		ILight(const std::string& name, const ISceneNodePtr& parent, Type type):
			ISceneNode(name, parent), _type(type), _color(0){}

		void setColor(const glm::vec3& color)
		{
			_color = color;
		}
		
		void setColor(float red, float green, float blue, float alpha = 1)
		{
			_color.r = red;
			_color.g = green;
			_color.b = blue;
		}

		const glm::vec3 getColor() const
		{
			return _color;
		}

		glm::vec3& getColor()
		{
			return _color;
		}

	private:
		glm::vec3 _color;
		Type _type;
	};
}