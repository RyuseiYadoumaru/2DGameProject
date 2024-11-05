#include "DxLib.h"
#include "Player.h"
#include "PlayerRootState.h"

#include "../Include/ObjectInclude.h"

#include "../Map/Map2DSponer.h"
#include "../Camera/ShakeCamera.h"

namespace Downwell
{
	void Player::Setup()
	{
		auto renderer = AddComponent<RectRenderer>();
		renderer->color.Set(0.0f, 0.0f, 255.0f, 255.0f);
		renderer->size.Set(19.0f, 25.0f);
		renderer->SetLayer(10);
		_renderer = renderer;

		auto collider = AddComponent<BoxCollider2D>();
		collider->SetOffset(0.0f, 0.0f);
		collider->SetSize(19.0f, 25.0f);
		_boxCollider = collider.get();

		auto gun = AddComponent<Gun>();

		auto life = AddComponent<Life>();
		_life = life;

		isDeath = false;
	}

	void Player::BeginPlay()
	{
		// ステートマシン
		_stateMahcine = make_shared<HFSM<Player>>(this);
		_stateMahcine->RegisterRootState<PlayerRootState>();
		_stateMahcine->OnEnable();

		// アクションイベント
		_actionEvent = make_shared<PlayerActionEvent>();

		// アクションパラメーター
		_actionParam.walkMaxSpeed = 8.0f;
		_actionParam.walkMinSpeed = 0.1f;

		_actionParam.jumpPower = 21.0f;
		_actionParam.risingFrame = 13;
		_actionParam.jumpFloatingFrame = 1;

		_actionParam.fallMaxSpeed = 17.0f;
		_actionParam.fallMaxSpeedFrame = 200;

		_actionParam.fireIntervalFrame = 8;

		_actionParam.startStepPower = 10.0f;
		_actionParam.stepFrame = 11;

		// 当たり判定をとるマップチップ追加
		auto mapSponer = GameObject::Find<Map2DSponer>("MapSponer");
		GetComponent<BoxCollider2D>()->RegisterMap(mapSponer->GetMap2DData(), mapSponer->GetBlockMap());
	}

	void Player::Tick()
	{
		_stateMahcine->OnUpdate();
	}

	void Player::EndPlay()
	{
		_stateMahcine->OnDisable();

		_stateMahcine	= nullptr;
		_actionEvent	= nullptr;

		_boxCollider	= nullptr;
		_renderer		= nullptr;
		_life			= nullptr;
	}

	void Player::OnStartStep()
	{
		isStep = true;
	}

	void Player::OnEndStep()
	{
		isStep = false;
	}
	void Player::OnDeath()
	{
		GamePad::StartVibration(900, 1000);
		auto camera = GameObject::Find("Camera");
		auto followCamera = (camera != nullptr) ? camera->GetComponent<ShakeCamera>() : nullptr;
		if (followCamera != nullptr)
		{
			followCamera->StartShakeCamera(20.0f, 1.0f, 20, 1);
		}
		isDeath = true;
	}
	void Player::OnDamage()
	{
		GamePad::StartVibration(500, 200);
		auto camera = GameObject::Find("Camera");
		auto followCamera = (camera != nullptr) ? camera->GetComponent<ShakeCamera>() : nullptr;
		if (followCamera != nullptr)
		{
			followCamera->StartShakeCamera(10.0f, 0.0f, 10, 1);
		}
	}
}