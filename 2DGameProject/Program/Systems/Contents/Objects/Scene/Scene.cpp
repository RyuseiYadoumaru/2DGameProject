#include "Scene.h"

#include "../../../ObjectManager/GameObjectManager.h"
#include "../../../RenderingManager/RenderingManager.h"
namespace myGame::Object
{
	void Scene::SetupObject()
	{
		// empty
	}

	void Scene::BeginPlay()
	{
		// empty

	}

	void Scene::Tick()
	{
		// empty

	}

	void Scene::EndPlay()
	{
		// empty
	}


#pragma region  Call SceneManager Function


	void Scene::OnEnter()
	{
		SetupObject();
		mySystem::GameObjectManager::SceneInitialize();
		BeginPlay();
	}


	void Scene::OnUpdate()
	{
		Tick();
	}


	void Scene::OnExit()
	{
		EndPlay();
		mySystem::GameObjectManager::SceneFinalize();
		mySystem::RenderingManager::SceneFinalize();
	}

#pragma endregion

}