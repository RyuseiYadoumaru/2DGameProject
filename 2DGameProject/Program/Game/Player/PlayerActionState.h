#pragma once
#include "Player.h"

namespace Downwell
{
	class PlayerActionState : public State<Player>
	{
	public:
		PlayerActionState(Player* context, State<Player>* parent);

	public:
		// State ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;

	private:
		float _fallTimer = 0.0f;

	};
}