#pragma once
#include "Player.h"

namespace Downwell
{
	class PlayerGroundedState : public State<Player>
	{
	public:
		PlayerGroundedState(Player* context, State<Player>* parent);

	public:
		// State ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;

	private:
		shared_ptr<Gun> _gun;
	};
}