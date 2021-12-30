#pragma once
#include "IBaseObject.h"

namespace RealEngine 
{
	class Camera : public IBaseObject
	{
	public:
		Camera();
		~Camera();

		void draw();
	};
}