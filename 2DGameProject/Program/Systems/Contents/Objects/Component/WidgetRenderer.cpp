#include "DxLib.h"
#include "WidgetRenderer.h"

#include "../../../../Systems/RenderingManager/RenderingManager.h"
#include "../Generic/GameObject.h"
namespace myGame::Object
{
	void WidgetRenderer::Initialize()
	{
		SetOrder(1000);
		color.Set(255.0f, 0.0f, 0.0f, 255.0f);
		size.Set(100.0f, 100.0f);
	}


	void WidgetRenderer::Finalize()
	{
	}


	void WidgetRenderer::Start()
	{
		mySystem::RenderingManager::Register(*this);
	}


	void WidgetRenderer::Update()
	{

	}


	void WidgetRenderer::LateUpdate()
	{

	}


	void WidgetRenderer::End()
	{
		mySystem::RenderingManager::Remove(*this);
	}


	void WidgetRenderer::Draw()
	{
		bool active = GetContext().IsActive();
		if (active == false) return;

		int renderColorR = static_cast<int>(color.r);
		int renderColorG = static_cast<int>(color.g);
		int renderColorB = static_cast<int>(color.b);
		int renderColorA = static_cast<int>(color.a);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, renderColorA);

		myMath::Vector2 pos = GetContext().GetTrans().position;
		if (_uiData == NULL)
		{
			DrawBox(pos.x, pos.y, pos.x + size.x, pos.y + size.y,
				GetColor(renderColorR, renderColorG, renderColorB), TRUE);
		}
		else
		{
			DrawModiGraph(pos.x, pos.y,
				(pos.x + size.x), pos.y,
				(pos.x + size.x), (pos.y + size.y),
				pos.x, (pos.y + size.y),
				_uiData, TRUE);
		}

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}