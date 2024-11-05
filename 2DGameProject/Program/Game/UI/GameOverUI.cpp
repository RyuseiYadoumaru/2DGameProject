#include "GameOverUI.h"

namespace Downwell
{
	void GameOverUI::OnPlay()
	{
		if (isPlay == true) return;
		isPlay = true;
		_renderer->SetActive(true);
		
	}
	void GameOverUI::OnPause()
	{
		if (isPlay == false) return;

		isPlay = false;
		_renderer->SetActive(false);
	}

#pragma region  System Callback Function

	void GameOverUI::Setup()
	{
		_renderer = AddComponent<TextRenderer>();
		_renderer->SetFontSize(30.0f);
		_renderer->SetFontThick(15.0f);
		_renderer->SetText("GameOver\n press B");
		_renderer->color.Set(255.0f, 0.0f, 0.0f, 0.0f);
		_renderer->SetLayer(60);

		_frameCounter = 0;

		_transform->position.Set(555.0, 720.0f * 0.5f);

		_startPosY = _transform->position.y;
		_targetPosY = _startPosY - _riseValue;
	}

	void GameOverUI::BeginPlay()
	{
		OnPause();
	}

	void GameOverUI::Tick()
	{
		if (isPlay == false) return;
		if (_frameCounter >= _riseFrame) return;

		_transform->position.y = Easing::SineIn(
			static_cast<float>(_frameCounter), static_cast<float>(_riseFrame),
			_startPosY, _targetPosY);

		_renderer->color.a = Easing::SineIn(
			static_cast<float>(_frameCounter), static_cast<float>(_riseFrame),
			0.0f, 255.0f);
		
		_frameCounter++;
	}

	void GameOverUI::EndPlay()
	{
		_renderer = nullptr;
	}

#pragma endregion

}