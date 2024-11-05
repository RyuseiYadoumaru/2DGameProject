#include "DxLib.h"

#include "TextMeshRenderer.h"
#include "Camera.h"
#include "../Generic/GameObject.h"
#include "../../Maths/Vector2.h"

namespace myGame::Object
{
	void TextMeshRenderer::LateUpdate()
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
	void TextMeshRenderer::Draw()
	{
		bool active = GetContext().IsActive();
		if (active == false) return;

		// DXLibÇÕç∂è„Ç™äÓèÄÇÃÇΩÇﬂê^ÇÒíÜÇ©ÇÁç∂è„Ç…åvéZÇµÇ»Ç®Ç∑
		int renderPosX = static_cast<int>(_screenPos.x);
		int renderPosY = static_cast<int>(_screenPos.y);

		int renderColorR = static_cast<int>(color.r);
		int renderColorG = static_cast<int>(color.g);
		int renderColorB = static_cast<int>(color.b);
		int renderColorA = static_cast<int>(color.a);

		int renderFontSize = static_cast<int>(_fontSize);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, renderColorA);

		if (_fontHandle != NULL)
		{
			int dxColor = GetColor(renderColorR, renderColorG, renderColorB);
			DrawStringFToHandle(_screenPos.x, _screenPos.y, _textStr.c_str(), dxColor, _fontHandle);
		}

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}