#pragma once
#include "GameObjectHeader.h"

#define  GAMEOBJECT_CLASS myGame::Object::GameObject::GameObject;

enum class Tag
{
	Default = 0,
	Player,
	Bullet,
	FloatingEnemy,
	CrawlEnemy,
	Block,
	MapSponer,
};

namespace myGame::Object
{
	class GameObject : public mySystem::Object
	{
	public:
		Transform& GetTrans() const noexcept { return *_transform.get(); }
		const Tag& GetTag() const noexcept { return _tag; }

	protected:
		shared_ptr<Transform> _transform;

	private:
		ComponentContainer _componentOrderList;
		Tag _tag;

	protected:
		virtual void Setup		() { /* empty */ }
		virtual void BeginPlay	() { /* empty */ }
		virtual void Tick		() { /* empty */ }
		virtual void LateTick	() { /* empty */ }
		virtual void EndPlay	() { /* empty */ }

#pragma region GameObject Function

	public:
		template<class T>
		static T* Instance(string name, Tag tag = Tag::Default)
		{
			shared_ptr<T> instance = make_shared<T>(name, tag);
			mySystem::GameObjectManager::Add(instance);
			return instance.get();
		}

		static void Destoy(GameObject* object)
		{
			mySystem::GameObjectManager::Remove(object);
		}

		static GameObject* Find(string name)
		{
			return mySystem::GameObjectManager::Get(name);
		}

		template<class T>
		static T* Find(string name)
		{
			GameObject* gameObject = mySystem::GameObjectManager::Get(name);
			T* typeGameObjet = dynamic_cast<T*>(gameObject);
			return typeGameObjet;
		}

#pragma endregion

#pragma region Constructor/Destructor

	public:
		GameObject(string name, Tag tag, bool active = true)
			: Object(name, active), _tag(tag)
		{
			_transform = AddComponent<Transform>();
		}
		GameObject(string name, bool active = true) 
			: Object(name, active), _tag(Tag::Default)
		{
			_transform = AddComponent<Transform>();
		}

		~GameObject() = default;

#pragma endregion

#pragma region  Component Function

	public:
		template<TComponent T>
		TComponentPtr<T> AddComponent()
		{
			string compNameClass = typeid(T).name();

			// ÉNÉâÉXñºÇÃÇ›íäèoÇ∑ÇÈ
			size_t index = compNameClass.find_last_of(":");
			size_t length = compNameClass.length() - index;
			string compName = compNameClass.substr(index + 1, length);

			TComponentPtr<T> component = std::make_shared<T>(compName);
			component->SetContext(this);
			component->Initialize();
			_componentOrderList[component->GetOrder()].push_back(component);
			return component;
		}

		template<TComponent T>
		TComponentPtr<T> GetComponent()
		{
			for (auto& componentList : _componentOrderList)
			{
				for (auto& comp : componentList.second)
				{
					auto component = std::dynamic_pointer_cast<T>(comp);
					if (component != nullptr) return component;
				}
			}
			return nullptr;
		}

#pragma endregion

#pragma region  System Function
	public:
		virtual void Initialize()
		{
			Setup();
		}

		void Start()
		{
			for (auto& compList : _componentOrderList)
			{
				for (auto& comp : compList.second)
				{
					comp->Start();
				}
			}

			BeginPlay();
		}

		void Update()
		{
			for (auto& compList : _componentOrderList)
			{
				for (auto& comp : compList.second)
				{
					if (comp->IsActive() == true)
					{
						comp->Update();
					}
				}
			}

			Tick();

			for (auto& compList : _componentOrderList)
			{
				for (auto& comp : compList.second)
				{
					if (comp->IsActive() == true)
					{
						comp->SecondUpdate();
					}
				}
			}
		}

		void LateUpdate()
		{
			LateTick();

			for (auto& compList : _componentOrderList)
			{
				for (auto& comp : compList.second)
				{
					if (comp->IsActive() == true)
					{
						comp->LateUpdate();
					}
				}
			}
		}


		void End()
		{
			for (auto& compList : _componentOrderList)
			{
				for (auto& comp : compList.second)
				{
					comp->End();
				}
			}

			EndPlay();
		}

		virtual void Finalize()
		{
			for (auto& compList : _componentOrderList)
			{
				for (auto& comp : compList.second)
				{
					comp->Finalize();
				}
			}
			_componentOrderList.clear();
		}
#pragma endregion

	};
}