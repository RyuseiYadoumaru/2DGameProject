#pragma once
#include "../Include/ObjectInclude.h"
#include "../Include/AIInclude.h"
#include "../Include/MathInclude.h"

#include "PlayerDefinition.h"
#include "PlayerActionEvent.h"

#include "../Gun/Gun.h"
#include "../Life/Life.h"

namespace Downwell
{
	enum
	{
		PLAYER_ACTION = 0,
		PLAYER_GROUND,
		PLAYER_FLOATING,
		PLAYER_IDLE,
		PLAYER_WALK,

		PLAYER_JUMP,
		PLAYER_FALL,
		PLAYER_FIRE,
		PLAYER_STEP,

		PLAYER_DEATH,

		PLAYER_ELEMNT_NUM
	};

	class Player : public Character
	{

	public:
		CHARACTER_CLASS

	private: 
		void Setup() override;
		void BeginPlay() override;
		void Tick() override;
		void EndPlay() override;

	public:
		IPlayerActionEvent& GetActionEvent() const noexcept { return *_actionEvent; }


	public:
		// 歩行パラメタ
		const float GetWalkMaxSpeed() const noexcept { return _actionParam.walkMaxSpeed; }
		const float GetWalkMinSpeed() const noexcept { return _actionParam.walkMinSpeed; }

		// ジャンプパラメタ
		const float GetJumpPower()		 const noexcept { return _actionParam.jumpPower; }
		const int GetRisingFrame()		 const noexcept { return _actionParam.risingFrame; }
		const int GetJumpFloatingFrame() const noexcept { return _actionParam.jumpFloatingFrame; }

		// 落下パラメタ
		const float GetFallMaxSpeed() const noexcept { return _actionParam.fallMaxSpeed; }
		const int GetFallMaxSpeedFrame() const noexcept { return _actionParam.risingFrame; }

		// 弾発射パラメタ
		const int GetFireIntervalFrame() const noexcept { return _actionParam.fireIntervalFrame; }

		// 踏みつけパラメタ
		const float GetStartStepPower() const noexcept { return _actionParam.startStepPower; }
		const int GetStepFrame() const noexcept { return _actionParam.stepFrame; }

		// コンポーネント
		BoxCollider2D& GetBoxCollider() const noexcept { return *_boxCollider; }
		Life& GetLife() const noexcept { return *_life.get(); }

		// 状態フラグ
		bool IsStep()	const noexcept { return isStep; }
		bool IsDeath()	const noexcept { return isDeath; }

		// プレイヤーカラー設定
		void SetColor(float r, float g, float b) noexcept
		{
			if (_renderer == nullptr) return;
			_renderer->color.Set(r, g, b, 255.0f);
		}

	public:
		void OnStartStep();
		void OnEndStep();

		void OnDeath();
		void OnDamage();

	private:
		shared_ptr<HFSM<Player>> _stateMahcine = nullptr;
		shared_ptr<IPlayerActionEvent> _actionEvent = nullptr;
		shared_ptr<Life> _life = nullptr;
		TComponentPtr<Renderer> _renderer = nullptr;

		PlayerActionData _actionParam;

		BoxCollider2D* _boxCollider = nullptr;

	private:
		bool isStep = false;
		bool isDeath = false;

	};
}