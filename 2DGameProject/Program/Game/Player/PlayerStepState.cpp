#include "PlayerStepState.h"

namespace Downwell
{
	PlayerStepState::PlayerStepState(Player* context, State<Player>* parent)
		: State<Player>(context, parent)
	{

	}

	void PlayerStepState::OnEnter()
	{
		 GetContext().GetComponent<Gun>()->Reload();

		_currenStepPower = GetContext().GetStartStepPower();
		_frame = 0;
	}

	void PlayerStepState::OnUpdate()
	{
		Player& player = GetContext();

		bool triggerFireButtom = (GamePad::Trigger(Xinput::A) == true);
		if (triggerFireButtom == true)
		{
			SendTrigger(PLAYER_FIRE);
			return;
		}

		Transform& trans = player.GetTrans();
		
		// 踏みつけノックバック
		player.GetActionEvent().Step(&trans, &_currenStepPower, player.GetStartStepPower(), player.GetStepFrame(), _frame);

		// 移動
		float stickX = GamePad::LStick().x;
		player.GetActionEvent().Movement(&trans, player.GetWalkMaxSpeed(), stickX, _frame);

		if(_currenStepPower <= 0.0f)
		{
			SendTrigger(PLAYER_FALL);
			return;
		}

		_frame++;
	}

	void PlayerStepState::OnExit()
	{
		GetContext().OnEndStep();
	}

};

