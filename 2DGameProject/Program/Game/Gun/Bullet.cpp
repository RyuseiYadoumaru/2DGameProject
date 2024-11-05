#include "Bullet.h"

#include "../Map/Map2DSponer.h"

#include "../Block/BreakBlock.h"
#include "../Enemy/EnemyManager.h"

namespace Downwell
{
#pragma region System Callback Methots

	void Bullet::Setup()
	{
		auto renderer = AddComponent<RectRenderer>();
		renderer->color.Set(200.0f, 0.0f, 0.0f, 255.0f);
		renderer->size.Set(13.0f, 15.0f);

		auto collider = AddComponent<BoxCollider2D>();
		collider->SetSize(13.0f, 15.0f);

		_boxCollider = collider.get();

	}

	void Bullet::BeginPlay()
	{
		_countFrame = 0;

		// �����蔻����Ƃ�}�b�v�`�b�v�ǉ�
		auto mapSponer = GameObject::Find<Map2DSponer>("MapSponer");
		_boxCollider->RegisterMap(mapSponer->GetMap2DData(), mapSponer->GetBlockMap());

		// ������
		_transform->position.x += _recoilValue;

		_destroyFrameCounter = 0;
	}

	void Bullet::Tick()
	{
		bool isEndLifeFrame = (_countFrame >= _lifeFrame);
		if (isEndLifeFrame == true)
		{
			// ���t���[���҂��ď�����
			if (_destroyFrameCounter >= _waitDestroyFrame)
			{
				GameObject::Destoy(this);
			}
			_transform->moveForce.Set(0.0f, 0.0f);
			_destroyFrameCounter++;
			return;
		}

		// ���X�Ɍ������Ă���
		_transform->moveForce.y = Easing::SineIn(static_cast<float>(_countFrame), static_cast<float>(_lifeFrame), _speed, 0.0f);
		_countFrame++;
	}

	void Bullet::LateTick()
	{
		// ����u���b�N
		bool isHitButtomBlock = _boxCollider->IsHitButtom();
		if (isHitButtomBlock == true)
		{
			// �e�폜
			GameObject::Destoy(this);

			BreakBlock* leftButtomBlock = dynamic_cast<BreakBlock*>(_boxCollider->GetHitBlockLeftButtom());
			BreakBlock* rightButtomBlock = dynamic_cast<BreakBlock*>(_boxCollider->GetHitBlockRightButtom());
			if (leftButtomBlock != nullptr)
			{
				leftButtomBlock->OnHitBullet();
			}
			if (rightButtomBlock != nullptr)
			{
				rightButtomBlock->OnHitBullet();
			}
		}

		// �G�폜
		vector<HitEnemyInfo> hitEnemyList = EnemyManager::HitCheckEnemy(*_boxCollider);
		for (auto& info : hitEnemyList)
		{
			// �e�폜
			GameObject::Destoy(this);
			
			// ���������G�͎���
			auto hitEnemy = info.hitEnemy;
			EnemyManager::Remove(hitEnemy);
		}

	}

	void Bullet::EndPlay()
	{
	}
#pragma endregion
}