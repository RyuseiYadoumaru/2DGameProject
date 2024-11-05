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
		printf("死亡演出開始\n");
		_frameCounter = 0;

		_gameOverUI = GameObject::Find<GameOverUI>("GameOverUI");
		
		_shakeCounter = 0;

		// ブロックを貫通して落下する演出を入れるため当たり判定を切る
		GetContext().GetBoxCollider().SetActive(false);

		// 死亡位置保存
		_savePlayerDeathPosX = GetContext().GetTrans().position.x;
		_savePlayerDeathPosY = GetContext().GetTrans().position.y;

		// カメラの追従を外す
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
			// 震える演出
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
			// 落下演出
			player.GetActionEvent().Fall(&playerTrans,
										 player.GetFallMaxSpeed(),
										 player.GetFallMaxSpeedFrame(),
										_frameCounter);
		}

		if (_frameCounter >= _showUIWaitFrame)
		{
			// UI演出
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
		printf("死亡演出終了\n");
	}
}