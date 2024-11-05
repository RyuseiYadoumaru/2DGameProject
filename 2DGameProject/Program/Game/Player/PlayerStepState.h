#pragma once
#include "Player.h"

namespace Downwell
{
	class PlayerStepState : public State<Player>
	{
	public:
		PlayerStepState(Player* context, State<Player>* parent);

	public:
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;

	private:
		int _frame = 0;
		float _currenStepPower = 0.0f;

	};
}