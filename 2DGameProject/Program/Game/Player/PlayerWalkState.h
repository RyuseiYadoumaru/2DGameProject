#pragma once
#include "Player.h"

namespace Downwell
{
	class PlayerWalkState : public State<Player>
	{
	public:
		PlayerWalkState(Player* context, State<Player>* parent);

	public:
		// State ����Čp������܂���
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;

	private:
		int _frame = 0;
	};
}