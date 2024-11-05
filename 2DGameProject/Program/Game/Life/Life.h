#pragma once
#include "../Include/ObjectInclude.h"
#include "../Include/MathInclude.h"

#include "LifeUI.h"

namespace Downwell
{
	class Life : public Script
	{
	public:
		SCRIPT_CLASS;

	public:
		constexpr static int MAX_LIFEPOINT_NUM = 3;

	public:
		void OnDamage(int damage = 1);
		void OnRecovery(int recovery = 1);

	public:
		const int GetLifePoint() const noexcept { return _lifePoint; }

	private:
		int _lifePoint = 0;

		TComponentPtr<LifeUIManager> _lifeUIManager = nullptr;

	private:
		void Start() override;
		void End() override;

	};
}