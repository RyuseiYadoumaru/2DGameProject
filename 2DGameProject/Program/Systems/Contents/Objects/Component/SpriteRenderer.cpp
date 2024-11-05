#include "DxLib.h"
#include "SpriteRenderer.h"
#include "Camera.h"

#include "../../../../Systems/RenderingManager/RenderingManager.h"
#include "../Generic/GameObject.h"
#include "../../Maths/Vector2.h"

namespace myGame::Object
{
	void SpriteRenderer::SetSprite(string fileName)
	{
		_spriteData = mySystem::RenderingManager::LoadSprite(fileName);
	}

	void SpriteRenderer::Initialize()
	{
		SetOrder(1000);
		size.Set(100.0f, 100.0f);
	}


	void SpriteRenderer::Finalize()
	{
	}


	void SpriteRenderer::Start()
	{
		mySystem::RenderingManager::Register(*this);
	}


	void SpriteRenderer::Update()
	{

	}


	void SpriteRenderer::LateUpdate()
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


	void SpriteRenderer::End()
	{
		mySystem::RenderingManager::Remove(*this);
	}


	void SpriteRenderer::Draw()
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

		if (_spriteData == NULL)
		{
			DrawBox(pos.x, pos.y, pos.x + size.x, pos.y + size.y,
				GetColor(renderColorR, renderColorG, renderColorB), TRUE);
		}
		else
		{
			DrawModiGraph(pos.x, pos.y,
						 (pos.x + size.x), pos.y,
						 (pos.x + size.x),(pos.y + size.y),
						  pos.x, (pos.y + size.y),
						  _spriteData, TRUE);
		}

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	}
}