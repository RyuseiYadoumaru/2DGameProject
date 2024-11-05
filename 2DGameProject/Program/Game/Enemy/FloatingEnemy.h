#pragma once
#include "Enemy.h"

namespace Downwell
{
	enum
	{
		FLOATINGENEMY_PATROL,
		FLOATING_PATROL_IDLE,
		FLOATING_PATROL_MOVEMENT,

		FLOATINGENEMY_DISCOVERY
	};

	class FloatingEnemy : public Enemy
	{
	public:
		ENEMY_CLASS

	private:
		shared_ptr<HFSM<FloatingEnemy>> _stateMahcine = nullptr;

	public:
		float GetMoveSpeed() const noexcept { return _moveSpeed; }

	private:
		float _moveSpeed = 2.0f;

	private:
		void Setup() override;
		void BeginPlay() override;
		void Tick() override;
		void EndPlay() override;

	};
};