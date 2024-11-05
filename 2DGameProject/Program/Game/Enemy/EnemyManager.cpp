#include "EnemyManager.h"

namespace Downwell
{
	map<unsigned int, Enemy*> EnemyManager::_instanceEnemyList;

	void EnemyManager::Register(Enemy* enemy)
	{
		unsigned int enemyID = enemy->GetID();
		if (_instanceEnemyList.contains(enemyID) == true) return;
		_instanceEnemyList[enemyID] = enemy;
	}
	void EnemyManager::Remove(Enemy* enemy)
	{
		unsigned int enemyID = enemy->GetID();
		if (_instanceEnemyList.contains(enemyID) == false) return;
		GameObject::Destoy(_instanceEnemyList[enemyID]);
		_instanceEnemyList[enemyID] = nullptr;
		_instanceEnemyList.erase(enemyID);
	}
	void EnemyManager::AllEnemyClear()
	{
		for (auto& enemy : _instanceEnemyList)
		{
			enemy.second = nullptr;
		}

		_instanceEnemyList.clear();
	}

	vector<HitEnemyInfo> EnemyManager::HitCheckEnemy(BoxCollider2D& inBoxColiider)
	{
		// 当たり判定
		vector<HitEnemyInfo> hitInfoList;
		for (auto& enemy : _instanceEnemyList)
		{
			auto enemyCollider = enemy.second->GetBoxCollider2D();

			// オブジェクト間の距離を求める
			Vector2 distance;
			Vector2 pos = inBoxColiider.GetPos();
			Vector2 enemyPos = enemyCollider->GetPos();
			distance.x = fabs(pos.x - enemyPos.x);
			distance.y = fabs(pos.y - enemyPos.y);

			// オブジェクトが衝突する距離を求める
			Vector2 halfSize;
			halfSize.Set(inBoxColiider.GetSize().x / 2.0f, inBoxColiider.GetSize().y / 2.0f);
			Vector2 enemyHalfSize;
			enemyHalfSize.Set(enemyCollider->GetSize().x / 2.0f, enemyCollider->GetSize().y / 2.0f);
			Vector2 hitDistance;
			hitDistance.x = halfSize.x + enemyHalfSize.x;
			hitDistance.y = halfSize.y + enemyHalfSize.y;

			if (distance.x < hitDistance.x && distance.y < hitDistance.y)
			{
				HitEnemyInfo info;
				info.hitEnemy = enemy.second;
				hitInfoList.push_back(info);
			}
		}




		return hitInfoList;
	}
}