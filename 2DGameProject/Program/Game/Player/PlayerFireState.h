#pragma once
#include "Player.h"

namespace Downwell
{
	class PlayerFireState : public State<Player>
	{
	public:
		PlayerFireState(Player* context, State<Player>* parent);

	public:
		// State ����Čp������܂���
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;

	private:
		shared_ptr<Gun> _gun;
		int _frame = 0;
		int _fireFrame = 0;
	};
}