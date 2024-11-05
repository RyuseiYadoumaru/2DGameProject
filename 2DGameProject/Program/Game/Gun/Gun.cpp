#include "Gun.h"
#include "Bullet.h"

#include "../Include/SystemInclude.h"

namespace Downwell
{
#pragma region  Gun Methots

	void Gun::Reload()
	{
		_remainingBulletsNum = MAX_BULLETS_NUM;
		cout << "リロード:::" << _remainingBulletsNum << std::endl;
		if (_gunUIManager != nullptr) _gunUIManager->ReloadUI(*this);
	}

	void Gun::Fire()
	{
		if (isFire == true) return;

		if (_remainingBulletsNum <= 0)
		{
			_remainingBulletsNum = 0;
			return;
		}
		// 弾を減らす
		_remainingBulletsNum--;
		if(_gunUIManager != nullptr) _gunUIManager->DecreaseUI(_remainingBulletsNum);

		// プレイヤーの座標と合わせるため
		// LateUpdateで生成する
		isFire = true;

		SoundManager::Play("Fire_1");	
	}

#pragma endregion

#pragma region  System Callback Methots

	void Gun::Start()
	{
		_remainingBulletsNum = MAX_BULLETS_NUM;

		_fireOffset.Set(0.0f, -15.0f);

		isFire = false;

		// UI生成
		auto gunUIObject = GameObject::Find("GunUIManager");
		if (gunUIObject == nullptr) return;

		_gunUIManager = gunUIObject->GetComponent<GunUIManager>();
		if (_gunUIManager == nullptr)
		{
			printf("Not Instance GunUIManager\n");
			return;
		}		
		_gunUIManager->Create(*this);
	}

	void Gun::End()
	{
		_gunUIManager = nullptr;
	}

	void Gun::LateUpdate()
	{
		if (isFire == false) return;

		// 弾生成
		auto bullet = GameObject::Instance<Bullet>("Bullet" + _remainingBulletsNum, Tag::Bullet);
		bullet->GetTrans().position = _transform->position + _fireOffset;

		// 弾は左右に反動が起きる
		_recoil *= -1.0f;
		bullet->SetRecoil(_recoil);

		isFire = false;
	}

#pragma endregion

}