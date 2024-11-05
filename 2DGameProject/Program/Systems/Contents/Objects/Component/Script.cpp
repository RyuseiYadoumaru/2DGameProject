#include "Script.h"

#include "Transform.h"
#include "../Generic/GameObject.h"

namespace myGame::Object
{
	void Script::Initialize()
	{
		SetOrder(100);
		_transform = &GetContext().GetTrans();
		Setup();
	}

	void Script::Finalize()
	{
		_transform = nullptr;
	}
}