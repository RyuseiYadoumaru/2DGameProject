#include "PlayerFloatingEnterState.h"

#include "../Include/SystemInclude.h"

namespace Downwell
{
	PlayerFloatingEnterState::PlayerFloatingEnterState(Player* context, State<Player>* parent)
		: State<Player>(context, parent)
	{

	}

	void PlayerFloatingEnterState::OnEnter()
	{
	}

	void PlayerFloatingEnterState::OnUpdate()
	{
		Player& player = GetContext();
		bool isOnGround = player.GetBoxCollider().IsOnGround();

		if (isOnGround == false)
		{
			SendTrigger(PLAYER_FALL);
		}
		else if (GamePad::Press(Xinput::A))
		{
			SendTrigger(PLAYER_JUMP);
		}
		else if (player.IsStep() == true)
		{
			SendTrigger(PLAYER_STEP);
		}
	}

	void PlayerFloatingEnterState::OnExit()
	{


	}
}
