#pragma once
#include "Player.h"

namespace Downwell
{
	class PlayerFloatingState : public State<Player>
	{
	public:
		PlayerFloatingState(Player* context, State<Player>* parent);

	public:
		// State を介して継承されました
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;

	private:
		float _timer = 0.0f;
	};
}