
#include "BaseApplication.h"
#include "SceneManager.h"
#include "PhysicsSystem.h"
#include "ScriptEngine.h"
#include "UISystem.h"
#include "RenderSystem.h"
#include "MemoryManager.h"


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

	UISystem& uSystem = UISystem::getInstance();
	uSystem.Tick();

	RenderSystem& rSystem = RenderSystem::getInstance();
	rSystem.Tick();
}
bool RealEngine::BaseApplication::IsQuit()
{
	return m_bQuit;
}