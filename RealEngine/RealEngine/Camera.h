#pragma once
#include "IBaseObject.h"
#include "Vector.h"
#include "Matrix.h"
#include "Math.h"

namespace RealEngine 
{
	class Camera : public IBaseObject
	{
	public:
		Camera();
		~Camera();

	public:
		virtual void draw() {};
		virtual void update(float deltaTime);

		virtual void onEnter() {};
		virtual void onExit() {};

		virtual void updateTransform(Matrix4 view, Matrix4 projection) {};
		
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
		// ���λ��
		Vector3f _position;
		Vector3f _front;
		Vector3f _up;
	};
}