#pragma once

#include "../../../BaseClasses/Renderer.h"

namespace myGame::Object
{
	class RectRenderer : public mySystem::Renderer
	{
	public:
		RENDERER_CLASS;

	public:
		myMath::Vector2 size;

	public:
		virtual void Initialize() override;
		virtual void Finalize() override;
		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void End() override;
		virtual void Draw() override;

	private:
		myMath::Vector2 _screenPos;
	};
}