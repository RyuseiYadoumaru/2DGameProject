#pragma once
#include "Player.h"

namespace Downwell
{
	class PlayerGroundedState : public State<Player>
	{
	public:
		PlayerGroundedState(Player* context, State<Player>* parent);

	public:
		// State を介して継承されました
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;

	private:
		shared_ptr<Gun> _gun;
	};
}