#include "Camera.h"

#include <glm\gtc\matrix_transform.hpp>

using namespace Good;

Camera::Camera(const ViewportPtr& viewport) :
_type(PERSPECTIVE),
_from(0.0, 0.0, -5.0),
_to(0.0, 0.0, 0.0),
_up(0.0, 1.0, 0.0),
_fovy(45.0f),
_zMin(0.01f), _zMax(100.0f),
_viewport(viewport)
{
	_updateViewMatrix();
	_updateProjectionMatrix();
}


Camera::~Camera()
{
}

void Camera::setType(CAMERA_TYPE type)
{
	_type = type;
	_updateProjectionMatrix();
}

Camera::CAMERA_TYPE Camera::type() const
{
	return _type;
}

void Camera::setFrom(const glm::vec3& from)
{
	_from = from;
	_updateViewMatrix();
}

void Camera::setTo(const glm::vec3& to)
{
	_to = to;
	_updateViewMatrix();
}

void Camera::setUp(const glm::vec3& up)
{
	_up = up;
	_updateViewMatrix();
}

void Camera::setZmin(float zMin)
{
	_zMin = zMin;
	_updateProjectionMatrix();
}

void Camera::setZMax(float zMax)
{
	_zMax = zMax;
	_updateProjectionMatrix();
}

void Camera::setFovY(float fovY)
{
	_fovy = fovY;
	_updateProjectionMatrix();
}

glm::vec3 Camera::from() const
{
	return _from;
}

glm::vec3 Camera::to() const
{
	return _to;
}

glm::vec3 Camera::up() const
{
	return _up;
}

float Camera::zMin() const
{
	return _zMin;
}

float Camera::zMax() const
{
	return _zMax;
}

float Camera::fovY() const
{
	return _fovy;
}

glm::mat4 Camera::viewMatrix() const
{
	return _viewMatrix;
}

glm::mat4 Camera::projectionMatrix() const
{
	return _projectionMatrix;
}

void Camera::_updateProjectionMatrix()
{
	if (_type == ORTHOGRAPHIC)
		_projectionMatrix = glm::ortho((float)_viewport->X(), (float)_viewport->X() + (float)_viewport->width(), (float)_viewport->Y(), (float)_viewport->Y() + (float)_viewport->height(), (float)_zMin, (float)_zMax);
	else
		_projectionMatrix = glm::perspective(_fovy, _viewport->aspect(), _zMin, _zMax);
}

void Camera::_updateViewMatrix()
{
	_viewMatrix = glm::lookAt(_from, _to, _up);
}
