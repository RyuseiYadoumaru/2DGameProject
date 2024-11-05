#include "GunUI.h"
#include "Gun.h"

namespace Downwell
{
//****************************************************
//	Bullet UI Class
//****************************************************

#pragma region System Callback Functions

	void BulletUI::Setup()
	{
		_widget->size.Set(25.0f, 38.0f);
		_widget->color.Set(240.0f, 240.0f, 240.0f, 255.0f);
		_widget->SetLayer(50);
	}

	void BulletUI::BeginPlay()
	{
	}

	void BulletUI::Tick()
	{
	}

	void BulletUI::EndPlay()
	{
		_widget = nullptr;
	}

#pragma endregion

//****************************************************
//	Gun UI Manager Class
//****************************************************

	void GunUIManager::Create(const Gun& inGun)
	{
		int remainigBulletsNum = inGun.GetRemainingBulletsNum();
		for (int num = 0; num < remainigBulletsNum; num++)
		{
			auto ui = GameObject::Instance<BulletUI>("BulletUI" + num);
			
			Transform& trans = ui->GetTrans();
			trans.position.x = _transform->position.x;
			trans.position.y = _transform->position.y + (_bulletUIDistance * num);
			_bulletUIList.push_back(ui);
		}
	}

	void GunUIManager::ReloadUI(const Gun& inGun)
	{
		// écíeÇï\é¶Ç∑ÇÈÅ@
		int remainigBulletsNum = inGun.GetRemainingBulletsNum();
		for (int num = 0; num < remainigBulletsNum; num++)
		{
			_bulletUIList[num]->SetActive(true);
		}
	}

	void GunUIManager::DecreaseUI(const int index)
	{
		if (index >= _bulletUIList.size())
		{
			return;
		}

		_bulletUIList[index]->SetActive(false);
	}

#pragma region System Callback Functions

	void GunUIManager::Setup()
	{
		_transform->position.Set(950.0f, 140.0f);
		SetOrder(500);
	}

#pragma endregion

}