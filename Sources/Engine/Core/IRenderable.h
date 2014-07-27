#pragma once

#include "../Core/GoodFoundation.h"

#include "../Camera/Camera.h"

namespace Good
{
	class GOOD_DLL IRenderable
	{
	public:
		virtual ~IRenderable(){}

		virtual bool init() = 0;
		virtual float draw() = 0;
		virtual bool shutdown() = 0;
	};
}