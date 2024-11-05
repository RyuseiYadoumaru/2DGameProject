#pragma once
#include "../Generic/GameObject.h"

#define CHARACTER_CLASS myGame::Object::Character::Character;
namespace myGame::Object
{
	class Character : public GameObject
	{
	public:
		GAMEOBJECT_CLASS
	};

}