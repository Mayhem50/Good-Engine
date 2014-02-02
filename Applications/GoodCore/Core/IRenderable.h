#pragma once

#include "Camera.h"
#include "FrameBufferObject.h"

namespace Good
{
	struct RenderResources
	{
		CameraPtr camera;
		FrameBufferObjectPtr fbo;
	};

	class IRenderable
	{
	public:
		virtual ~IRenderable(){}

		virtual bool init() = 0;
		virtual float draw() = 0;
		virtual bool shutdown() = 0;
	};
}