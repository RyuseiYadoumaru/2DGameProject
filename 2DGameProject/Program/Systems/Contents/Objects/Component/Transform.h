#pragma once
#include "../../../../Systems/BaseClasses/Component.h"
#include "../../Maths/Vector2.h"

namespace myGame::Object
{
	class Transform : public mySystem::IComponent
	{
	public:
		COMPONENT_CLASS

	public:
		myMath::Vector2 position;
		myMath::Vector2 scale;

		myMath::Vector2 moveForce;

	public:
		const myMath::Vector2& GetMoveVector() const noexcept { return _moveVector; }

	private:
		myMath::Vector2 _prePosition;
		myMath::Vector2 _moveVector;

	public:
		virtual void Initialize() override;
		virtual void Finalize() override;

		virtual void Start() override final;
		virtual void Update() override final;
		virtual void SecondUpdate() override final;
		virtual void LateUpdate() override final;
		virtual void End() override final;

	};
}