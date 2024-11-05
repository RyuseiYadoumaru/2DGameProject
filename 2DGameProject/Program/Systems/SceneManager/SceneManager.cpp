#include "SceneManager.h"
#include "../ObjectManager/GameObjectManager.h"

#include "../../Game/Scene/TitleScene.h"
#include "../../Game/Scene/MainGameScene.h"
#include "../../Game/Scene/GameClearScene.h"

using namespace Downwell;

namespace mySystem
{
	shared_ptr<IScene> SceneManager::_currentScene = nullptr;
	string SceneManager::_nextSceneName = "";
	unordered_map<string, shared_ptr<IScene>> SceneManager::_sceneMap = {};

	void SceneManager::LoadScene(string sceneName)
	{
		if (_sceneMap.contains(sceneName) == false)
		{
			cout << sceneName << "‚Í“o˜^‚³‚ê‚Ä‚¢‚Ü‚¹‚ñ" << endl;
			return;
		}

		_nextSceneName = sceneName;
	}


	void SceneManager::Initialize()
	{
		AddScene<TitleScene>();
		AddScene<MainGameScene>();
		AddScene<GameClearScene>();

		if (_currentScene == nullptr)
		{
			printf("ƒV[ƒ“‚ª“o˜^‚³‚ê‚Ä‚¢‚Ü‚¹‚ñ\n");
			return;
		}
		_currentScene->OnEnter();
		_nextSceneName = "";
	}


	void SceneManager::SceneUpdate()
	{
		_currentScene->OnUpdate();
	}


	void SceneManager::ChangeScene()
	{
		if (_nextSceneName == "") return;

		_currentScene->OnExit();
		_currentScene = _sceneMap[_nextSceneName];
		_currentScene->OnEnter();
		_nextSceneName = "";
	}


	void SceneManager::Finalize()
	{
		_currentScene->OnExit();
		_currentScene = nullptr;
		for (auto& scene : _sceneMap)
		{
			scene.second = nullptr;
		}
	}
}