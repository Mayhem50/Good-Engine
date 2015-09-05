#include "CameraMotion.h"

using namespace Good;

CameraMotion::CameraMotion(CameraPtr camera, ViewportPtr viewport) :
_camera(camera), _viewport(viewport),
_startX(0), _startY(0),
_action(ACTIONS::PAN)
{

}

CameraMotion::~CameraMotion()
{

}

void CameraMotion::startMotion(int x, int y, ACTIONS action)
{
	_startX = x;
	_startY = y;
	_action = action;
}

void CameraMotion::motion(int x, int y)
{
	switch (_action)
	{
	case Good::CameraMotion::PAN:
		_pan(x, y);
		break;
	case Good::CameraMotion::ORBIT:
		_orbit(x, y);
		break;
	case Good::CameraMotion::ZOOM:
		_zoom(x, y);
		break;
	}
}

void CameraMotion::_pan(int x, int y)
{	
	float dx = (float)(x - _startX) / 100.0;
	float dy = (float)(y - _startY) / 100.0;

	glm::vec3 translate(dx, dy, 0.0);
	_camera->setFrom(_camera->from() + translate);
	_camera->setTo(_camera->to() + translate);
}

void CameraMotion::_orbit(int x, int y)
{
}

void CameraMotion::_zoom(int x, int y)
{
}