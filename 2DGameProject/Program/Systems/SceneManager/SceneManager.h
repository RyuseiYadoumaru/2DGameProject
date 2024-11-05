#pragma once
#include "../Typedef/Typedef.h"
namespace mySystem
{
	class IScene
	{
	public:
		virtual void OnEnter() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnExit() = 0;
	};

	class SceneManager final
	{
	public:
		static void LoadScene(string sceneName);

		template<class SCENE>
		static void AddScene()
		{
			string sceneNameClass = typeid(SCENE).name();
			
			// クラス名のみ抽出する
			size_t index = sceneNameClass.find_last_of(":");
			size_t length = sceneNameClass.length() - index;
			string sceneName = sceneNameClass.substr(index + 1, length);

			if (_sceneMap.contains(sceneName))
			{
				cout << sceneName << "はすでに登録されています" << endl;
				return;
			}
			_sceneMap[sceneName] = make_shared<SCENE>(sceneName);
			if (_currentScene == nullptr)
			{
				// 最初に登録されたシーンを初期シーンにする
				_currentScene = _sceneMap[sceneName];
			}
		}

	public:
		static void Initialize();
		static void SceneUpdate();
		static void ChangeScene();
		static void Finalize();

	private:
		static shared_ptr<IScene> _currentScene;
		static string _nextSceneName;
		static unordered_map<string, shared_ptr<IScene>> _sceneMap;

	};
}