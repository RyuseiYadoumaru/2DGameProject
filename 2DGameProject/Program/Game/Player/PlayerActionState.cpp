#include "PlayerActionState.h"

#include "PlayerGroundedState.h"
#include "PlayerFloatingState.h"

#include "../Enemy/EnemyManager.h"

#include "../Include/SystemInclude.h"
#include "../Include/MathInclude.h"


namespace Downwell
{
	PlayerActionState::PlayerActionState(Player* context, State<Player>* parent)
		: State<Player>(context, parent)
	{
		AddChildState<PlayerGroundedState>();
		AddChildState<PlayerFloatingState>();

		// �n�ʏ�ԑJ�ڏ���
		AddChildTransition<PlayerGroundedState, PlayerFloatingState>(PLAYER_FLOATING);

		// ���V��ԑJ�ڏ���
		AddChildTransition<PlayerFloatingState, PlayerGroundedState>(PLAYER_GROUND);

		RegisterStartState<PlayerFloatingState>();
	}

	void PlayerActionState::OnEnter()
	{
		printf("�A�N�V�����J�n\n");

		_fallTimer = 0.0f;
	}

	void PlayerActionState::OnUpdate()
	{
		Player& player = GetContext();

		auto collider = player.GetBoxCollider();
		vector<HitEnemyInfo> hitEnemyList = EnemyManager::HitCheckEnemy(collider);
		for (auto& info : hitEnemyList)
		{
			auto hitEnemy = info.hitEnemy;

			bool isHitButtom = (player.GetTrans().position.y < hitEnemy->GetTrans().position.y);
			bool isHitTagFloatingEnemy = (hitEnemy->GetTag() == Tag::FloatingEnemy);
			bool canStep = (player.IsStep() == false);
			if ( isHitButtom == true &&
				 isHitTagFloatingEnemy == true &&
				 canStep == true)
			{
				// �����������ĕ��V�G�������瓥�݂���
				player.OnStartStep();
			}
			else
			{
				// ����ȊO�̃q�b�g����Ȃ�_���[�W���󂯂�
				player.GetLife().OnDamage();
				int currentLifePoint = player.GetLife().GetLifePoint();
				if (currentLifePoint == 0)
				{
					// ���S����
					player.OnDeath();
					SendTrigger(PLAYER_DEATH);
				}
				else
				{
					// ���S���Ă��Ȃ��Ƃ��̏���
					player.OnDamage();
				}
			}

			EnemyManager::Remove(hitEnemy);
		}
	}

	void PlayerActionState::OnExit()
	{
		printf("�A�N�V�����I��\n");
	}

}