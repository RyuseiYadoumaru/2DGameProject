#include "MainGameScene.h"

#include "../Player/Player.h"
#include "../Map/Map2DSponer.h"
#include "../Gun/GunUI.h"
#include "../Life/LifeUI.h"
#include "../UI/GameOverUI.h"
#include "../Map/MapLevelChecker.h"
#include "../Animation/Slide.h"

#include "../Camera/FollowCamera.h"
#include "../Camera/ShakeCamera.h"

namespace Downwell
{
	void MainGameScene::SetupObject()
	{
		auto camera = GameObjectManager::SceneEntry<GameObject>("Camera");
		camera->AddComponent<Camera>();
		auto followCamera = camera->AddComponent<FollowCamera>();
		auto shakeCamera = camera->AddComponent<ShakeCamera>();

		auto gunUIManager = GameObjectManager::SceneEntry<GameObject>("GunUIManager");
		gunUIManager->AddComponent<GunUIManager>();

		auto lifeUIManager = GameObjectManager::SceneEntry<GameObject>("LifeUIManager");
		lifeUIManager->AddComponent<LifeUIManager>();

		auto gameOverUI = GameObjectManager::SceneEntry<GameOverUI>("GameOverUI");

		_player = GameObjectManager::SceneEntry<Player>("Player", Tag::Player);

		// �}�b�v
		auto mapSponer = GameObjectManager::SceneEntry<Map2DSponer>("MapSponer");

		// �}�b�v���x��UI
		auto levelUI = GameObjectManager::SceneEntry<GameObject>("MapLevelChecker");
		levelUI->GetTrans().position.Set(300.0f, 220.0f);
		auto checker = levelUI->AddComponent<MapLevelChecker>();
		checker->RegisterCheckPos(&_player->GetTrans().position);
		auto levelUIText = levelUI->AddComponent<TextRenderer>();
		levelUIText->SetFontSize(50);
		levelUIText->color.Set(230.0f, 230.0f, 230.0f, 255.0f);
		levelUIText->SetText("0");

		// �g�����W�V����
		_startTransition = GameObjectManager::SceneEntry<GameObject>("StartTransition");
		auto startWidget = _startTransition->AddComponent<WidgetRenderer>();
		startWidget->color.Set(10.0f, 10.0f, 10.0f, 255.0f);
		startWidget->SetLayer(30);
		startWidget->size.Set(1280.0f, 720.0f);

		auto startAnim = _startTransition->AddComponent<Slide>();
		startAnim->SetStartPos(0.0f, 0.0f);
		startAnim->SetTargetPos(0.0f, 720.0f);
		startAnim->SetPlayFrame(_fadeFrame);

		_endTransition = GameObjectManager::SceneEntry<GameObject>("EndTransition");
		auto endWidget = _endTransition->AddComponent<WidgetRenderer>();
		endWidget->color.Set(10.0f, 10.0f, 10.0f, 255.0f);
		endWidget->SetLayer(30);
		endWidget->size.Set(1280.0f, 720.0f);

		auto endAnim = _endTransition->AddComponent<Slide>();
		endAnim->SetStartPos(0.0f, 720.0f);
		endAnim->SetTargetPos(0.0f, 0.0f);
		endAnim->SetPlayFrame(_fadeFrame);

		// �J�����ݒ�
		followCamera->SetFollowTransform(&_player->GetTrans());
		followCamera->SetFollowOffset(0.0f, 0.0f);
		followCamera->OnEnableRangeY(420.0f, 21900.0f);
		followCamera->OnEnableDelay();
		followCamera->SetFollowingDistance(10.0f);
	}


	void MainGameScene::BeginPlay()
	{
		printf("���C���Q�[���V�[���J�n\n");
		float playerWidth = _player->GetComponent<RectRenderer>()->size.x;
		_player->GetTrans().position.Set(225.0f, -600.0f);

		GamePad::SetActive(false);

		_startAnimFrame = 0;
		isPlayTransition = false;

		_endAnimFrame = 0;
		isPlayEndTransition = false;

		_loadSceneFrame = 0;
	}

	void MainGameScene::Tick()
	{
		if (isPlayTransition == false)
		{
			// �J�n�g�����W�V����
			if (_startAnimFrame >= _fadeWaitFrame)
			{
				_startTransition->GetComponent<Slide>()->OnPlay();
				isPlayTransition = true;
			}
			_startAnimFrame++;
		}

		if (_player->GetTrans().position.y >= 1500.0f)
		{
			// �J�n���o���I���������͂�������
			GamePad::SetActive(true);
		}

		

		if (_player->GetTrans().position.y >= 22000.0f &&
			_player->IsDeath() == false)
		{
			// �J�n���o���I���������͂�������
			GamePad::SetActive(false);

			// �S�[������ɂȂ�����
			if (isPlayEndTransition == false)
			{
				// �I���g�����W�V�����J�n
				if (_endAnimFrame >= _fadeWaitFrame)
				{
					_endTransition->GetComponent<Slide>()->OnPlay();
					isPlayEndTransition = true;
				}
				_endAnimFrame++;
			}
			else
			{
				// �g�����W�V�������Đ���ҋ@�t���[��
				if (_loadSceneFrame >= _waitLoadSceneFrame)
				{
					SceneManager::LoadScene("GameClearScene");
				}
				_loadSceneFrame++;
			}
		}

	}


	void MainGameScene::EndPlay()
	{
		printf("���C���Q�[���V�[���I��\n");
	}

}