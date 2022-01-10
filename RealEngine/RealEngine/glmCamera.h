#pragma once
#include "Vector.h"
#include "Matrix.h"
#include "Math.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace RealEngine
{
	class glmCamera
	{
	public:
		glmCamera();
		~glmCamera();

		void update(float deltaTime);

	public:
		Matrix4 getViewMatrix();
		Matrix4 getProjectionMatrix();
		Vector3f getViewPosition();

	private:
		Matrix4 lookAt(const Vector3f&, const Vector3f&, const Vector3f&);

		Vector2d _lastCursorPosition;
		float yaw = -90.0f;
		float pitch = 0.0f;
	private:
		// œ‡ª˙Œª÷√
		glm::vec3 _position;
		glm::vec3 _front;
		glm::vec3 _up;
	};
}