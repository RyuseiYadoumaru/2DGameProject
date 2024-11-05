#include "Timer.h"
#include <chrono>
#include <thread>
#include "DxLib.h"
#include <iostream>

namespace mySystem
{
	void Timer::Initialize()
{
}

void Timer::Update()
{
	_currentTime = static_cast<float>(GetNowCount());
	_deltaTime = _currentTime - _lastTime;
	_lastTime = _currentTime;
	_totalFrameCount++;

	// �ҋ@
	Wait();

	// �\��
	//PrintFPS();
}

void Timer::Finalize()
{
}

void Timer::Wait()
{
	float frameParam = (1.0f / FPS) * 1000.0f;
	float sleep_time = frameParam - _deltaTime;

	if (sleep_time > 0)
	{
		float tt = sleep_time / 1000.0f;

		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(tt)));
	}
}

void Timer::PrintFPS()
{
	unsigned int intervalFrame = 60;

	/*	FPS�v��	*/
	if (_totalFrameCount % intervalFrame == 0)
	{
		_currentFps = intervalFrame * 1000.0f / (_currentTime - _saveTime);
		_saveTime = _currentTime;

		/****	FPS�\���ݒ�	****/
		std::cout << "FPS�F" << _currentFps << std::endl;
	}
}

}