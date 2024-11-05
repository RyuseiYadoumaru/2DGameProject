#include "Life.h"
#include "../Include/SystemInclude.h"

namespace Downwell
{
	void Life::OnDamage(int damage)
	{
		_lifePoint -= damage;

		if (_lifeUIManager != nullptr)
		{
			_lifeUIManager->DamageUI(_lifePoint);
		}

		if (_lifePoint <= 0)
		{
			_lifePoint = 0;
		}
	}

	void Life::OnRecovery(int recovery)
	{
		//_lifePoint += recovery;
		//if (_lifePoint >= MAX_LIFEPOINT_NUM) _lifePoint = MAX_LIFEPOINT_NUM;
	}

#pragma region  System Callback Functions

	void Life::Start()
	{
		_lifePoint = MAX_LIFEPOINT_NUM;
		auto lifeUIObject = GameObject::Find("LifeUIManager");
		if (lifeUIObject == nullptr) return;

		_lifeUIManager = lifeUIObject->GetComponent<LifeUIManager>();
		if (_lifeUIManager == nullptr)
		{
			printf("Not Instance LifeUIManager\n");
			return;
		}

		_lifeUIManager->Create(_lifePoint);
	}

	void Life::End()
	{
		_lifePoint = 0;
		_lifeUIManager = nullptr;
	}

#pragma endregion

}