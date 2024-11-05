#pragma once

#include "TextRenderer.h"

namespace myGame::Object
{
	class TextMeshRenderer : public TextRenderer
	{
	public:
		TextRenderer::TextRenderer;

#pragma region  SystemCallback Function
	public:
		virtual void LateUpdate() override;
		virtual void Draw() override;
#pragma endregion

	};
}