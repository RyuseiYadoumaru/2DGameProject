#include "DxLib.h"
#include "RectRenderer.h"
#include "Camera.h"

#include "../../../../Systems/RenderingManager/RenderingManager.h"
#include "../Generic/GameObject.h"
#include "../../Maths/Vector2.h"

namespace myGame::Object
{
	void RectRenderer::Initialize()
	{
		SetOrder(1000);
		color.Set(255.0f, 0.0f, 0.0f, 255.0f);
		size.Set(100.0f, 100.0f);
	}


	void RectRenderer::Finalize()
	{
	}


	void RectRenderer::Start()
	{
		mySystem::RenderingManager::Register(*this);
	}


	void RectRenderer::Update()
	{

	}


	void RectRenderer::LateUpdate()
	{
		const Transform& ownerTrans = GetContext().GetTrans();
		if (Camera::EnableMainCaera() == false)
		{
			_screenPos = ownerTrans.position;
			return;
		}
		const myMath::Vector2& cameraPos = Camera::GetMainCamera().GetCameraPosition();
		_screenPos = ownerTrans.position - cameraPos;
	}


	void RectRenderer::End()
	{
		mySystem::RenderingManager::Remove(*this);
	}


	void RectRenderer::Draw()
	{
		bool active = GetContext().IsActive();
		if (active == false) return;

		// DXLibÇÕç∂è„Ç™äÓèÄÇÃÇΩÇﬂê^ÇÒíÜÇ©ÇÁç∂è„Ç…åvéZÇµÇ»Ç®Ç∑
		myMath::Vector2 pos = CalcLeftUpPos(_screenPos, size);
		int renderPosX = static_cast<int>(pos.x);
		int renderPosY = static_cast<int>(pos.y);
		int renderSizeX = static_cast<int>(size.x);
		int renderSizeY = static_cast<int>(size.y);

		int renderColorR = static_cast<int>(color.r);
		int renderColorG = static_cast<int>(color.g);
		int renderColorB = static_cast<int>(color.b);
		int renderColorA = static_cast<int>(color.a);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, renderColorA);


		DrawBox(pos.x, pos.y, pos.x + size.x, pos.y + size.y,
			GetColor(renderColorR, renderColorG, renderColorB), TRUE);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	}
}