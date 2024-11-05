#pragma once
#include "../Include/ObjectInclude.h"

namespace Downwell
{
	class Bullet : public Item
	{
	public:
		ITEM_CLASS;

	public:
		void SetRecoil(float recoil) noexcept { _recoilValue = recoil; }

	protected:
		float _speed = 38.0f;
		int _countFrame = 0;
		int _lifeFrame = 13;

		int _waitDestroyFrame = 1;
		int _destroyFrameCounter = 0;

	private:
		BoxCollider2D* _boxCollider = nullptr;

		float _recoilValue = 0.0f;

	private:
		virtual void Setup() override;
		virtual void BeginPlay() override;
		virtual void Tick() override;
		
		virtual void LateTick() override;
		virtual void EndPlay() override;
	};
}