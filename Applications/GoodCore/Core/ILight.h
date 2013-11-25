#pragma once

#include "ISceneNode.h"
#include "Color.h"

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

		void setColor(const Color& color)
		{
			_color = color;
		}
		
		void setColor(Real red, Real green, Real blue, Real alpha = 1)
		{
			_color.red = red;
			_color.green = green;
			_color.blue = blue;
			_color.alpha = alpha;
		}

		const Color getColor() const
		{
			return _color;
		}

		Color& getColor()
		{
			return _color;
		}

	private:
		Color _color;
		Type _type;
	};
}