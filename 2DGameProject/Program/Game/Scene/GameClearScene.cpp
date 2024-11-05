#include "GameClearScene.h"

#include "../../Systems/SceneManager/SceneManager.h"
#include "../../Systems/RenderingManager/RenderingManager.h"

#include "../Include/SystemInclude.h"
#include "../Include/MathInclude.h"

#include "../Player/Player.h"
#include "../Map/Map2DResultSponer.h"
#include "../Camera/FollowCamera.h"


namespace Downwell
{
	void GameClearScene::SetupObject()
	{
		// カメラ
		auto camera = GameObjectManager::SceneEntry<GameObject>("Camera");
		camera->AddComponent<Camera>();
		auto followCamera = camera->AddComponent<FollowCamera>();

		// プレイヤー
		auto player = GameObjectManager::SceneEntry<Player>("Player", Tag::Player);
		_player = player;

		GameObjectManager::SceneEntry<Map2DResultSponer>("MapSponer");

		// クリアロゴ
		auto clearLogo = GameObjectManager::SceneEntry<GameObject>("GameClearLogo");
		auto logoRenderer = clearLogo->AddComponent<TextMeshRenderer>();
		logoRenderer->SetText("Stage Clear !!!");
		logoRenderer->color.Set(255.0f, 0.0f, 0.0f, 255.0f);
		logoRenderer->SetFontSize(24.0f);
		logoRenderer->SetFontThick(15.0f);
		clearLogo->GetTrans().position.Set(130.0f, 1920.0f);

		// カメラ設定
		followCamera->SetFollowTransform(&player->GetTrans());
		followCamera->SetFollowOffset(0.0f, 0.0f);
		followCamera->OnEnableRangeY(420.0f, 2000.0f);
		followCamera->OnDisableDelay();
	}


	void GameClearScene::BeginPlay()
	{
		printf("ゴールシーン開始\n");
		GamePad::SetActive(false);
		_player->GetTrans().position.Set(225.0f, 10.0f);
		canTransitionTitle = false;
		_frameCounter = 0;
	}


	void GameClearScene::Tick()
	{

		// ロゴが出た後にボタンをプレスしたときに次の遷移を行う
		if (canTransitionTitle == true)
		{
			if (_frameCounter >= _waitTransitionFrame)
			{
				SceneManager::LoadScene("TitleScene");
			}
			_frameCounter++;
			return;
		}

		if (_player->GetTrans().position.y >= 2200.0)
		{
			canTransitionTitle = true;
		}
	}


	void GameClearScene::EndPlay()
	{
		printf("ゴールシーン終了\n");
		_player = nullptr;
		GamePad::SetActive(true);
	}
}