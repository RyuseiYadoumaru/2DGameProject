#pragma once
#include "Player.h"

namespace Downwell
{
	class PlayerIdleState : public State<Player>
	{
	public:
		PlayerIdleState(Player* context, State<Player>* parent);

	public:
		// State ����Čp������܂���
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;
	};
}