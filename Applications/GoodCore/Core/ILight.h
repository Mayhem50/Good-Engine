#pragma once

#include "ISceneNode.h"

namespace Good
{
	class GOOD_DLL ILight : public ISceneNode
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

		void setColor(const glm::vec4& color)
		{
			_color = color;
		}
		
		void setColor(float red, float green, float blue, float alpha = 1)
		{
			_color.r = red;
			_color.g = green;
			_color.b = blue;
			_color.a = alpha;
		}

		const glm::vec4 color() const
		{
			return _color;
		}

		glm::vec4& color()
		{
			return _color;
		}

	private:
		glm::vec4 _color;
		float _power;

		Type _type;
	};
}