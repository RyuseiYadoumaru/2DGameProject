#pragma once
#include "Player.h"

namespace Downwell
{
	class PlayerJumpState : public State<Player>
	{
	public:
		PlayerJumpState(Player* context, State<Player>* parent);

	public:
		// State ����Čp������܂���
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;

	private:
		int _jumpFrameCounter = 0;
		float _currentRisePower = 0.0f;

		bool isFloating = false;
		int _floatingFrameCounter = 0;
	};
}