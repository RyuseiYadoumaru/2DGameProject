#include "LifeUI.h"
#include "Life.h"

#include "../../Systems/RenderingManager/RenderingManager.h"

namespace Downwell
{
//****************************************************
//	Life UI Class
//****************************************************

	void LifeUI::Setup()
	{
		_widget->size.Set(42.0f * 0.85f, 36.0f * 0.85f);
		int uiData = mySystem::RenderingManager::LoadSprite("Life.png");
		_widget->SetUI(uiData);
		_widget->color.Set(200.0f, 10.0f, 70.0f, 255.0f);

		_widget->SetLayer(50);
	}

//****************************************************
//	Life UI Manager Class
//****************************************************

	void LifeUIManager::Create(int lifeNum)
	{
		for (int num = 0; num < lifeNum; num++)
		{
			auto ui = GameObject::Instance<LifeUI>("LifeUI" + num);

			Transform& trans = ui->GetTrans();
			trans.position.x = _transform->position.x + (_uiDistance * num);
			trans.position.y = _transform->position.y;
			_lifeUIList.push_back(ui);
		}
	}


	void LifeUIManager::DamageUI(int index)
	{
		if (index >= _lifeUIList.size()) return;
		_lifeUIList[index]->SetActive(false);
	}

#pragma region  System Callback Function

	void LifeUIManager::Setup()
	{
		_transform->position.Set(20.0f, 20.0f);
		SetOrder(500);
	}

#pragma endregion

}