#pragma once

#include "Camera.h"

namespace Good
{
	class CameraMotion
	{
	public:
		enum ACTIONS
		{
			PAN,
			ORBIT,
			ZOOM
		};

		CameraMotion(CameraPtr camera, ViewportPtr viewport);
		~CameraMotion();

		void startMotion(int x, int y, ACTIONS action);
		void motion(int x, int y);

	private:
		void _pan(int x, int y);
		void _zoom(int x, int y);
		void _orbit(int x, int y);

		CameraPtr _camera;
		ViewportPtr _viewport;

		int _startX;
		int _startY;

		ACTIONS _action;
	};
}