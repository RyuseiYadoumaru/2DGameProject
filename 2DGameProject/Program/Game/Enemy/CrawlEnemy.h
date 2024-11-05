#pragma once
#include "Enemy.h"


namespace Downwell
{
	enum
	{
		CRAWL_IDLE,
		CRAWL_MOVEMENT
	};

	class CrawlEnemy : public Enemy
	{
	public:
		ENEMY_CLASS

	public:
		void ReverseMoveVector();

	public:
		const Vector2& GetMoveVector() const noexcept { return _moveVec; }
		bool GetIsFall() const noexcept { return isFall; }
		const float GetFallMaxSpeed() const noexcept { return _fallMaxSpeed; }

	private:
		shared_ptr<HFSM<CrawlEnemy>> _stateMahcine = nullptr;
		Vector2 _moveVec = Vector2::Zero;
		Vector2 _downward = Vector2::Down;

		Map2DData* _mapData = nullptr;

		bool isFall = false;
		float _fallMaxSpeed = 20.0f;

	private:
		void OnUpdateCrawlGround();

		void OnHitWall();
		void OnStandCliff();

		bool CheckStandCliff(const Vector2& inDownward, const Vector2& inMoveVector);
		bool CheckHitWall(const Vector2& inMoveVector);

#pragma region System Callback Function
	private:
		void Setup() override;
		void BeginPlay() override;
		void Tick() override;
		void EndPlay() override;
#pragma endregion

	};
}