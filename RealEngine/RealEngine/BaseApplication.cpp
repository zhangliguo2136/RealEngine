
#include "BaseApplication.h"
#include "SceneManager.h"
#include "PhysicsSystem.h"
#include "ScriptEngine.h"


bool RealEngine::BaseApplication::m_bQuit = false;

int RealEngine::BaseApplication::Initialize()
{
	//auto& scriptInstance = ScriptEngine::getInstance();

	//scriptInstance.runScript("../Resource/script/main.rs");

	return 0;
}
void RealEngine::BaseApplication::Finalize()
{

}
void RealEngine::BaseApplication::Tick()
{
	PhysicEngine::PhysicsSystem& pSystem = PhysicEngine::PhysicsSystem::getInstance();
	pSystem.Tick();

	SceneManager& pManager = SceneManager::getInstance();
	pManager.Tick();
}
bool RealEngine::BaseApplication::IsQuit()
{
	return m_bQuit;
}