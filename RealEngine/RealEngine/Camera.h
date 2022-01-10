#pragma once
#include "Vector.h"
#include "Matrix.h"
#include "Math.h"

namespace RealEngine 
{
	class Camera
	{
	public:
		Camera();
		~Camera();

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
		Vector3f _position;
		Vector3f _front;
		Vector3f _up;
	};
}