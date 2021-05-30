#pragma once
#include "IRuntimeModule.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "RenderInfo.h"

namespace RealEngine {
	class OpenglDriver :public IRuntimeModule 
	{
	public:
		virtual int Initialize() { return 0; };
		virtual void Finalize() {};
		virtual void Tick() {};

		static OpenglDriver& getInstance()
		{
			static OpenglDriver driver;
			return driver;
		}
	public:
		OpenglDriver();
		~OpenglDriver();

		// »æÖÆÈý½ÇÐÎ
		void drawTriangle();

		void loadShaderTest();

		void draw(RenderInfo renderInfo);
	};
}