#pragma once
#include "../Include/ObjectInclude.h"
#include "../Include/MathInclude.h"

namespace Downwell
{
	class Player;

	class MapLevelChecker : public Script
	{
	public:
		SCRIPT_CLASS;

	public:
		int CurrentLevel() const noexcept { return _currentLevel; }
		string CurrentLevelChar() const noexcept { return std::to_string(_currentLevel); }

		void RegisterCheckPos(myMath::Vector2* pos) noexcept { _checkPos = pos; }

	private:
		int _currentLevel = 0;

		int _mapNum = 0;
		int _oneMapBlockNum = 55;
		float _blockSize = 45.0f;

		myMath::Vector2* _checkPos = nullptr;
		TComponentPtr<TextRenderer> _renderer = nullptr;

		vector<float> _levelPosYList;

		Player* _player = nullptr;

	private:
		void Start		() override;
		void LateUpdate () override;
		void End		() override;

	};
}
