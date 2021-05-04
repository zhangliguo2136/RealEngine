
#include "BaseApplication.h"
#include "SceneManager.h"

bool RealEngine::BaseApplication::m_bQuit = false;

int RealEngine::BaseApplication::Initialize()
{
	return 0;
}
void RealEngine::BaseApplication::Finalize()
{

}
void RealEngine::BaseApplication::Tick()
{
	SceneManager& pManager = SceneManager::getInstance();
	pManager.Tick();
}
bool RealEngine::BaseApplication::IsQuit()
{
	return m_bQuit;
}