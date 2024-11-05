#pragma once
#include "Object.h"

namespace myGame::Object
{
	class GameObject;
}


#define COMPONENT_CLASS using mySystem::IComponent::IComponent;


namespace mySystem
{

	class IComponent : public Object
	{
	public:
		IComponent(string name) :
			Object(name),  _order(100)
		{

		}

		~IComponent() = default;

	public:
		virtual void Initialize() = 0;
		virtual void Finalize() = 0;

	public:
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void SecondUpdate() { }
		virtual void LateUpdate() = 0;
		virtual void End() = 0;

	public:
		void SetContext(myGame::Object::GameObject * context) noexcept { _context = context; }
		myGame::Object::GameObject& GetContext() const noexcept { return *_context; }

		const unsigned int GetOrder() const noexcept { return _order; }
		void SetOrder(Order order) noexcept { _order = order; }

	private:
		myGame::Object::GameObject* _context = nullptr;
		Order _order;

	};

}