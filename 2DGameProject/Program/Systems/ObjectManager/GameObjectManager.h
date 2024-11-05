#pragma once
#include "../Typedef/Typedef.h"

enum class Tag;

namespace myGame::Object
{
	class GameObject;
}

namespace mySystem
{
	class IComponent;

	class GameObjectManager final
	{
		using Order = unsigned int;
		using GameObjectPtr = shared_ptr<myGame::Object::GameObject>;
		using GameObjectContainer = map<unsigned int, GameObjectPtr>;

	public:
		template <class T>
		static shared_ptr<T> SceneEntry(string name, Tag tag = Tag::Default)
		{
			shared_ptr<T> gameObject = make_shared<T>(name, tag);
			unsigned int id = gameObject->GetID();
			_gameObjectList[id] = gameObject;
			return gameObject;
		}

		static void Add(GameObjectPtr object);

		static void Remove(myGame::Object::GameObject* object);
		static  myGame::Object::GameObject* Get(string name);

	public:
		static void Initialize();
		static void Update();
		static void ObjectUpdate();
		static void ObjectLateUpate();
		static void Finalize();

		static void SceneInitialize();
		static void SceneFinalize();

	private:

		// ゲームオブジェクト
		static GameObjectContainer _gameObjectList;
		static vector<GameObjectPtr> _instanceObjectList;
		static vector<unsigned int> _destoroyObjectList;

	private:
		static void ObjectInstance();
		static void ObjectDestroy();

	};
}