#pragma once
#include "../../../../Systems/BaseClasses/Component.h"
#include "../../Maths/Vector2.h"

#include "Transform.h"

// DownWell用にBoxColliderをカスタマイズしています
#include "../../../../Game/Map/Map2DDefinition.h"

namespace myGame::Object
{
	class BoxCollider2D : public mySystem::IComponent
	{
	public:
		COMPONENT_CLASS;

	public:
		const myMath::Vector2& GetSize() const noexcept { return _size; }
		void SetSize(float inSizeX, float inSizeY) noexcept { _size.x = inSizeX; _size.y = inSizeY; }
		void SetOffset(float inOffsetX, float inOffsetY) noexcept { _offset.x = inOffsetX; _offset.y = inOffsetY; }

		myMath::Vector2 GetPos() noexcept
		{
			myMath::Vector2 pos;
			pos.x = _ownerTransform->position.x + _offset.x;
			pos.y = _ownerTransform->position.y + _offset.y;
			return pos;
		}

		bool IsHitLeft()	const noexcept { return isHitLeft; }
		bool IsHitRight()	const noexcept { return isHitRight; }
		bool IsHitTop()		const noexcept { return isHitTop; }
		bool IsHitButtom()	const noexcept { return isHitButtom; }

		bool IsOnGround() const noexcept { return isOnGround; }

		float GetLeftPos()	 const noexcept { return _leftPos; }
		float GetRightPos()	 const noexcept { return _rightPos; }
		float GetTopPos()	 const noexcept { return _topPos; }
		float GetButtomPos() const noexcept { return _buttomPos; }

	private:
		Transform* _ownerTransform = nullptr;

		myMath::Vector2 _size;
		myMath::Vector2 _offset;

		float _leftPos	 = 0.0f;
		float _rightPos  = 1.0f;
		float _topPos	 = 0.0f;
		float _buttomPos = 1.0f;

		bool isHitLeft		= false;
		bool isHitRight		= false;
		bool isHitTop		= false;
		bool isHitButtom	= false;

		bool isOnGround = false;

	private:
		void UpdateRectVertex();

#pragma region Downwell
	public:
		void RegisterMap(Downwell::Map2DData* mapData, Downwell::BlockMap* blockMap)
		{
			canHitCheckMap = true;
			_mapData = mapData;
			_blockList = blockMap;
		}

		Downwell::Map2DData* GetCheckMapData() const noexcept { return _mapData; }

		Downwell::Block* GetHitBlockLeftTop()		const noexcept { return _hitBlockLeftTop; }
		Downwell::Block* GetHitBlockLeftButtom()	const noexcept { return _hitBlockLeftButtom; }
		Downwell::Block* GetHitBlockRightTop()		const noexcept { return _hitBlockRightTop; }
		Downwell::Block* GetHitBlockRightButtom()	const noexcept { return _hitBlockRightButtom; }

	private:
		bool canHitCheckMap = false;
		Downwell::Map2DData* _mapData = nullptr;
		Downwell::BlockMap* _blockList = nullptr;

		Downwell::Block* _hitBlockLeftTop		= nullptr;
		Downwell::Block* _hitBlockLeftButtom	= nullptr;
		Downwell::Block* _hitBlockRightTop		= nullptr;
		Downwell::Block* _hitBlockRightButtom	= nullptr;

	private:
		void HitCheckAndPushBackMap();
		bool CheckGroundFromMap();

		bool IsHitMapChipBlock(float inLeft, float inRight, float inTop, float inButtom);

		float CalcPushBackHorizontal(float moveVecX, const myMath::Vector2& inPos);
		float CalcPushBackVertical(float moveVecY, const myMath::Vector2& inPos);
		float CalcPushBackMap(float inHitBlockPos, float inHitBlockSize, float inHitPos, bool  isPushBackLeftOrTop);

#pragma endregion // Downwell専用でBoxColliderをカスタマイズ

	public:
		virtual void Initialize() override;
		virtual void Finalize() override;

		virtual void Start() override;
		virtual void Update() override;
		virtual void SecondUpdate() override;
		virtual void LateUpdate() override;
		virtual void End() override;
	};
}