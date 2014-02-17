#pragma once

#include "GoodObject.h"

#include "Viewport.h"

#ifdef _DEBUG
#include "ILogger.h"
#endif

#include <memory>
#include <glm\glm.hpp>

namespace Good
{
	class GOOD_DLL Camera : public GoodObject
	{
	public:
		enum CAMERA_TYPE
		{
			PERSPECTIVE,
			ORTHOGRAPHIC
		};

		Camera(const ViewportPtr& viewport);
		virtual ~Camera();

		void setType(CAMERA_TYPE type);
		CAMERA_TYPE type() const;

		void setFrom(const glm::vec3& from);
		void setTo(const glm::vec3& from);
		void setUp(const glm::vec3& from);
		void setZmin(float zMin);
		void setZMax(float zMax);
		void setFovY(float fovy);

		glm::vec3 from() const;
		glm::vec3 to() const;
		glm::vec3 up() const;
		float zMin() const;
		float zMax() const;
		float fovY() const;

		glm::mat4 viewMatrix() const;
		glm::mat4 projectionMatrix() const;

	private:
		Camera();
		void _updateProjectionMatrix();
		void _updateViewMatrix();

		glm::vec3 _from;
		glm::vec3 _to;
		glm::vec3 _up;

		glm::mat4 _viewMatrix;
		glm::mat4 _projectionMatrix;

		float _fovy;
		float _zMin;
		float _zMax;

		CAMERA_TYPE _type;

		ViewportPtr _viewport;

#ifdef _DEBUG
		ILoggerPtr _logger;
#endif
	};

	typedef std::shared_ptr<Camera> CameraPtr;
}

