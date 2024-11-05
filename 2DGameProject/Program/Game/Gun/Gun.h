#pragma once
#include "../Include/ObjectInclude.h"
#include "../Include/MathInclude.h"

#include "GunUI.h"

namespace Downwell
{
	class Gun : public Script
	{
	public:
		SCRIPT_CLASS;

	public:
		constexpr static int MAX_BULLETS_NUM = 8;

	public:
		void Reload();
		void Fire();

	public:
		const int GetRemainingBulletsNum() const noexcept { return _remainingBulletsNum; }

	private:
		int _remainingBulletsNum = 0;
		Vector2 _fireOffset;

		float _recoil = 3.0f;

		TComponentPtr<GunUIManager> _gunUIManager = nullptr;
		bool isFire = false;



	private:
		void Start		() override;
		void End		() override;
		void LateUpdate () override;

	};
}