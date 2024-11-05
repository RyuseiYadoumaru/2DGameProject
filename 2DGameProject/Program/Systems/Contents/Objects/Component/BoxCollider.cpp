
#include "DxLib.h"
#include "BoxCollider.h"
#include "../Generic/GameObject.h"

#include "Camera.h"

#include "../../../../Game/Block/Block.h"
#include "../../../Input/GamePad.h"

namespace myGame::Object
{
#pragma region  System Callbac Functions
	void BoxCollider2D::Initialize()
	{
		SetOrder(50);
		_ownerTransform = &GetContext().GetTrans();
	}

	void BoxCollider2D::Finalize()
	{
		_ownerTransform = nullptr;
	}

	void BoxCollider2D::Start()
	{
	}

	void BoxCollider2D::Update()
	{
		isOnGround = false;

		if (_ownerTransform == nullptr) return;

		// 頂点の更新
		UpdateRectVertex();

		if (canHitCheckMap == false) return;
		isOnGround = CheckGroundFromMap();
	}

	void BoxCollider2D::SecondUpdate()
	{
		// 当たり判定フラグ初期化
		isHitLeft = false;
		isHitRight = false;
		isHitTop = false;
		isHitButtom = false;

		if (_ownerTransform == nullptr) return;

		// 頂点の更新
		UpdateRectVertex();

		if (canHitCheckMap == true)
		{
			// ヒットブロックポインタの初期化
			_hitBlockLeftTop	 = nullptr;
			_hitBlockLeftButtom  = nullptr;
			_hitBlockRightTop	 = nullptr;
			_hitBlockRightButtom = nullptr;

			// マップデータの当たり判定
			// 押し戻し処理も入れてます
			HitCheckAndPushBackMap();
		}
	}

	void BoxCollider2D::LateUpdate()
	{
	}

	void BoxCollider2D::End()
	{
	}

#pragma endregion

	void BoxCollider2D::UpdateRectVertex()
	{
		if (_ownerTransform == nullptr) return;

		// 4頂点の座標
		myMath::Vector2 colliderPos = _ownerTransform->position + _offset;
		_leftPos	= colliderPos.x - (_size.x / 2.0f);
		_rightPos	= colliderPos.x + (_size.x / 2.0f);
		_topPos		= colliderPos.y - (_size.y / 2.0f);
		_buttomPos	= colliderPos.y + (_size.y / 2.0f);
	}

#pragma region  Downwell


	void BoxCollider2D::HitCheckAndPushBackMap()
	{
		// 移動量が多いベクトルを先に判定する
		myMath::Vector2 moveVector = _ownerTransform->GetMoveVector();

		//cout << "MoveVector:::" << "( " << moveVector.x << "," << moveVector.y << " )\n";

		float absMoveVecX = fabsf(moveVector.x);
		float absMoveVecY = fabsf(moveVector.y);
		
		if (absMoveVecX >= absMoveVecY)
		{
			myMath::Vector2 pos = _ownerTransform->position;

			// 左右判定をする
			float pushBackX = CalcPushBackHorizontal(moveVector.x, pos);
			pos.x += pushBackX;

			// 上下判定
			float pushBackY = CalcPushBackVertical(moveVector.y, pos);
			pos.y += pushBackY;

			// 座標の更新
			_ownerTransform->position = pos;

		}
		else
		{
			myMath::Vector2 pos = _ownerTransform->position;

			// 上下判定
			float pushBackY = CalcPushBackVertical(moveVector.y, pos);
			pos.y += pushBackY;

			// 左右判定をする
			float pushBackX = CalcPushBackHorizontal(moveVector.x, pos);
			pos.x += pushBackX;

			// NOTE:座標の更新
			//		横のみで押し戻しが完了する場合、縦の押し戻しは行わない
			//		縦も入れてしまうと壁に張り付いてしまう
			_ownerTransform->position.x = pos.x;
			float newPushBackY = CalcPushBackVertical(moveVector.y, _ownerTransform->position);
			if (newPushBackY == 0)
			{
				// 当たり判定のフラグも折る
				if		(moveVector.y < 0) isHitTop		= false;
				else if (moveVector.y > 0) isHitButtom	= false;
			}
			else
			{
				_ownerTransform->position.y += newPushBackY;
			}
		}

		// 最後に頂点の更新を行う
		UpdateRectVertex();
	}

	bool BoxCollider2D::CheckGroundFromMap()
	{
		auto leftButtom = Downwell::Map2DUtility::GetMapChipFromPosition (*_mapData, _leftPos  + 1.0f, _buttomPos + 1.0f);
		auto rightButtom = Downwell::Map2DUtility::GetMapChipFromPosition(*_mapData, _rightPos - 1.0f, _buttomPos + 1.0f);

		// 右頂点か左頂点がブロックに当たっているとき
		bool isHitBlockLeftButtom = (leftButtom == Downwell::MapChip::NB) || (leftButtom == Downwell::MapChip::BB);
		bool isHitBlockRightButtom = (rightButtom == Downwell::MapChip::NB) || (rightButtom == Downwell::MapChip::BB);
		if (isHitBlockLeftButtom == true || isHitBlockRightButtom == true)
		{
			// 地面に当たった
			return true;
		}
		// 地面に当たっていない
		return false;
	}

	bool BoxCollider2D::IsHitMapChipBlock(float inLeft, float inRight, float inTop, float inButtom)
	{
		auto mapChipLeftTop = Downwell::Map2DUtility::GetMapChipFromPosition(*_mapData, inLeft, inTop);
		auto mapChipRightButtom = Downwell::Map2DUtility::GetMapChipFromPosition(*_mapData, inRight, inButtom);
		
		if (mapChipLeftTop == Downwell::MapChip::BB || mapChipLeftTop == Downwell::MapChip::NB ||
			mapChipRightButtom == Downwell::MapChip::BB || mapChipRightButtom == Downwell::MapChip::NB)
		{
			return true;
		}
		
		return false;
	}

	float BoxCollider2D::CalcPushBackHorizontal(float moveVecX, const myMath::Vector2& inPos)
	{
		//cout << "横判定\n";

		// 4頂点の座標
		myMath::Vector2 colliderPos = inPos + _offset;
		float leftPos	= colliderPos.x - (_size.x / 2.0f);
		float rightPos	= colliderPos.x + (_size.x / 2.0f);
		float topPos	= colliderPos.y - (_size.y / 2.0f);
		float buttomPos = colliderPos.y + (_size.y / 2.0f);


		if (moveVecX < 0)
		{
			// 左判定
			_hitBlockLeftTop = Downwell::Map2DUtility::GetMapChipObjectFromPosition(*_blockList, *_mapData, leftPos, topPos);
			_hitBlockLeftButtom = Downwell::Map2DUtility::GetMapChipObjectFromPosition(*_blockList, *_mapData, leftPos, buttomPos - 1.0f);

			float pushBackX = 0.0f;
			float blockSize = 0.0f;
			if (_hitBlockLeftTop != nullptr)
			{
				blockSize = _hitBlockLeftTop->GetBlockSize();
				pushBackX = CalcPushBackMap(_hitBlockLeftTop->GetTrans().position.x, blockSize, leftPos, false);
			}
			else if (_hitBlockLeftButtom != nullptr)
			{
				blockSize = _hitBlockLeftButtom->GetBlockSize();
				pushBackX = CalcPushBackMap(_hitBlockLeftButtom->GetTrans().position.x, blockSize, leftPos, false);
			}

			//bool isWithinRange = fabsf(pushBackX) <= blockSize / 2.0f;
			bool canPushBack = pushBackX > 0.0f;
			if (canPushBack/* && isWithinRange*/)
			{
				isHitLeft = true;
				cout << pushBackX << ":::→に押し戻し\n";
				return pushBackX;
			}
		}
		else if (moveVecX > 0)
		{
			// 右判定
			_hitBlockRightTop = Downwell::Map2DUtility::GetMapChipObjectFromPosition(*_blockList, *_mapData, rightPos, topPos);
			_hitBlockRightButtom = Downwell::Map2DUtility::GetMapChipObjectFromPosition(*_blockList, *_mapData, rightPos, buttomPos - 1.0f);

			float pushBackX = 0.0f;
			float blockSize = 0.0f;
			if (_hitBlockRightTop != nullptr)
			{
				blockSize = _hitBlockRightTop->GetBlockSize();
				pushBackX = CalcPushBackMap(_hitBlockRightTop->GetTrans().position.x, blockSize, rightPos, true);
			}
			else if (_hitBlockRightButtom != nullptr)
			{
				blockSize = _hitBlockRightButtom->GetBlockSize();
				pushBackX = CalcPushBackMap(_hitBlockRightButtom->GetTrans().position.x, blockSize, rightPos, true);
			}

			bool isWithinRange = fabsf(pushBackX) <= blockSize / 2.0f;
			bool canPushBack = pushBackX < 0.0f;
			if (canPushBack && isWithinRange)
			{
				isHitRight = true;
				cout << pushBackX << ":::←に押し戻し\n";
				return pushBackX;
			}
		}
		return 0.0f;
	}

	float BoxCollider2D::CalcPushBackVertical(float moveVecY, const myMath::Vector2& inPos)
	{
		//cout << "縦判定\n";

		// 4頂点の座標
		myMath::Vector2 colliderPos = inPos + _offset;
		float leftPos	= colliderPos.x - (_size.x / 2.0f);
		float rightPos	= colliderPos.x + (_size.x / 2.0f);
		float topPos	= colliderPos.y - (_size.y / 2.0f);
		float buttomPos = colliderPos.y + (_size.y / 2.0f);

		if (moveVecY >= 0)
		{
			// 下判定
			_hitBlockLeftButtom = Downwell::Map2DUtility::GetMapChipObjectFromPosition(*_blockList, *_mapData, leftPos + 1.0f, buttomPos);
			_hitBlockRightButtom = Downwell::Map2DUtility::GetMapChipObjectFromPosition(*_blockList, *_mapData, rightPos - 1.0f, buttomPos);

			float pushBackY = 0.0f;
			float blockSize = 0.0f;
			if (_hitBlockLeftButtom != nullptr)
			{
				blockSize = _hitBlockLeftButtom->GetBlockSize();
				pushBackY = CalcPushBackMap(_hitBlockLeftButtom->GetTrans().position.y, blockSize, buttomPos, true);
			}
			else if (_hitBlockRightButtom != nullptr)
			{
				blockSize = _hitBlockRightButtom->GetBlockSize();
				pushBackY = CalcPushBackMap(_hitBlockRightButtom->GetTrans().position.y, blockSize, buttomPos, true);
			}

			bool canPushBack = pushBackY < 0.0f;
			if (canPushBack)
			{
				isHitButtom = true;
				cout << pushBackY << ":::↑に押し戻し\n";
				return pushBackY;
			}
		}
		else if (moveVecY < 0.0f)
		{
			// 上判定
			_hitBlockLeftTop = Downwell::Map2DUtility::GetMapChipObjectFromPosition (*_blockList, *_mapData, leftPos  + 1.0f, topPos);
			_hitBlockRightTop = Downwell::Map2DUtility::GetMapChipObjectFromPosition(*_blockList, *_mapData, rightPos - 1.0f, topPos);

			float pushBackY = 0.0f;
			float blockSize = 0.0f;
			if (_hitBlockLeftTop != nullptr)
			{
				blockSize = _hitBlockLeftTop->GetBlockSize();
				pushBackY = CalcPushBackMap(_hitBlockLeftTop->GetTrans().position.y, blockSize, topPos, false);
			}
			else if (_hitBlockRightTop != nullptr)
			{
				blockSize = _hitBlockRightTop->GetBlockSize();
				pushBackY = CalcPushBackMap(_hitBlockRightTop->GetTrans().position.y, blockSize, topPos, false);
			}

			bool isWithinRange = fabsf(pushBackY) <= blockSize / 2.0f;
			bool canPushBack = pushBackY > 0.0f;
			if (canPushBack && isWithinRange)
			{
				isHitTop = true;
				cout << pushBackY << ":::↓に押し戻し\n";
				return pushBackY;
			}
		}
		return 0.0f;
	}


	float BoxCollider2D::CalcPushBackMap(float inHitBlockPos, float inHitBlockSize, float inHitPos, bool  isPushBackLeftOrTop)
	{
		float hitBlockPos = 0.0f;
		if (isPushBackLeftOrTop == true)
		{
			// 上か左に押し戻すとき
			hitBlockPos = inHitBlockPos - (inHitBlockSize / 2.0f);
		}
		else
		{
			hitBlockPos = inHitBlockPos + (inHitBlockSize / 2.0f);
		}
		float pushBack = hitBlockPos - inHitPos;
		return pushBack;
	}

#pragma endregion

}