#pragma once
#include "EnemyDefinition.h"

#include "../Include/ObjectInclude.h"
#include "../Include/AIInclude.h"
#include "../Include/MathInclude.h"
#include "../Common/GameDefinition.h"

#define  ENEMY_CLASS  Downwell::Enemy::Enemy;

namespace Downwell
{
	class Enemy : public Character 
	{
	public:
		CHARACTER_CLASS;

	public:
		shared_ptr<BoxCollider2D> GetBoxCollider2D() const noexcept { return _boxCollider; }
		float GetMoveSpeed() const noexcept { return _actionParam.movementSpeed; }

	protected:
		shared_ptr<BoxCollider2D>  _boxCollider = nullptr;
		EnemyCommonActionData _actionParam;

	};
}