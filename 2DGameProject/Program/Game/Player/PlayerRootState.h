#pragma once
#include "Player.h"

namespace Downwell 
{
	class PlayerRootState : public State<Player>
	{
	public:
		PlayerRootState(Player* context, State<Player>* parent);

	public:
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;
	};
}