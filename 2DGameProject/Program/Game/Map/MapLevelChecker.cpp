#include "MapLevelChecker.h"
#include "../Player/Player.h"

namespace Downwell
{
	void MapLevelChecker::Start()
	{
		_blockSize = 45.0f;
		_mapNum = 8;
		_oneMapBlockNum = 55;

		// �e�X�e�[�W�̏I�_���W�����̂�
		// 1���烋�[�v���n�߂�
		for (int i = 1; i <= _mapNum; i++)
		{
			// �^�C�g�����������܂�
			float posY = (_blockSize * _oneMapBlockNum * i) + (40 * _blockSize);
			_levelPosYList.push_back(posY);
		}

		_renderer = GetContext().GetComponent<TextRenderer>();
		_renderer->SetText(CurrentLevelChar());

		_player = GameObject::Find<Player>("Player");

	}

	void MapLevelChecker::LateUpdate()
	{
		if (_player == nullptr || _player->IsDeath() == true) return;
		if (_checkPos == nullptr || _renderer == nullptr) return;

		int level = 0;
		for(auto& posY : _levelPosYList)
		{
			level++;
			if (_checkPos->y < posY)
			{
				_currentLevel = (level >= _mapNum) ? _mapNum : level;
				_renderer->SetText(CurrentLevelChar());
				break;
			}
		}

	}

	void MapLevelChecker::End()
	{
		_levelPosYList.clear();
		_renderer = nullptr;
		_checkPos = nullptr;
		_player = nullptr;
	}
}
