#include "DxLib.h"
#include "TextRenderer.h"
#include "Camera.h"

#include "../../../../Systems/RenderingManager/RenderingManager.h"
#include "../Generic/GameObject.h"
#include "../../Maths/Vector2.h"

namespace myGame::Object
{
	void TextRenderer::SetFontSize(float size)
	{
		if (size <= 0) return;
		_fontSize = size;
		_fontHandle = CreateFontToHandle(NULL,
			static_cast<int>(_fontSize),
			static_cast<int>(_fontThick),
			DX_FONTTYPE_NORMAL);
	}
	void TextRenderer::SetFontThick(float thick)
	{
		if (thick <= 0) return;
		_fontThick = thick;
		_fontHandle = CreateFontToHandle(NULL,
			static_cast<int>(_fontSize),
			static_cast<int>(_fontThick),
			DX_FONTTYPE_NORMAL);
	}
	void TextRenderer::Initialize()
	{
		SetOrder(1000);
		_fontHandle = CreateFontToHandle(NULL,
			static_cast<int>(_fontSize),
			static_cast<int>(_fontThick),
			DX_FONTTYPE_NORMAL);
	}

	void TextRenderer::Finalize()
	{
		DeleteFontToHandle(_fontHandle);
		_textStr.clear();
	}

	void TextRenderer::Start()
	{
		mySystem::RenderingManager::Register(*this);
	}

	void TextRenderer::Update()
	{

	}

	void TextRenderer::LateUpdate()
	{
		const Transform& ownerTrans = GetContext().GetTrans();
		_screenPos = ownerTrans.position;
	}

	void TextRenderer::End()
	{
		mySystem::RenderingManager::Remove(*this);
	}

	void TextRenderer::Draw()
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