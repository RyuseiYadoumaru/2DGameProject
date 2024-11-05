
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

		// ���_�̍X�V
		UpdateRectVertex();

		if (canHitCheckMap == false) return;
		isOnGround = CheckGroundFromMap();
	}

	void BoxCollider2D::SecondUpdate()
	{
		// �����蔻��t���O������
		isHitLeft = false;
		isHitRight = false;
		isHitTop = false;
		isHitButtom = false;

		if (_ownerTransform == nullptr) return;

		// ���_�̍X�V
		UpdateRectVertex();

		if (canHitCheckMap == true)
		{
			// �q�b�g�u���b�N�|�C���^�̏�����
			_hitBlockLeftTop	 = nullptr;
			_hitBlockLeftButtom  = nullptr;
			_hitBlockRightTop	 = nullptr;
			_hitBlockRightButtom = nullptr;

			// �}�b�v�f�[�^�̓����蔻��
			// �����߂�����������Ă܂�
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

		// 4���_�̍��W
		myMath::Vector2 colliderPos = _ownerTransform->position + _offset;
		_leftPos	= colliderPos.x - (_size.x / 2.0f);
		_rightPos	= colliderPos.x + (_size.x / 2.0f);
		_topPos		= colliderPos.y - (_size.y / 2.0f);
		_buttomPos	= colliderPos.y + (_size.y / 2.0f);
	}

#pragma region  Downwell


	void BoxCollider2D::HitCheckAndPushBackMap()
	{
		// �ړ��ʂ������x�N�g�����ɔ��肷��
		myMath::Vector2 moveVector = _ownerTransform->GetMoveVector();

		//cout << "MoveVector:::" << "( " << moveVector.x << "," << moveVector.y << " )\n";

		float absMoveVecX = fabsf(moveVector.x);
		float absMoveVecY = fabsf(moveVector.y);
		
		if (absMoveVecX >= absMoveVecY)
		{
			myMath::Vector2 pos = _ownerTransform->position;

			// ���E���������
			float pushBackX = CalcPushBackHorizontal(moveVector.x, pos);
			pos.x += pushBackX;

			// �㉺����
			float pushBackY = CalcPushBackVertical(moveVector.y, pos);
			pos.y += pushBackY;

			// ���W�̍X�V
			_ownerTransform->position = pos;

		}
		else
		{
			myMath::Vector2 pos = _ownerTransform->position;

			// �㉺����
			float pushBackY = CalcPushBackVertical(moveVector.y, pos);
			pos.y += pushBackY;

			// ���E���������
			float pushBackX = CalcPushBackHorizontal(moveVector.x, pos);
			pos.x += pushBackX;

			// NOTE:���W�̍X�V
			//		���݂̂ŉ����߂�����������ꍇ�A�c�̉����߂��͍s��Ȃ�
			//		�c������Ă��܂��ƕǂɒ���t���Ă��܂�
			_ownerTransform->position.x = pos.x;
			float newPushBackY = CalcPushBackVertical(moveVector.y, _ownerTransform->position);
			if (newPushBackY == 0)
			{
				// �����蔻��̃t���O���܂�
				if		(moveVector.y < 0) isHitTop		= false;
				else if (moveVector.y > 0) isHitButtom	= false;
			}
			else
			{
				_ownerTransform->position.y += newPushBackY;
			}
		}

		// �Ō�ɒ��_�̍X�V���s��
		UpdateRectVertex();
	}

	bool BoxCollider2D::CheckGroundFromMap()
	{
		auto leftButtom = Downwell::Map2DUtility::GetMapChipFromPosition (*_mapData, _leftPos  + 1.0f, _buttomPos + 1.0f);
		auto rightButtom = Downwell::Map2DUtility::GetMapChipFromPosition(*_mapData, _rightPos - 1.0f, _buttomPos + 1.0f);

		// �E���_�������_���u���b�N�ɓ������Ă���Ƃ�
		bool isHitBlockLeftButtom = (leftButtom == Downwell::MapChip::NB) || (leftButtom == Downwell::MapChip::BB);
		bool isHitBlockRightButtom = (rightButtom == Downwell::MapChip::NB) || (rightButtom == Downwell::MapChip::BB);
		if (isHitBlockLeftButtom == true || isHitBlockRightButtom == true)
		{
			// �n�ʂɓ�������
			return true;
		}
		// �n�ʂɓ������Ă��Ȃ�
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
		//cout << "������\n";

		// 4���_�̍��W
		myMath::Vector2 colliderPos = inPos + _offset;
		float leftPos	= colliderPos.x - (_size.x / 2.0f);
		float rightPos	= colliderPos.x + (_size.x / 2.0f);
		float topPos	= colliderPos.y - (_size.y / 2.0f);
		float buttomPos = colliderPos.y + (_size.y / 2.0f);


		if (moveVecX < 0)
		{
			// ������
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
				cout << pushBackX << ":::���ɉ����߂�\n";
				return pushBackX;
			}
		}
		else if (moveVecX > 0)
		{
			// �E����
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
				cout << pushBackX << ":::���ɉ����߂�\n";
				return pushBackX;
			}
		}
		return 0.0f;
	}

	float BoxCollider2D::CalcPushBackVertical(float moveVecY, const myMath::Vector2& inPos)
	{
		//cout << "�c����\n";

		// 4���_�̍��W
		myMath::Vector2 colliderPos = inPos + _offset;
		float leftPos	= colliderPos.x - (_size.x / 2.0f);
		float rightPos	= colliderPos.x + (_size.x / 2.0f);
		float topPos	= colliderPos.y - (_size.y / 2.0f);
		float buttomPos = colliderPos.y + (_size.y / 2.0f);

		if (moveVecY >= 0)
		{
			// ������
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
				cout << pushBackY << ":::���ɉ����߂�\n";
				return pushBackY;
			}
		}
		else if (moveVecY < 0.0f)
		{
			// �㔻��
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
				cout << pushBackY << ":::���ɉ����߂�\n";
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
			// �ォ���ɉ����߂��Ƃ�
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