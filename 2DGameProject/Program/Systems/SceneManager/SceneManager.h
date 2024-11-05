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
			
			// �N���X���̂ݒ��o����
			size_t index = sceneNameClass.find_last_of(":");
			size_t length = sceneNameClass.length() - index;
			string sceneName = sceneNameClass.substr(index + 1, length);

			if (_sceneMap.contains(sceneName))
			{
				cout << sceneName << "�͂��łɓo�^����Ă��܂�" << endl;
				return;
			}
			_sceneMap[sceneName] = make_shared<SCENE>(sceneName);
			if (_currentScene == nullptr)
			{
				// �ŏ��ɓo�^���ꂽ�V�[���������V�[���ɂ���
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