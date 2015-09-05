#include "Camera.h"

#include "../../Tools/Logger/LogConsole.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace Good;

Camera::Camera(const ViewportPtr& viewport, const char* name) :
GoodObject(name),
_type(PERSPECTIVE),
_from(0.0, 0.0, 5.0),
_to(0.0, 0.0, 0.0),
_up(0.0, 1.0, 0.0),
_fovy(45.0f),
_zMin(0.01f), _zMax(100.0f),
_viewport(viewport)
{
#ifdef _DEBUG
	_logger = ILoggerPtr(new LogConsole);
	_logger->write("Create", this);
#endif
	_updateViewMatrix();
	_updateProjectionMatrix();
}


Camera::~Camera()
{
#ifdef _DEBUG
	_logger->write("Delete", this);
#endif
}

void Camera::setType(CAMERA_TYPE type)
{
#ifdef _DEBUG
	std::string typeStr;
	switch (type)
	{
	case Good::Camera::PERSPECTIVE:
		typeStr = "PERSPECTIVE";
		break;
	case Good::Camera::ORTHOGRAPHIC:
		typeStr = "ORTHOGRAPHIC";
		break;
	}
	_logger->write("Change type: " + typeStr, this);
#endif
	_type = type;
	_updateProjectionMatrix();
}

Camera::CAMERA_TYPE Camera::type() const
{
	return _type;
}

void Camera::setFrom(const glm::vec3& from)
{
#ifdef _DEBUG
	std::string fromStr;
	fromStr += std::to_string(from.x);
	fromStr += " ";
	fromStr += std::to_string(from.y);
	fromStr += " ";
	fromStr += std::to_string(from.z);
	fromStr += " ";
	_logger->write("Change from " + fromStr, this);
#endif
	_from = from;
	_updateViewMatrix();
}

void Camera::setFrom(float x, float y, float z)
{
	setFrom(glm::vec3(x, y, z));
}

void Camera::setTo(const glm::vec3& to)
{
#ifdef _DEBUG
	std::string toStr;
	toStr += std::to_string(to.x);
	toStr += " ";
	toStr += std::to_string(to.y);
	toStr += " ";
	toStr += std::to_string(to.z);
	toStr += " ";
	_logger->write("Change to " + toStr, this);
#endif
	_to = to;
	_updateViewMatrix();
}

void Camera::setTo(float x, float y, float z)
{
	setTo(glm::vec3(x, y, z));
}

void Camera::setUp(const glm::vec3& up)
{
#ifdef _DEBUG
	std::string upStr;
	upStr += std::to_string(up.x);
	upStr += " ";
	upStr += std::to_string(up.y);
	upStr += " ";
	upStr += std::to_string(up.z);
	upStr += " ";
	_logger->write("Change to " + upStr, this);
#endif
	_up = up;
	_updateViewMatrix();
}

void Camera::setUp(float x, float y, float z)
{
	setUp(glm::vec3(x, y, z));
}

void Camera::setZmin(float zMin)
{
#ifdef _DEBUG
	std::string zMinStr;
	zMinStr += std::to_string(zMin);
	_logger->write("Change to " + zMinStr, this);
#endif
	_zMin = zMin;
	_updateProjectionMatrix();
}

void Camera::setZMax(float zMax)
{
#ifdef _DEBUG
	std::string zMaxStr;
	zMaxStr += std::to_string(zMax);
	_logger->write("Change to " + zMaxStr, this);
#endif
	_zMax = zMax;
	_updateProjectionMatrix();
}

void Camera::setFovY(float fovY)
{
#ifdef _DEBUG
	std::string fovYStr;
	fovYStr += std::to_string(fovY);
	_logger->write("Change to " + fovYStr, this);
#endif
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
#ifdef _DEBUG
	_logger->write("Update Projection Matrix", this);
#endif
	if (_type == ORTHOGRAPHIC)
		_projectionMatrix = glm::ortho((float)_viewport->X(), (float)_viewport->X() + (float)_viewport->width(), (float)_viewport->Y(), (float)_viewport->Y() + (float)_viewport->height(), (float)_zMin, (float)_zMax);
	else
		_projectionMatrix = glm::perspective(_fovy, _viewport->aspect(), _zMin, _zMax);
}

void Camera::_updateViewMatrix()
{
#ifdef _DEBUG
	_logger->write("Update View Matrix", this);
#endif
	_viewMatrix = glm::lookAt(_from, _to, _up);
}
