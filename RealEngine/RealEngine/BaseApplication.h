#pragma once
#include "IApplication.h"

namespace RealEngine 
{
	class BaseApplication : public IApplication 
	{
	public:
		virtual int Initialize() override;
		virtual void Finalize() override;
		virtual void Tick() override;
		virtual bool IsQuit() override;
	protected:
		static bool m_bQuit;
	};
}