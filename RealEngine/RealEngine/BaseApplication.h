#pragma once
#include "IApplication.h"

namespace RealEngine 
{
	class BaseApplication : public IApplication 
	{
	public:
		virtual int Initialize();
		virtual void Finalize();
		virtual void Tick();
		virtual bool IsQuit();

	protected:
		static bool m_bQuit;
	};
}