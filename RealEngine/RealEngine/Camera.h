#pragma once
#include "ISceneObject.h"

namespace RealEngine 
{
	class Camera : public ISceneObject
	{
	public:
		Camera();
		~Camera();

		void draw();
	};
}