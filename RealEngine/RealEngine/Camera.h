#pragma once
#include "IBaseObject.h"
#include "Math.h"
#include "Matrix.h"

namespace RealEngine 
{
	class Camera : public IBaseObject
	{
	public:
		Camera();
		~Camera();

	public:
		virtual void draw() {};
		virtual void update(float deltaTime) {};

		virtual void onEnter() {};
		virtual void onExit() {};

		virtual void updateTransform(Matrix4 view, Matrix4 projection) {};
		
	public:
		Matrix4 getViewMatrix();
		Matrix4 getProjectionMatrix();
		Vector3f getViewPosition();

	private:
		Matrix4 lookAt(Vector3f&, Vector3f&, Vector3f&);

	private:
		// œ‡ª˙Œª÷√
		Vector3f _position;
		Vector3f _front;
		Vector3f _up;
	};
}