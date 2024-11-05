#include "PlayerDeathState.h"

#include "PlayerGroundedState.h"
#include "PlayerFloatingState.h"

#include "../Enemy/EnemyManager.h"
#include "../UI/GameOverUI.h"

#include "../Camera/FollowCamera.h"

#include "../Include/ObjectInclude.h"
#include "../Include/SystemInclude.h"
#include "../Include/MathInclude.h"


namespace Downwell
{
	PlayerDeathState::PlayerDeathState(Player* context, State<Player>* parent)
		: State<Player>(context, parent)
	{

	}

	void PlayerDeathState::OnEnter()
	{
		printf("���S���o�J�n\n");
		_frameCounter = 0;

		_gameOverUI = GameObject::Find<GameOverUI>("GameOverUI");
		
		_shakeCounter = 0;

		// �u���b�N���ђʂ��ė������鉉�o�����邽�ߓ����蔻���؂�
		GetContext().GetBoxCollider().SetActive(false);

		// ���S�ʒu�ۑ�
		_savePlayerDeathPosX = GetContext().GetTrans().position.x;
		_savePlayerDeathPosY = GetContext().GetTrans().position.y;

		// �J�����̒Ǐ]���O��
		auto camera = GameObject::Find("Camera");
		if (camera != nullptr) camera->GetComponent<FollowCamera>()->ResetFollowTransform();
	}

	void PlayerDeathState::OnUpdate()
	{
		auto& player = GetContext();
		auto& playerTrans = GetContext().GetTrans();

		playerTrans.moveForce.Set(0.0f, 0.0f);

		if (_shakeCounter < _shakeCount)
		{
			// �k���鉉�o
			if (_frameCounter > _shakeIntervalFrame)
			{
				playerTrans.position.x = _savePlayerDeathPosX + _deathPlayerShakeRange;
				playerTrans.position.y = _savePlayerDeathPosY;
				_deathPlayerShakeRange *= -1.0f;
				_frameCounter = 0;
				_shakeCounter++;
			}

		}

		if (_frameCounter >= _playerFallWaitFrame)
		{
			// �������o
			player.GetActionEvent().Fall(&playerTrans,
										 player.GetFallMaxSpeed(),
										 player.GetFallMaxSpeedFrame(),
										_frameCounter);
		}

		if (_frameCounter >= _showUIWaitFrame)
		{
			// UI���o
			if (_gameOverUI == nullptr) return;

			_gameOverUI->OnPlay();
			if (GamePad::Press(Xinput::B))
			{
				SceneManager::LoadScene("TitleScene");
				return;
			}
		}

		_frameCounter++;
		cout << player.GetTrans().moveForce.x << "," << player.GetTrans().moveForce.y << "\n";
	}

	void PlayerDeathState::OnExit()
	{
		_gameOverUI = nullptr;
		printf("���S���o�I��\n");
	}
}