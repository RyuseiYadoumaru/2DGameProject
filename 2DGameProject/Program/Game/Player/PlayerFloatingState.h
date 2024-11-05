#pragma once
#include "Player.h"

namespace Downwell
{
	class PlayerFloatingState : public State<Player>
	{
	public:
		PlayerFloatingState(Player* context, State<Player>* parent);

	public:
		// State ����Čp������܂���
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;

	private:
		float _timer = 0.0f;
	};
}