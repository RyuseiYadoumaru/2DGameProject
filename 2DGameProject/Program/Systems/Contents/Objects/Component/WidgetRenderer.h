#pragma once

#include "../../../BaseClasses/Renderer.h"

#include "../../Maths/Color.h"
#include "../../Maths/Vector2.h"

namespace myGame::Object
{
	class WidgetRenderer : public mySystem::Renderer
	{
	public:
		RENDERER_CLASS;

	public:
		myMath::Vector2 size;

	public:
		void SetUI(int uiData) noexcept { _uiData = uiData; }

	private:
		int _uiData = NULL;

#pragma region  System Callback Function
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