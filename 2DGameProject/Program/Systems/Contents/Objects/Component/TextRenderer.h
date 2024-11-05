#pragma once

#include "../../../BaseClasses/Renderer.h"

namespace myGame::Object
{
	class TextRenderer : public mySystem::Renderer
	{
	public:
		RENDERER_CLASS;

	public:
		void SetText(string inText)  noexcept { _textStr = inText; }
		void SetFontSize(float size);
		void SetFontThick(float thick);

	protected:
		string _textStr = "";
		float _fontSize = 10.0f;
		float _fontThick = 40.0f;

		myMath::Vector2 _screenPos;

		int _fontHandle = NULL;

#pragma region  SystemCallback Function
	public:
		virtual void Initialize() override;
		virtual void Finalize() override;
		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void End() override;
		virtual void Draw() override;
#pragma endregion

	};
}