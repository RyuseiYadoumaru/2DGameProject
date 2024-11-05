#pragma once
#include "../../../Typedef/Typedef.h"

#include "../../../ObjectManager/GameObjectManager.h"

#include "../../../BaseClasses/Object.h"
#include "../../../BaseClasses/Component.h"

#include "../Component/Transform.h"


namespace myGame::Object
{
	template <class T>
	concept TComponent = requires(T & comp)
	{
		comp.GetContext();
		comp.Initialize();
	};

	using ComponentPtr = shared_ptr<mySystem::IComponent>;
	using ComponentContainer = map<Order,vector<ComponentPtr>>;

	template<TComponent T>
	using TComponentPtr = shared_ptr<T>;

}