#include "DxLib.h"
#include "CrawlEnemy.h"

#include "../Map/Map2DSponer.h"

#include "CrawlEnemyRootState.h"

namespace Downwell
{
	void CrawlEnemy::ReverseMoveVector()
	{
		_moveVec.x *= -1.0f;
		_moveVec.y *= -1.0f;

		_moveVec = Vector2::Normalize(_moveVec);
	}

	void CrawlEnemy::OnUpdateCrawlGround()
	{
		bool isHitWall		= CheckHitWall(_moveVec);
		bool isStandCliff	= CheckStandCliff(_downward, _moveVec);
		if (isHitWall == true)
		{
			OnHitWall();
		}
		else if (isStandCliff == true)
		{
			OnStandCliff();
		}
	}

	void CrawlEnemy::OnHitWall()
	{
		Vector2 temp(_moveVec);
		_moveVec = Vector2::Inverse(_downward);
		_downward = temp;
	}

	void CrawlEnemy::OnStandCliff()
	{
		// 浮いた分戻す
		_transform->position.x += GetMoveSpeed() * Vector2::Inverse(_moveVec).x;
		_transform->position.y += GetMoveSpeed() * Vector2::Inverse(_moveVec).y;

		if (CheckStandCliff(_downward, _moveVec) == true)
		{
			// 戻した先になにもないときにブロックない状態
			// ブロックがないときは次のブロックが見つかるまで落下する
			_downward.Set(0.0f, 1.0f);
			isFall = true;
		}
		else
		{
			Vector2 temp(_moveVec);
			_moveVec = _downward;
			_downward = Vector2::Inverse(temp);
			isFall = false;
		}

	}

	bool CrawlEnemy::CheckStandCliff(const Vector2& inDownward, const Vector2& inMoveVector)
	{
		Vector2 colliderPos	 = _boxCollider->GetPos();
		Vector2 colliderSize = _boxCollider->GetSize();

		// チェックポイントはコライダのオフセットから下ベクトルに配置しています
		Vector2 checkPoint;
		checkPoint.x = colliderPos.x + ((colliderSize.x * 0.5f) * inDownward.x);
		checkPoint.y = colliderPos.y + ((colliderSize.y * 0.5f) * inDownward.y);

		// 前と後ろの角にチェックポイントを置く
		Vector2 checkPointFront;
		checkPointFront.x = checkPoint.x + (colliderSize.x * 0.5f) * inMoveVector.x;
		checkPointFront.y = checkPoint.y + (colliderSize.y * 0.5f) * inMoveVector.y;

		Vector2 checkPointBack;
		checkPointBack.x = checkPoint.x + (colliderSize.x * 0.5f) * Vector2::Inverse(inMoveVector).x;
		checkPointBack.y = checkPoint.y + (colliderSize.y * 0.5f) * Vector2::Inverse(inMoveVector).y;

		MapChip hitChipFront = Map2DUtility::GetMapChipFromPosition(*_mapData, checkPointFront.x, checkPointFront.y);
		MapChip hitChipBack  = Map2DUtility::GetMapChipFromPosition(*_mapData, checkPointBack.x, checkPointBack.y);

		bool isHitFront = hitChipFront == MapChip::NB || hitChipFront == MapChip::BB;
		bool isHitBack  = hitChipBack  == MapChip::NB || hitChipBack == MapChip::BB;

		if (isHitFront == true || isHitBack == true)
		{
			// 地面についている判定
			return false;
		}
		return true;
	}

	bool CrawlEnemy::CheckHitWall(const Vector2& inMoveVector)
	{
		Vector2 colliderPos = _boxCollider->GetPos();
		Vector2 colliderSize = _boxCollider->GetSize();

		// チェックポイントはコライダのオフセットから下ベクトルに配置しています
		Vector2 checkPoint;
		checkPoint.x = colliderPos.x + ((colliderSize.x * 0.5f) * inMoveVector.x);
		checkPoint.y = colliderPos.y + ((colliderSize.y * 0.5f) * inMoveVector.y);

		MapChip hitChip = Map2DUtility::GetMapChipFromPosition(*_mapData, checkPoint.x, checkPoint.y);

		if (hitChip == MapChip::BB || hitChip == MapChip::NB)
		{
			return true;
		}
		return false;
	}

#pragma region  System Callback Functions

	void CrawlEnemy::Setup()
	{
		auto renderer = AddComponent<RectRenderer>();
		renderer->size.Set(25.0f, 25.0f);
		renderer->color.Set(50.f, 0.0f, 128.0f, 255.0f);

		auto collider = AddComponent<BoxCollider2D>();
		collider->SetSize(25.0f, 25.0f);
		_boxCollider = collider;

		// 移動ベクトルと下向きベクトルの初期化
		_moveVec = Vector2::Left;
		_downward = Vector2::Down;

		// マップチップで生成しているため
		// 地面につく座標に配置しなおしている
		_transform->position.y += _boxCollider->GetSize().y * 0.5f;

		// アクションパラメータ設定
		_actionParam.movementSpeed = 2.0f;
	}

	void CrawlEnemy::BeginPlay()
	{
		// NOTE:当たり判定を取るマップチップ
		//		押し戻しは[CrawlEnemy]独自のもので行っているため、[BoxCollider]の押し戻しは使用していません
		//		これはブロックに沿って動くオブジェクトのため地面の方向が動的に変わるためである
		//		使用するときは→ [ _boxCollider->RegisterMap(mapSponer->GetMap2DData(), mapSponer->GetBlockMap()); ]
		auto mapSponer = GameObject::Find<Map2DSponer>("MapSponer");
		_mapData = mapSponer->GetMap2DData();

		// ステートマシン初期化
		_stateMahcine = make_shared<HFSM<CrawlEnemy>>(this);
		_stateMahcine->RegisterRootState<CrawlEnemyRootState>();
		_stateMahcine->OnEnable();
	}

	void CrawlEnemy::Tick()
	{
		OnUpdateCrawlGround();
		_stateMahcine->OnUpdate();
	}

	void CrawlEnemy::EndPlay()
	{
		_mapData = nullptr;
		_stateMahcine->OnDisable();
	}

#pragma endregion
}