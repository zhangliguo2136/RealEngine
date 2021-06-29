#pragma once


namespace RealEngine
{
	class ISceneObject
	{
	public:
		virtual ~ISceneObject() {};

		virtual void draw() = 0;
		virtual void update(float deltaTime) = 0;
	};
}