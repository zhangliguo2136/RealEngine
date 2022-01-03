#pragma once
class Matrix4;

namespace RealEngine
{
	class IBaseObject
	{
	public:
		virtual ~IBaseObject() {};

		virtual void draw() = 0;
		virtual void update(float deltaTime) = 0;

		virtual void onEnter() = 0;
		virtual void onExit() = 0;

		virtual void updateTransform(Matrix4 view, Matrix4 projection) = 0;
	};
}