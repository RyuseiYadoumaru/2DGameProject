#pragma once
#include "Player.h"

namespace Downwell
{
	class PlayerActionState : public State<Player>
	{
	public:
		PlayerActionState(Player* context, State<Player>* parent);

	public:
		// State ����Čp������܂���
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;

	private:
		float _fallTimer = 0.0f;

	};
}