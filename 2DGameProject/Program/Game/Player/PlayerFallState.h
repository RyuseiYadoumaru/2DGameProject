#pragma once
#include "Player.h"

namespace Downwell
{
	class PlayerFallState : public State<Player>
	{
	public:
		PlayerFallState(Player* context, State<Player>* parent);

	public:
		// State ����Čp������܂���
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;

	private:
		int _frame = 0;
	};
}