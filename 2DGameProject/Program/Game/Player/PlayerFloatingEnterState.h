#pragma once
#include "Player.h"

namespace Downwell
{
	class PlayerFloatingEnterState : public State<Player>
	{
	public:
		PlayerFloatingEnterState(Player* context, State<Player>* parent);

	public:
		// State ����Čp������܂���
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;

	};
}