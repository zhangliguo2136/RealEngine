
#include "BaseApplication.h"

int RealEngine::BaseApplication::Initialize()
{
	m_bQuit = true;

	return 0;
}
void RealEngine::BaseApplication::Finalize()
{

}
void RealEngine::BaseApplication::Tick()
{

}
bool RealEngine::BaseApplication::IsQuit()
{
	return m_bQuit;
}