#pragma once
#include "../Include/SystemInclude.h"
#include "../Include/ObjectInclude.h"
#include "Enemy.h"

namespace Downwell
{
	struct HitEnemyInfo
	{
		Enemy* hitEnemy = nullptr;
	};

	class EnemyManager final
	{
	public:
		static void Register(Enemy* enemy);
		static void Remove(Enemy* enemy);

		static void AllEnemyClear();

		static vector<HitEnemyInfo> HitCheckEnemy(BoxCollider2D& inBoxColiider);

	private:
		static map<unsigned int, Enemy*> _instanceEnemyList;

#pragma region  Constructor
	public:
		EnemyManager() = delete;
		~EnemyManager() = delete;
#pragma endregion

	};
}