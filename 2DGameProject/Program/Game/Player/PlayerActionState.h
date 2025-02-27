#pragma once
#include "Player.h"

namespace Downwell
{
	class PlayerActionState : public State<Player>
	{
	public:
		PlayerActionState(Player* context, State<Player>* parent);

	public:
		// State を介して継承されました
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;

	private:
		float _fallTimer = 0.0f;

	};
}