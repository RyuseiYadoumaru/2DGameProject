#pragma once
#include "../Generic/GameObject.h"

#define  ITEM_CLASS myGame::Object::Item::Item;
namespace myGame::Object
{
	class Item : public GameObject
	{
	public:
		GAMEOBJECT_CLASS
	};
}