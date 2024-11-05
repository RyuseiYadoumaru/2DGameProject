#include "GameSystem.h"

#include "../SceneManager/SceneManager.h"
#include "../ObjectManager/GameObjectManager.h"
#include "../RenderingManager/RenderingManager.h"
#include "../Sound/SoundManager.h"


#include "../Input/GamePad.h"
#include "../Timer/Timer.h"

namespace mySystem
{
	void GameSystem::Initialize()
	{
		RenderingManager::Initialize();
		GameObjectManager::Initialize();
		SceneManager::Initialize();
		SoundManager::SetUp();
	}


	void GameSystem::MainLoop()
	{
		GamePad::GetBuffer();
		RenderingManager::ClearBuffer();
		GameObjectManager::Update();
		GameObjectManager::ObjectUpdate();
		SceneManager::SceneUpdate();
		GameObjectManager::ObjectLateUpate();
		RenderingManager::Rendering();
		SceneManager::ChangeScene();
		Timer::Get().Update();
	}


	void GameSystem::Finalize()
	{
		GamePad::StopVibration();
		SoundManager::ShutDown();
		GameObjectManager::Finalize();
		SceneManager::Finalize();
		RenderingManager::Finalize();
	}

}