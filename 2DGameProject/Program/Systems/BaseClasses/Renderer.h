#pragma once
#include "Component.h"
#include "../Contents/Maths/Color.h"
#include "../Contents/Maths/Vector2.h"
#define  RENDERER_CLASS using mySystem::Renderer::Renderer;

namespace mySystem
{
	class Renderer : public IComponent
	{
	public:
		COMPONENT_CLASS;

	public:
		myMath::Color color;

	public:
		virtual void Draw() = 0;

	public:
		const int GetLayer() const noexcept { return _layer; }
		void SetLayer(int layer) noexcept { _layer = layer; }

	protected:
		int _layer = 0;

	protected:
		myMath::Vector2 CalcCenterPos(const myMath::Vector2& inLeftUpPos, const myMath::Vector2& inSize)
		{
			myMath::Vector2 centerPos;
			centerPos.x = inLeftUpPos.x + (inSize.x / 2.0f);
			centerPos.y = inLeftUpPos.y + (inSize.y / 2.0f);
			return centerPos;
		}

		myMath::Vector2 CalcLeftUpPos(const myMath::Vector2& inCenterPos, const myMath::Vector2& inSize)
		{
			myMath::Vector2 centerPos;
			centerPos.x = inCenterPos.x - (inSize.x / 2.0f);
			centerPos.y = inCenterPos.y - (inSize.y / 2.0f);
			return centerPos;
		}

	};
}