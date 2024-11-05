#include "FloatingEnemy.h"
#include "FloatingEnemyRootState.h"

#include "../Map/Map2DSponer.h"


namespace Downwell
{
	void FloatingEnemy::Setup()
	{
		auto renderer = AddComponent<SpriteRenderer>();
		renderer->size.Set(40.0f, 40.0f);
		renderer->SetSprite("Enemy01.png");

		auto collider = AddComponent<BoxCollider2D>();
		collider->SetSize(30.0f, 30.0f);
		_boxCollider = collider;
	}

	void FloatingEnemy::BeginPlay()
	{
		// 当たり判定を取るマップチップ
		auto mapSponer = GameObject::Find<Map2DSponer>("MapSponer");
		_boxCollider->RegisterMap(mapSponer->GetMap2DData(), mapSponer->GetBlockMap());


		// ステートマシン初期化
		_stateMahcine = make_shared<HFSM<FloatingEnemy>>(this);
		_stateMahcine->RegisterRootState<FloatingEnemyRootState>();
		_stateMahcine->OnEnable();

	}

	void FloatingEnemy::Tick()
	{
		_stateMahcine->OnUpdate();
	}

	void FloatingEnemy::EndPlay()
	{
		_stateMahcine->OnDisable();
	}
}
