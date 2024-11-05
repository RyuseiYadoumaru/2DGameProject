#include "TitleScene.h"

#include "../../Systems/SceneManager/SceneManager.h"
#include "../../Systems/RenderingManager/RenderingManager.h"

#include "../Include/SystemInclude.h"
#include "../Include/MathInclude.h"

#include "../Player/Player.h"
#include "../Map/Map2DTitleSponer.h"
#include "../Camera/FollowCamera.h"
#include "../UI/WaveAnimation.h"


namespace Downwell
{
	void TitleScene::SetupObject()
	{
		auto camera = GameObjectManager::SceneEntry<GameObject>("Camera");
		camera->AddComponent<Camera>();
		auto followCamera = camera->AddComponent<FollowCamera>();

		auto gunUIManager = GameObjectManager::SceneEntry<GameObject>("GunUIManager");
		gunUIManager->AddComponent<GunUIManager>();

		auto player = GameObjectManager::SceneEntry<Player>("Player", Tag::Player);
		_player = player;
		
		GameObjectManager::SceneEntry<Map2DTitleSponer>("MapSponer");

		// タイトルロゴ
		auto titleLogo = GameObjectManager::SceneEntry<GameObject>("TitleLogo");
		auto logoRenderer = titleLogo->AddComponent<SpriteRenderer>();
		logoRenderer->SetSprite("TitleLogo.png");
		logoRenderer->size.Set(960.0f * 0.3f, 540.0f * 0.3f);
		titleLogo->GetTrans().position.Set(223.0f, 650.0f);

		// 誘導UI
		auto triangle = GameObjectManager::SceneEntry<GameObject>("Triangle");
		auto triangleRenderer = triangle->AddComponent<TextMeshRenderer>();
		triangleRenderer->SetText("▼");
		triangleRenderer->SetFontSize(35);
		triangle->GetTrans().position.Set(207.0f, 890.0f);

		auto waveAnim = triangle->AddComponent<WaveAnimation>();
		waveAnim->SetWaveRange(0.0f, 25.0f);
		waveAnim->SetWaveCycleFrame(100);

		// カメラ設定
		followCamera->SetFollowTransform(&player->GetTrans());
		followCamera->SetFollowOffset(0.0f, 0.0f);
		followCamera->OnEnableRangeY(200.0f, 670.0f);
		followCamera->OnDisableDelay();
	}


	void TitleScene::BeginPlay()
	{
		printf("タイトルシーン開始\n");
		_player->GetTrans().position.Set(100.0f, 857.0f);
	}

	int a = 0;
	void TitleScene::Tick()
	{
		float playerPosY = _player->GetTrans().position.y;
		if(playerPosY >= 1800.0f)
		{
			SceneManager::LoadScene("MainGameScene");
		}
	}


	void TitleScene::EndPlay()
	{
		printf("タイトルシーン終了\n");
		_player = nullptr;
	}

}