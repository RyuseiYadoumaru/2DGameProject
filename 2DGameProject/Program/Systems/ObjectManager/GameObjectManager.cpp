#include "GameObjectManager.h"

#include "../Contents/Objects/Generic/GameObject.h"
#include "../BaseClasses/Component.h"

namespace mySystem
{
	GameObjectManager::GameObjectContainer		GameObjectManager::_gameObjectList;
	vector<GameObjectManager::GameObjectPtr>	GameObjectManager::_instanceObjectList;
	vector<unsigned int>						GameObjectManager::_destoroyObjectList;
	

	void GameObjectManager::Add(GameObjectManager::GameObjectPtr object)
	{
		_instanceObjectList.push_back(object);
	}

	void GameObjectManager::Remove(myGame::Object::GameObject* object)
	{
		for (auto& objId : _destoroyObjectList)
		{
			if (objId == object->GetID()) return;
		}
		_destoroyObjectList.push_back(object->GetID());
	}

	myGame::Object::GameObject* GameObjectManager::Get(string name)
	{
		for (auto& obj : _gameObjectList)
		{
			if (obj.second->GetName() == name)
			{
				return obj.second.get();
			}
		}
		return nullptr;
	}

	void GameObjectManager::Initialize()
	{
		_gameObjectList.clear();
		_instanceObjectList.clear();
		_destoroyObjectList.clear();
	}

	void GameObjectManager::Update()
	{
		ObjectDestroy();

		ObjectInstance();
	}

	void GameObjectManager::ObjectUpdate()
	{
		for (auto& obj : _gameObjectList)
		{
			bool active = obj.second->IsActive();
			if (active)
			{
				obj.second->Update();
			}
		}
	}

	void GameObjectManager::ObjectLateUpate()
	{
		for (auto& obj : _gameObjectList)
		{
			bool active = obj.second->IsActive();
			if (active)
			{
				obj.second->LateUpdate();
			}
		}
	}

	void GameObjectManager::Finalize()
	{
		_gameObjectList.clear();
		_instanceObjectList.clear();
		_destoroyObjectList.clear();
	}

	void GameObjectManager::SceneInitialize()
	{
		for (auto& object : _gameObjectList)
		{
			object.second->Initialize();
		}
		for (auto& object : _gameObjectList)
		{
			object.second->Start();
		}
	}

	void GameObjectManager::SceneFinalize()
	{
		ObjectDestroy();

		for (auto& object : _gameObjectList)
		{
			object.second->End();
		}
		for (auto& object : _gameObjectList)
		{
			object.second->Finalize();
			object.second.reset();
		}

		_gameObjectList.clear();

	}

	void GameObjectManager::ObjectInstance()
	{
		// �I�u�W�F�N�g������
		vector<GameObjectPtr> initializedObjectList;
		for (auto& obj : _instanceObjectList)
		{
			obj->Initialize();
			initializedObjectList.push_back(obj);
		}
		_instanceObjectList.clear();

		// �I�u�W�F�N�g����
		for (auto& obj : initializedObjectList)
		{
			unsigned int id = obj->GetID();
			_gameObjectList[id] = obj;
			obj->Start();
		}
		initializedObjectList.clear();
	}

	void GameObjectManager::ObjectDestroy()
	{
		// �I�u�W�F�N�g�I������
		for (auto& objId : _destoroyObjectList)
		{
			_gameObjectList[objId]->End();
		}

		// �I�u�W�F�N�g�폜����
		for (auto& objId : _destoroyObjectList)
		{
			_gameObjectList[objId]->Finalize();
			_gameObjectList.erase(objId);
		}
		_destoroyObjectList.clear();
	}
}