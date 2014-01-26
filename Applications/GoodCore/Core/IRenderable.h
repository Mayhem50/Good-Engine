#pragma once

#include "Camera.h"

namespace Good
{
	class IRenderable
	{
	public:
		virtual ~IRenderable(){}

		virtual bool init() = 0;
		virtual float render(const CameraPtr& camera) = 0;
		virtual bool shutdown() = 0;
	};
}