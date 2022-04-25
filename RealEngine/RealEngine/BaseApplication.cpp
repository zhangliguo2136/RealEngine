
#include "BaseApplication.h"
#include "SceneManager.h"
#include "PhysicsSystem.h"


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
	PhysicEngine::PhysicsSystem& pSystem = PhysicEngine::PhysicsSystem::getInstance();
	pSystem.Tick(0);

	SceneManager& pManager = SceneManager::getInstance();
	pManager.Tick();
}
bool RealEngine::BaseApplication::IsQuit()
{
	return m_bQuit;
}