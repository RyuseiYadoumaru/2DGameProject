#pragma once
#include "Player.h"

namespace Downwell
{
	class PlayerFloatingEnterState : public State<Player>
	{
	public:
		PlayerFloatingEnterState(Player* context, State<Player>* parent);

	public:
		// State を介して継承されました
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;

	};
}