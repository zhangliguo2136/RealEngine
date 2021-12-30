
#include "BaseApplication.h"
#include "SceneManager.h"

#include "Model.h"

bool RealEngine::BaseApplication::m_bQuit = false;

int RealEngine::BaseApplication::Initialize()
{
	SceneManager& pManager = SceneManager::getInstance();

	Model* model = new Model("../Resource/model/diablo3_pose/diablo3_pose.obj");
	pManager.addSceneObject(model);

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